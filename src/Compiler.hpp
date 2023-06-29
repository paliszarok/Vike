#pragma once

#include "Processor.hpp"

void StringReplace(std::string &str, const std::string &old_sub, const std::string &new_sub)
{
    size_t pos = str.find(old_sub);
    while (pos != std::string::npos)
    {
        str.replace(pos, old_sub.length(), new_sub);
        pos = str.find(old_sub, pos + new_sub.length());
    }
}

std::string FileToString(const std::string &FilePath)
{
    std::ifstream File(FilePath);
    std::stringstream Buffer;
    Buffer << File.rdbuf();
    return Buffer.str();
}

std::string RemoveComments(const std::string &Line)
{
    std::size_t CommentPosition = Line.find(';');
    if (CommentPosition != std::string::npos)
    {
        return Line.substr(0, CommentPosition);
    }
    return Line;
}

std::string TrimWhitespace(const std::string &Line)
{
    std::size_t Start = Line.find_first_not_of(" \t\n\r");
    std::size_t End = Line.find_last_not_of(" \t\n\r");

    if (Start != std::string::npos && End != std::string::npos)
    {
        return Line.substr(Start, End - Start + 1);
    }

    return Line;
}

std::string ToLowercase(const std::string &Line)
{
    std::string LowercaseLine = Line;
    std::transform(LowercaseLine.begin(), LowercaseLine.end(), LowercaseLine.begin(), [](unsigned char c)
                   { return std::tolower(c); });
    return LowercaseLine;
}

std::string RemoveEmptyLines(const std::string &FileContent)
{
    std::string Result;
    std::string Line;

    std::istringstream FileStream(FileContent);
    while (std::getline(FileStream, Line))
    {
        if (!Line.empty())
        {
            Result += Line + '\n';
        }
    }

    return Result;
}

std::string CleanCode(const std::string &FileContent)
{
    std::string CleanedContent;
    std::string Line;

    std::istringstream FileStream(FileContent);
    while (std::getline(FileStream, Line))
    {
        std::string CleanedLine = RemoveComments(Line);
        CleanedLine = TrimWhitespace(CleanedLine);
        CleanedLine = ToLowercase(CleanedLine);
        CleanedContent += CleanedLine + '\n';
    }

    return RemoveEmptyLines(CleanedContent);
}

std::string RemoveLabels(const std::string &FileContent)
{
    std::stringstream ResultStream;
    std::string Line;

    std::istringstream FileStream(FileContent);
    while (std::getline(FileStream, Line))
    {
        if (!Line.empty() && Line.back() == ':')
        {
            continue;
        }

        ResultStream << Line << '\n';
    }

    return RemoveEmptyLines(ResultStream.str());
}

std::string GetOpcode(const std::string &Line)
{
    std::stringstream StringStream(Line);
    std::string Opcode;
    StringStream >> Opcode;
    return Opcode;
}

std::vector<std::string> GetOperands(const std::string &Line)
{
    std::vector<std::string> Operands;
    std::stringstream StringStream(Line);

    std::string Opcode;
    StringStream >> Opcode;

    std::string Operand;
    while (StringStream >> Operand)
    {
        if (!Operand.empty() && Operand.back() == ',')
        {
            Operand.pop_back();
        }

        Operands.push_back(Operand);
    }

    return Operands;
}

uint32_t HandleNumber(std::string Operand)
{
    if (Operand[0] == '%' || Operand.substr(0, 2) == "0b")
    {
        return std::stoul(Operand.substr(1), nullptr, 2);
    }
    else if (Operand[0] == '#' || Operand.substr(0, 2) == "0d")
    {
        return std::stoul(Operand.substr(1), nullptr, 10);
    }
    else if (Operand[0] == '$' || Operand.substr(0, 2) == "0x")
    {
        return std::stoul(Operand.substr(1), nullptr, 16);
    }
    else
    {
        return std::stoul(Operand);
    }
}

uint8_t HandleRegister(std::string Operand)
{
    if (Operand == "a")
    {
        return 0;
    }
    else if (Operand == "c")
    {
        return 1;
    }
    else if (Operand == "h")
    {
        return 2;
    }
    else if (Operand == "l")
    {
        return 3;
    }
    else if (Operand == "s")
    {
        return 4;
    }
    else if (Operand == "x")
    {
        return 5;
    }
    else if (Operand == "y")
    {
        return 6;
    }
    else if (Operand == "z")
    {
        return 7;
    }
    else
    {
        return HandleNumber(Operand);
    }
}

std::unordered_map<std::string, uint8_t> InstructionSizes = {
    {"nop", 1},
    {"lda", 2},
    {"ldc", 2},
    {"ldh", 2},
    {"ldl", 2},
    {"ldm", 3},
    {"lds", 2},
    {"ldx", 2},
    {"ldy", 2},
    {"ldz", 2},
    {"lra", 2},
    {"lrc", 2},
    {"lrh", 2},
    {"lrl", 2},
    {"lrs", 2},
    {"lrx", 2},
    {"lry", 2},
    {"lrz", 2},
    {"sta", 3},
    {"stam", 1},
    {"stx", 3},
    {"sty", 3},
    {"stz", 3},
    {"lma", 3},
    {"lmam", 1},
    {"lmx", 3},
    {"lmy", 3},
    {"lmz", 3},
    {"pha", 1},
    {"phx", 1},
    {"phy", 1},
    {"phz", 1},
    {"ppa", 1},
    {"ppx", 1},
    {"ppy", 1},
    {"ppz", 1},
    {"swa", 2},
    {"swb", 2},
    {"ada", 1},
    {"adx", 1},
    {"ady", 1},
    {"adz", 1},
    {"sba", 1},
    {"sbx", 1},
    {"sby", 1},
    {"sbz", 1},
    {"anx", 1},
    {"any", 1},
    {"anz", 1},
    {"orx", 1},
    {"ory", 1},
    {"orz", 1},
    {"xrx", 1},
    {"xry", 1},
    {"xrz", 1},
    {"slx", 1},
    {"sly", 1},
    {"slz", 1},
    {"srx", 1},
    {"sry", 1},
    {"srz", 1},
    {"inm", 1},
    {"inx", 1},
    {"iny", 1},
    {"inz", 1},
    {"dem", 1},
    {"dex", 1},
    {"dey", 1},
    {"dez", 1},
    {"cpx", 2},
    {"cpy", 2},
    {"cpz", 2},
    {"jmp", 3},
    {"jne", 3},
    {"jb", 3},
    {"je", 3},
    {"ja", 3},
    {"call", 3},
    {"ret", 1},
};

bool Compile(const std::string &FilePath)
{
    std::string Filename = FilePath.substr(0, FilePath.length() - 3) + "vike";
    std::string Code = CleanCode(FileToString(FilePath));

    std::istringstream PreStream(Code);
    std::string Line;

    while (std::getline(PreStream, Line))
    {
        std::string Opcode = GetOpcode(Line);
        std::vector<std::string> Operands = GetOperands(Line);

        if (Opcode[0] == '.')
        {
            if (Opcode.substr(1) == "def")
            {
                StringReplace(Code, Operands[0], Operands[1]);
            }
            else if (Opcode.substr(1) == "inc")
            {
                std::string IncludeFilePath = Operands[0];
                std::string IncludedCode = FileToString(IncludeFilePath);

                std::string IncludeDirective = Opcode + " " + Operands[0];
                std::size_t IncludeLinePos = Code.find(IncludeDirective);
                if (IncludeLinePos != std::string::npos)
                {
                    Code.insert(IncludeLinePos + IncludeDirective.length(), "\n" + IncludedCode);
                }

                StringReplace(Code, IncludeDirective, "");
                Code = CleanCode(Code);
            }
        }
    }

    std::unordered_map<std::string, uint16_t> Labels;
    std::istringstream LabelStream(Code);
    uint16_t Address = 0;

    while (std::getline(LabelStream, Line))
    {
        std::string Opcode = GetOpcode(Line);
        std::vector<std::string> Operands = GetOperands(Line);

        if (Opcode[0] == '.')
        {
            if (Opcode.substr(1) == "byte")
            {
                Address += Operands.size();
            }
            else if (Opcode.substr(1) == "dbyte")
            {
                Address += Operands.size() * 2;
            }
            else if (Opcode.substr(1) == "tbyte")
            {
                Address += Operands.size() * 3;
            }
            else if (Opcode.substr(1) == "qbyte")
            {
                Address += Operands.size() * 4;
            }
            else if (Opcode.substr(1) == "align")
            {
                for (uint16_t i = Address; i < HandleNumber(Operands[0]); i++)
                {
                    Address++;
                }
            }
            else if (Opcode.substr(1) == "org")
            {
                Address = HandleNumber(Operands[0]);
            }
            else if (Opcode.substr(1) == "zero")
            {
                for (uint32_t i = 0; i < HandleNumber(Operands[0]); i++)
                {
                    Address++;
                }
            }
        }
        else
        {
            if (Opcode.back() == ':')
            {
                std::string Label = Opcode.substr(0, Opcode.length() - 1);
                Labels[Label] = Address;
            }
            else
            {
                Address += InstructionSizes[Opcode];
            }
        }
    }
    Code = RemoveLabels(Code);

    Address = 0;
    std::istringstream FileStream(Code);
    std::vector<uint8_t> Data;

    while (std::getline(FileStream, Line))
    {
        std::string Opcode = GetOpcode(Line);
        std::vector<std::string> Operands = GetOperands(Line);

        if (Opcode[0] == '.')
        {
            if (Opcode.substr(1) == "byte")
            {
                for (uint8_t i = 0; i < Operands.size(); i++)
                {
                    Data.push_back(HandleNumber(Operands[i]));
                    Address += 1;
                }
            }
            else if (Opcode.substr(1) == "dbyte")
            {
                for (uint8_t i = 0; i < Operands.size(); i++)
                {
                    uint8_t DoubleByte[2];
                    U16toU8(HandleNumber(Operands[i]), DoubleByte);
                    Data.push_back(DoubleByte[0]);
                    Data.push_back(DoubleByte[1]);
                    Address += 2;
                }
            }
            else if (Opcode.substr(1) == "tbyte")
            {
                for (uint8_t i = 0; i < Operands.size(); i++)
                {
                    uint8_t TripleByte[3];
                    U24toU8(HandleNumber(Operands[i]), TripleByte);
                    Data.push_back(TripleByte[0]);
                    Data.push_back(TripleByte[1]);
                    Data.push_back(TripleByte[2]);
                    Address += 3;
                }
            }
            else if (Opcode.substr(1) == "qbyte")
            {
                for (uint8_t i = 0; i < Operands.size(); i++)
                {
                    uint8_t QuadrupleByte[4];
                    U32toU8(HandleNumber(Operands[i]), QuadrupleByte);
                    Data.push_back(QuadrupleByte[0]);
                    Data.push_back(QuadrupleByte[1]);
                    Data.push_back(QuadrupleByte[2]);
                    Data.push_back(QuadrupleByte[3]);
                    Address += 4;
                }
            }
            else if (Opcode.substr(1) == "align")
            {
                for (uint16_t i = Address; i < HandleNumber(Operands[0]); i++)
                {
                    Data.push_back(0);
                    Address++;
                }
            }
            else if (Opcode.substr(1) == "zero")
            {
                for (uint32_t i = 0; i < HandleNumber(Operands[0]); i++)
                {
                    Data.push_back(0);
                    Address++;
                }
            }
            else if (Opcode.substr(1) != "def" && Opcode.substr(1) != "inc" && Opcode.substr(1) != "org")
            {
                std::cerr << "Unknown directive: " << Opcode << ", press any keys to ignore";
                std::cin.get();
            }
        }
        else
        {
            if (Opcode == "nop")
            {
                Data.push_back(I_NOP);
            }
            else if (Opcode == "lda")
            {
                Data.push_back(I_LDA);
                Data.push_back(HandleNumber(Operands[0]));
            }
            else if (Opcode == "ldc")
            {
                Data.push_back(I_LDC);
                Data.push_back(HandleNumber(Operands[0]));
            }
            else if (Opcode == "ldh")
            {
                Data.push_back(I_LDH);
                Data.push_back(HandleNumber(Operands[0]));
            }
            else if (Opcode == "ldl")
            {
                Data.push_back(I_LDL);
                Data.push_back(HandleNumber(Operands[0]));
            }
            else if (Opcode == "ldm")
            {
                Data.push_back(I_LDM);
                uint8_t MemoryAddressBytes[2];
                U16toU8(HandleNumber(Operands[0]), MemoryAddressBytes);
                Data.push_back(MemoryAddressBytes[0]);
                Data.push_back(MemoryAddressBytes[1]);
            }
            else if (Opcode == "lds")
            {
                Data.push_back(I_LDS);
                Data.push_back(HandleNumber(Operands[0]));
            }
            else if (Opcode == "ldx")
            {
                Data.push_back(I_LDX);
                Data.push_back(HandleNumber(Operands[0]));
            }
            else if (Opcode == "ldy")
            {
                Data.push_back(I_LDY);
                Data.push_back(HandleNumber(Operands[0]));
            }
            else if (Opcode == "ldz")
            {
                Data.push_back(I_LDZ);
                Data.push_back(HandleNumber(Operands[0]));
            }
            else if (Opcode == "lra")
            {
                Data.push_back(I_LRA);
                Data.push_back(HandleRegister(Operands[0]));
            }
            else if (Opcode == "lrc")
            {
                Data.push_back(I_LRC);
                Data.push_back(HandleRegister(Operands[0]));
            }
            else if (Opcode == "lrh")
            {
                Data.push_back(I_LRH);
                Data.push_back(HandleRegister(Operands[0]));
            }
            else if (Opcode == "lrl")
            {
                Data.push_back(I_LRL);
                Data.push_back(HandleRegister(Operands[0]));
            }
            else if (Opcode == "lrs")
            {
                Data.push_back(I_LRS);
                Data.push_back(HandleRegister(Operands[0]));
            }
            else if (Opcode == "lrx")
            {
                Data.push_back(I_LRX);
                Data.push_back(HandleRegister(Operands[0]));
            }
            else if (Opcode == "lry")
            {
                Data.push_back(I_LRY);
                Data.push_back(HandleRegister(Operands[0]));
            }
            else if (Opcode == "lrz")
            {
                Data.push_back(I_LRZ);
                Data.push_back(HandleRegister(Operands[0]));
            }
            else if (Opcode == "sta")
            {
                Data.push_back(I_STA);
                uint8_t MemoryAddressBytes[2];
                U16toU8(HandleNumber(Operands[0]), MemoryAddressBytes);
                Data.push_back(MemoryAddressBytes[0]);
                Data.push_back(MemoryAddressBytes[1]);
            }
            else if (Opcode == "stam")
            {
                Data.push_back(I_STAM);
            }
            else if (Opcode == "stx")
            {
                Data.push_back(I_STX);
                uint8_t MemoryAddressBytes[2];
                U16toU8(HandleNumber(Operands[0]), MemoryAddressBytes);
                Data.push_back(MemoryAddressBytes[0]);
                Data.push_back(MemoryAddressBytes[1]);
            }
            else if (Opcode == "sty")
            {
                Data.push_back(I_STY);
                uint8_t MemoryAddressBytes[2];
                U16toU8(HandleNumber(Operands[0]), MemoryAddressBytes);
                Data.push_back(MemoryAddressBytes[0]);
                Data.push_back(MemoryAddressBytes[1]);
            }
            else if (Opcode == "stz")
            {
                Data.push_back(I_STZ);
                uint8_t MemoryAddressBytes[2];
                U16toU8(HandleNumber(Operands[0]), MemoryAddressBytes);
                Data.push_back(MemoryAddressBytes[0]);
                Data.push_back(MemoryAddressBytes[1]);
            }
            else if (Opcode == "lma")
            {
                Data.push_back(I_LMA);
                uint8_t MemoryAddressBytes[2];
                U16toU8(HandleNumber(Operands[0]), MemoryAddressBytes);
                Data.push_back(MemoryAddressBytes[0]);
                Data.push_back(MemoryAddressBytes[1]);
            }
            else if (Opcode == "lmam")
            {
                Data.push_back(I_LMAM);
            }
            else if (Opcode == "lmx")
            {
                Data.push_back(I_LMX);
                uint8_t MemoryAddressBytes[2];
                U16toU8(HandleNumber(Operands[0]), MemoryAddressBytes);
                Data.push_back(MemoryAddressBytes[0]);
                Data.push_back(MemoryAddressBytes[1]);
            }
            else if (Opcode == "lmy")
            {
                Data.push_back(I_LMY);
                uint8_t MemoryAddressBytes[2];
                U16toU8(HandleNumber(Operands[0]), MemoryAddressBytes);
                Data.push_back(MemoryAddressBytes[0]);
                Data.push_back(MemoryAddressBytes[1]);
            }
            else if (Opcode == "lmz")
            {
                Data.push_back(I_LMZ);
                uint8_t MemoryAddressBytes[2];
                U16toU8(HandleNumber(Operands[0]), MemoryAddressBytes);
                Data.push_back(MemoryAddressBytes[0]);
                Data.push_back(MemoryAddressBytes[1]);
            }
            else if (Opcode == "pha")
            {
                Data.push_back(I_PHA);
            }
            else if (Opcode == "phx")
            {
                Data.push_back(I_PHX);
            }
            else if (Opcode == "phy")
            {
                Data.push_back(I_PHY);
            }
            else if (Opcode == "phz")
            {
                Data.push_back(I_PHZ);
            }
            else if (Opcode == "ppa")
            {
                Data.push_back(I_PPA);
            }
            else if (Opcode == "ppx")
            {
                Data.push_back(I_PPX);
            }
            else if (Opcode == "ppy")
            {
                Data.push_back(I_PPY);
            }
            else if (Opcode == "ppz")
            {
                Data.push_back(I_PPZ);
            }
            else if (Opcode == "swa")
            {
                Data.push_back(I_SWA);
                Data.push_back(HandleNumber(Operands[0]));
            }
            else if (Opcode == "swb")
            {
                Data.push_back(I_SWB);
                Data.push_back(HandleNumber(Operands[0]));
            }
            else if (Opcode == "ada")
            {
                Data.push_back(I_ADA);
            }
            else if (Opcode == "adx")
            {
                Data.push_back(I_ADX);
            }
            else if (Opcode == "ady")
            {
                Data.push_back(I_ADY);
            }
            else if (Opcode == "adz")
            {
                Data.push_back(I_ADZ);
            }
            else if (Opcode == "sba")
            {
                Data.push_back(I_SBA);
            }
            else if (Opcode == "sbx")
            {
                Data.push_back(I_SBX);
            }
            else if (Opcode == "sby")
            {
                Data.push_back(I_SBY);
            }
            else if (Opcode == "sbz")
            {
                Data.push_back(I_SBZ);
            }
            else if (Opcode == "anx")
            {
                Data.push_back(I_ANX);
            }
            else if (Opcode == "any")
            {
                Data.push_back(I_ANY);
            }
            else if (Opcode == "anz")
            {
                Data.push_back(I_ANZ);
            }
            else if (Opcode == "orx")
            {
                Data.push_back(I_ORX);
            }
            else if (Opcode == "ory")
            {
                Data.push_back(I_ORY);
            }
            else if (Opcode == "orz")
            {
                Data.push_back(I_ORZ);
            }
            else if (Opcode == "xrx")
            {
                Data.push_back(I_XRX);
            }
            else if (Opcode == "xry")
            {
                Data.push_back(I_XRY);
            }
            else if (Opcode == "xrz")
            {
                Data.push_back(I_XRZ);
            }
            else if (Opcode == "slx")
            {
                Data.push_back(I_SLX);
            }
            else if (Opcode == "sly")
            {
                Data.push_back(I_SLY);
            }
            else if (Opcode == "slz")
            {
                Data.push_back(I_SLZ);
            }
            else if (Opcode == "srx")
            {
                Data.push_back(I_SRX);
            }
            else if (Opcode == "sry")
            {
                Data.push_back(I_SRY);
            }
            else if (Opcode == "srz")
            {
                Data.push_back(I_SRZ);
            }
            else if (Opcode == "inm")
            {
                Data.push_back(I_INM);
            }
            else if (Opcode == "inx")
            {
                Data.push_back(I_INX);
            }
            else if (Opcode == "iny")
            {
                Data.push_back(I_INY);
            }
            else if (Opcode == "inz")
            {
                Data.push_back(I_INZ);
            }
            else if (Opcode == "dem")
            {
                Data.push_back(I_DEM);
            }
            else if (Opcode == "dex")
            {
                Data.push_back(I_DEX);
            }
            else if (Opcode == "dey")
            {
                Data.push_back(I_DEY);
            }
            else if (Opcode == "dez")
            {
                Data.push_back(I_DEZ);
            }
            else if (Opcode == "cpx")
            {
                Data.push_back(I_CPX);
                Data.push_back(HandleRegister(Operands[0]));
            }
            else if (Opcode == "cpy")
            {
                Data.push_back(I_CPY);
                Data.push_back(HandleRegister(Operands[0]));
            }
            else if (Opcode == "cpz")
            {
                Data.push_back(I_CPZ);
                Data.push_back(HandleRegister(Operands[0]));
            }
            else if (Opcode == "jmp")
            {
                Data.push_back(I_JMP);
                uint8_t MemoryAddressBytes[2];
                uint16_t MemoryAddress;
                if (Labels.find(Operands[0]) != Labels.end())
                {
                    MemoryAddress = Labels[Operands[0]];
                }
                else
                {
                    MemoryAddress = HandleNumber(Operands[0]);
                }
                U16toU8(MemoryAddress, MemoryAddressBytes);
                Data.push_back(MemoryAddressBytes[0]);
                Data.push_back(MemoryAddressBytes[1]);
            }
            else if (Opcode == "jne")
            {
                Data.push_back(I_JNE);
                uint8_t MemoryAddressBytes[2];
                uint16_t MemoryAddress;
                if (Labels.find(Operands[0]) != Labels.end())
                {
                    MemoryAddress = Labels[Operands[0]];
                }
                else
                {
                    MemoryAddress = HandleNumber(Operands[0]);
                }
                U16toU8(MemoryAddress, MemoryAddressBytes);
                Data.push_back(MemoryAddressBytes[0]);
                Data.push_back(MemoryAddressBytes[1]);
            }
            else if (Opcode == "jb")
            {
                Data.push_back(I_JB);
                uint8_t MemoryAddressBytes[2];
                uint16_t MemoryAddress;
                if (Labels.find(Operands[0]) != Labels.end())
                {
                    MemoryAddress = Labels[Operands[0]];
                }
                else
                {
                    MemoryAddress = HandleNumber(Operands[0]);
                }
                U16toU8(MemoryAddress, MemoryAddressBytes);
                Data.push_back(MemoryAddressBytes[0]);
                Data.push_back(MemoryAddressBytes[1]);
            }
            else if (Opcode == "je")
            {
                Data.push_back(I_JE);
                uint8_t MemoryAddressBytes[2];
                uint16_t MemoryAddress;
                if (Labels.find(Operands[0]) != Labels.end())
                {
                    MemoryAddress = Labels[Operands[0]];
                }
                else
                {
                    MemoryAddress = HandleNumber(Operands[0]);
                }
                U16toU8(MemoryAddress, MemoryAddressBytes);
                Data.push_back(MemoryAddressBytes[0]);
                Data.push_back(MemoryAddressBytes[1]);
            }
            else if (Opcode == "ja")
            {
                Data.push_back(I_JA);
                uint8_t MemoryAddressBytes[2];
                uint16_t MemoryAddress;
                if (Labels.find(Operands[0]) != Labels.end())
                {
                    MemoryAddress = Labels[Operands[0]];
                }
                else
                {
                    MemoryAddress = HandleNumber(Operands[0]);
                }
                U16toU8(MemoryAddress, MemoryAddressBytes);
                Data.push_back(MemoryAddressBytes[0]);
                Data.push_back(MemoryAddressBytes[1]);
            }
            else if (Opcode == "call")
            {
                Data.push_back(I_CALL);
                uint8_t MemoryAddressBytes[2];
                uint16_t MemoryAddress;
                if (Labels.find(Operands[0]) != Labels.end())
                {
                    MemoryAddress = Labels[Operands[0]];
                }
                else
                {
                    MemoryAddress = HandleNumber(Operands[0]);
                }
                U16toU8(MemoryAddress, MemoryAddressBytes);
                Data.push_back(MemoryAddressBytes[0]);
                Data.push_back(MemoryAddressBytes[1]);
            }
            else if (Opcode == "ret")
            {
                Data.push_back(I_RET);
            }
            else
            {
                std::cerr << "Unknown instruction: " << Opcode << ", press any keys to ignore";
                std::cin.get();
            }

            Address += InstructionSizes[Opcode];
        }
    }

    Cartridge.Create(Filename, Data);

    std::cin.get();
    return 0;
}