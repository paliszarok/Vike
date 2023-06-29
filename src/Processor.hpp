#pragma once

#include "Other.hpp"

uint8_t Register[8];
uint16_t ProgramCounter;
/*
A [0]: Accumulator
C [1]: Comparation flags (CMP)
H [2]: High
L [3]: Low
S [4]: Stack Pointer (SP)
X [5]: General Purpose
Y [6]: General Purpose
Z [7]: General Purpose
Stack Pointer (SP)
Program Counter (PC)
Comparation flags (CMP):
    0: Not equal
    1: Below
    2: Equal
    3: Above
*/

enum Instruction
{
    I_NOP = 0x00,  // Do nothing [1]
    I_LDA = 0x10,  // Load constant into Accumulator [2]
    I_LDC = 0x11,  // Load constant into CMP [2]
    I_LDH = 0x12,  // Load constant into High [2]
    I_LDL = 0x13,  // Load constant into Low [2]
    I_LDM = 0x14,  // Load constant into High and Low [3]
    I_LDS = 0x15,  // Load constant into SP [2]
    I_LDX = 0x16,  // Load constant into X register [2]
    I_LDY = 0x17,  // Load constant into Y register [2]
    I_LDZ = 0x18,  // Load constant into Z register [2]
    I_LRA = 0x20,  // Load register into Accumulator [2]
    I_LRC = 0x21,  // Load register into CMP [2]
    I_LRH = 0x22,  // Load register into High [2]
    I_LRL = 0x23,  // Load register into Low [2]
    I_LRS = 0x24,  // Load register into SP [2]
    I_LRX = 0x25,  // Load register into X register [2]
    I_LRY = 0x26,  // Load register into Y register [2]
    I_LRZ = 0x27,  // Load register into Z register [2]
    I_STA = 0x30,  // Move Accumulator to memory [3]
    I_STAM = 0x31, // Move Accumulator to memory at High and Low [1]
    I_STX = 0x32,  // Move X register to memory [3]
    I_STY = 0x33,  // Move Y register to memory [3]
    I_STZ = 0x34,  // Move Z register to memory [3]
    I_LMA = 0x3A,  // Move memory to Accumulator [3]
    I_LMAM = 0x3B, // Move memory at High and Low to Accumulator [1]
    I_LMX = 0x3C,  // Move memory to X register [3]
    I_LMY = 0x3D,  // Move memory to Y register [3]
    I_LMZ = 0x3E,  // Move memory to Z register [3]
    I_PHA = 0x40,  // Push Accumulator on stack [1]
    I_PHX = 0x42,  // Push X register on stack [1]
    I_PHY = 0x43,  // Push Y register on stack [1]
    I_PHZ = 0x44,  // Push Z register on stack [1]
    I_PPA = 0x4A,  // Pop Accumulator from stack [1]
    I_PPX = 0x4C,  // Pop X register from stack [1]
    I_PPY = 0x4D,  // Pop Y register from stack [1]
    I_PPZ = 0x4E,  // Pop Z register from stack [1]
    I_SWA = 0x50,  // Switch BROM1 to constant [2]
    I_SWB = 0x5A,  // Switch BROM2 to constant [2]
    I_ADA = 0x60,  // Add Accumulator to Accumulator [1]
    I_ADX = 0x61,  // Add X register to Accumulator [1]
    I_ADY = 0x62,  // Add Y register to Accumulator [1]
    I_ADZ = 0x63,  // Add Z register to Accumulator [1]
    I_SBA = 0x6A,  // Substract Accumulator from Accumulator [1]
    I_SBX = 0x6B,  // Substract X register from Accumulator [1]
    I_SBY = 0x6C,  // Substract Y register from Accumulator [1]
    I_SBZ = 0x6D,  // Substract Z register from Accumulator [1]
    I_ANX = 0x70,  // AND on X register and Accumulator to Accumulator [1]
    I_ANY = 0x71,  // AND on Y register and Accumulator to Accumulator [1]
    I_ANZ = 0x72,  // AND on Z register and Accumulator to Accumulator [1]
    I_ORX = 0x80,  // OR on X register and Accumulator to Accumulator [1]
    I_ORY = 0x81,  // OR on Y register and Accumulator to Accumulator [1]
    I_ORZ = 0x82,  // OR on Z register and Accumulator to Accumulator [1]
    I_XRX = 0x8A,  // XOR on X register and Accumulator to Accumulator [1]
    I_XRY = 0x8B,  // XOR on Y register and Accumulator to Accumulator [1]
    I_XRZ = 0x8C,  // XOR on Z register and Accumulator to Accumulator [1]
    I_SLX = 0x90,  // Shift bit left on X register to Accumulator [1]
    I_SLY = 0x91,  // Shift bit left on Y register to Accumulator [1]
    I_SLZ = 0x92,  // Shift bit left on Z register to Accumulator [1]
    I_SRX = 0x9A,  // Shift bit right on X register to Accumulator [1]
    I_SRY = 0x9B,  // Shift bit right on Y register to Accumulator [1]
    I_SRZ = 0x9C,  // Shift bit right on Z register to Accumulator [1]
    I_INM = 0xA0,  // Increment High and Low [1]
    I_INX = 0xA1,  // Increment X register [1]
    I_INY = 0xA2,  // Increment Y register [1]
    I_INZ = 0xA3,  // Increment Z register [1]
    I_DEM = 0xAA,  // Decrement High and Low [1]
    I_DEX = 0xAB,  // Decrement X register [1]
    I_DEY = 0xAC,  // Decrement Y register [1]
    I_DEZ = 0xAD,  // Decrement Z register [1]
    I_CPX = 0xB0,  // Compare X register and register, set CMP register [2]
    I_CPY = 0xB1,  // Compare Y register and register, set CMP register [2]
    I_CPZ = 0xB2,  // Compare Z register and register, set CMP register [2]
    I_JMP = 0xC0,  // Jump to memory address [3]
    I_JNE = 0xC1,  // Jump to memory address if CMP is not equal [3]
    I_JB = 0xC2,   // Jump to memory address if CMP is below [3]
    I_JE = 0xC3,   // Jump to memory address if CMP is equal [3]
    I_JA = 0xC4,   // Jump to memory address if CMP is above [3]
    I_CALL = 0xD0, // Jumps to subroutine address [3]
    I_RET = 0xDA,  // Returns from subroutine [1]
};

void NOP()
{
}

void LDA(uint8_t Constant1)
{
    Register[0] = Constant1;
}

void LDC(uint8_t Constant1)
{
    Register[1] = Constant1;
}

void LDH(uint8_t Constant1)
{
    Register[2] = Constant1;
}

void LDL(uint8_t Constant1)
{
    Register[3] = Constant1;
}

void LDM(uint8_t Constant1, uint8_t Constant2)
{
    Register[2] = Constant1;
    Register[3] = Constant2;
}

void LDS(uint8_t Constant1)
{
    Register[4] = Constant1;
}

void LDX(uint8_t Constant1)
{
    Register[5] = Constant1;
}

void LDY(uint8_t Constant1)
{
    Register[6] = Constant1;
}

void LDZ(uint8_t Constant1)
{
    Register[7] = Constant1;
}

void LRA(uint8_t Register1)
{
    Register[0] = Register[Register1];
}

void LRC(uint8_t Register1)
{
    Register[1] = Register[Register1];
}

void LRH(uint8_t Register1)
{
    Register[2] = Register[Register1];
}

void LRL(uint8_t Register1)
{
    Register[3] = Register[Register1];
}

void LRS(uint8_t Register1)
{
    Register[4] = Register[Register1];
}

void LRX(uint8_t Register1)
{
    Register[5] = Register[Register1];
}

void LRY(uint8_t Register1)
{
    Register[6] = Register[Register1];
}

void LRZ(uint8_t Register1)
{
    Register[7] = Register[Register1];
}

void STA(uint16_t MemoryAddress1)
{
    Memory.Write(MemoryAddress1, Register[0]);
}

void STAM()
{
    uint8_t MemoryAddressBytes[2];
    MemoryAddressBytes[0] = Register[2];
    MemoryAddressBytes[1] = Register[3];
    Memory.Write(U8toU16(MemoryAddressBytes), Register[0]);
}

void STX(uint16_t MemoryAddress1)
{
    Memory.Write(MemoryAddress1, Register[5]);
}

void STY(uint16_t MemoryAddress1)
{
    Memory.Write(MemoryAddress1, Register[6]);
}

void STZ(uint16_t MemoryAddress1)
{
    Memory.Write(MemoryAddress1, Register[7]);
}

void LMA(uint16_t MemoryAddress1)
{
    Register[0] = Memory.Read(MemoryAddress1);
}

void LMAM()
{
    uint8_t MemoryAddressBytes[2];
    MemoryAddressBytes[0] = Register[2];
    MemoryAddressBytes[1] = Register[3];
    Register[0] = Memory.Read(U8toU16(MemoryAddressBytes));
}

void LMX(uint16_t MemoryAddress1)
{
    Register[5] = Memory.Read(MemoryAddress1);
}

void LMY(uint16_t MemoryAddress1)
{
    Register[6] = Memory.Read(MemoryAddress1);
}

void LMZ(uint16_t MemoryAddress1)
{
    Register[7] = Memory.Read(MemoryAddress1);
}

void PHA()
{
    if (Register[4] + STACK_START <= STACK_START)
    {
        std::cerr << "Error: Stack overflow [" << std::hex << std::setw(4) << std::setfill('0') << Register[4] + STACK_START << "], press any key to ignore";
        std::cin.get();
        return;
    }
    Memory.Write(--Register[4] + STACK_START, Register[0]);
}

void PHX()
{
    if (Register[4] + STACK_START <= STACK_START)
    {
        std::cerr << "Error: Stack overflow [" << std::hex << std::setw(4) << std::setfill('0') << Register[4] + STACK_START << "], press any key to ignore";
        std::cin.get();
        return;
    }
    Memory.Write(--Register[4] + STACK_START, Register[5]);
}

void PHY()
{
    if (Register[4] + STACK_START <= STACK_START)
    {
        std::cerr << "Error: Stack overflow [" << std::hex << std::setw(4) << std::setfill('0') << Register[4] + STACK_START << "], press any key to ignore";
        std::cin.get();
        return;
    }
    Memory.Write(--Register[4] + STACK_START, Register[6]);
}

void PHZ()
{
    if (Register[4] + STACK_START <= STACK_START)
    {
        std::cerr << "Error: Stack overflow [" << std::hex << std::setw(4) << std::setfill('0') << Register[4] + STACK_START << "], press any key to ignore";
        std::cin.get();
        return;
    }
    Memory.Write(--Register[4] + STACK_START, Register[7]);
}

void PPA()
{
    if (Register[4] + STACK_START >= STACK_END)
    {
        std::cerr << "Error: Stack underflow [" << std::hex << std::setw(4) << std::setfill('0') << Register[4] + STACK_START << "], press any key to ignore";
        std::cin.get();
        return;
    }
    Register[0] = Memory.Read(Register[4]++ + STACK_START);
}

void PPX()
{
    if (Register[4] + STACK_START >= STACK_END)
    {
        std::cerr << "Error: Stack underflow [" << std::hex << std::setw(4) << std::setfill('0') << Register[4] + STACK_START << "], press any key to ignore";
        std::cin.get();
        return;
    }
    Register[5] = Memory.Read(Register[4]++ + STACK_START);
}

void PPY()
{
    if (Register[4] + STACK_START >= STACK_END)
    {
        std::cerr << "Error: Stack underflow [" << std::hex << std::setw(4) << std::setfill('0') << Register[4] + STACK_START << "], press any key to ignore";
        std::cin.get();
        return;
    }
    Register[6] = Memory.Read(Register[4]++ + STACK_START);
}

void PPZ()
{
    if (Register[4] + STACK_START >= STACK_END)
    {
        std::cerr << "Error: Stack underflow [" << std::hex << std::setw(4) << std::setfill('0') << Register[4] + STACK_START << "], press any key to ignore";
        std::cin.get();
        return;
    }
    Register[7] = Memory.Read(Register[4]++ + STACK_START);
}

void SWA(uint8_t Constant1)
{
    Cartridge.BankSwitch1(Constant1);
}

void SWB(uint8_t Constant1)
{
    Cartridge.BankSwitch2(Constant1);
}

void ADA()
{
    Register[0] += Register[0];
}

void ADX()
{
    Register[0] += Register[5];
}

void ADY()
{
    Register[0] += Register[6];
}

void ADZ()
{
    Register[0] += Register[7];
}

void SBA()
{
    Register[0] -= Register[0];
}

void SBX()
{
    Register[0] -= Register[5];
}

void SBY()
{
    Register[0] -= Register[6];
}

void SBZ()
{
    Register[0] -= Register[7];
}

void ANX()
{
    Register[0] &= Register[5];
}

void ANY()
{
    Register[0] &= Register[6];
}

void ANZ()
{
    Register[0] &= Register[7];
}

void ORX()
{
    Register[0] |= Register[5];
}

void ORY()
{
    Register[0] |= Register[6];
}

void ORZ()
{
    Register[0] |= Register[7];
}

void XRX()
{
    Register[0] ^= Register[5];
}

void XRY()
{
    Register[0] ^= Register[6];
}

void XRZ()
{
    Register[0] ^= Register[7];
}

void SLX()
{
    Register[0] = Register[5] << 1;
}

void SLY()
{
    Register[0] = Register[6] << 1;
}

void SLZ()
{
    Register[0] = Register[7] << 1;
}

void SRX()
{
    Register[0] = Register[5] >> 1;
}

void SRY()
{
    Register[0] = Register[6] >> 1;
}

void SRZ()
{
    Register[0] = Register[7] >> 1;
}

void INM()
{
    uint8_t NumberBytes[2];
    NumberBytes[0] = Register[2];
    NumberBytes[1] = Register[3];
    U16toU8(U8toU16(NumberBytes) + 1, NumberBytes);
    Register[2] = NumberBytes[0];
    Register[3] = NumberBytes[1];
}

void INX()
{
    Register[5]++;
}

void INY()
{
    Register[6]++;
}

void INZ()
{
    Register[7]++;
}

void DEM()
{
    uint8_t NumberBytes[2];
    NumberBytes[0] = Register[2];
    NumberBytes[1] = Register[3];
    U16toU8(U8toU16(NumberBytes) - 1, NumberBytes);
    Register[2] = NumberBytes[0];
    Register[3] = NumberBytes[1];
}

void DEX()
{
    Register[5]--;
}

void DEY()
{
    Register[6]--;
}

void DEZ()
{
    Register[7]--;
}

void CPX(uint8_t Register1)
{
    if (Register[5] != Register[Register1])
    {
        Register[1] = 0;
    }
    else if (Register[5] > Register[Register1])
    {
        Register[1] = 1;
    }
    else if (Register[5] == Register[Register1])
    {
        Register[1] = 2;
    }
    else if (Register[5] < Register[Register1])
    {
        Register[1] = 3;
    }
}

void CPY(uint8_t Register1)
{
    if (Register[6] != Register[Register1])
    {
        Register[1] = 0;
    }
    else if (Register[6] > Register[Register1])
    {
        Register[1] = 1;
    }
    else if (Register[6] == Register[Register1])
    {
        Register[1] = 2;
    }
    else if (Register[6] < Register[Register1])
    {
        Register[1] = 3;
    }
}

void CPZ(uint8_t Register1)
{
    if (Register[7] != Register[Register1])
    {
        Register[1] = 0;
    }
    else if (Register[7] > Register[Register1])
    {
        Register[1] = 1;
    }
    else if (Register[7] == Register[Register1])
    {
        Register[1] = 2;
    }
    else if (Register[7] < Register[Register1])
    {
        Register[1] = 3;
    }
}

void JMP(uint16_t MemoryAddress1)
{
    ProgramCounter = MemoryAddress1;
}

void JNE(uint16_t MemoryAddress1)
{
    if (Register[1] == 0)
    {
        JMP(MemoryAddress1);
    }
    else
    {
        ProgramCounter += 3;
    }
}

void JB(uint16_t MemoryAddress1)
{
    if (Register[1] == 1)
    {
        JMP(MemoryAddress1);
    }
    else
    {
        ProgramCounter += 3;
    }
}

void JE(uint16_t MemoryAddress1)
{
    if (Register[1] == 2)
    {
        JMP(MemoryAddress1);
    }
    else
    {
        ProgramCounter += 3;
    }
}

void JA(uint16_t MemoryAddress1)
{
    if (Register[1] == 3)
    {
        JMP(MemoryAddress1);
    }
    else
    {
        ProgramCounter += 3;
    }
}

void CALL(uint16_t MemoryAddress1)
{
    ProgramCounter += 2;
    uint8_t ProgramCounterBytes[2];
    U16toU8(ProgramCounter, ProgramCounterBytes);
    for (uint8_t i = 0; i < 2; i++)
    {
        if (Register[4] + STACK_START <= STACK_START)
        {
            std::cerr << "Error: Stack overflow [" << std::hex << std::setw(4) << std::setfill('0') << Register[4] + STACK_START << "], press any key to ignore";
            std::cin.get();
            return;
        }
        Memory.Write(--Register[4] + STACK_START, ProgramCounterBytes[i]);
    }
    JMP(MemoryAddress1);
}

void RET()
{
    uint8_t ReturnAddressBytes[2];
    for (uint8_t i = 0; i < 2; i++)
    {
        if (Register[4] + STACK_START >= STACK_END)
        {
            std::cerr << "Error: Stack underflow [" << std::hex << std::setw(4) << std::setfill('0') << Register[4] + STACK_START << "], press any key to ignore";
            std::cin.get();
            return;
        }
        ReturnAddressBytes[1 - i] = Memory.Read(Register[4]++ + STACK_START);
    }
    ProgramCounter = U8toU16(ReturnAddressBytes);
}

void Process()
{
    // std::cout << "PC: [" << std::hex << std::setw(4) << std::setfill('0') << ProgramCounter << "] [" << (uint16_t)Memory.Read(ProgramCounter) << "]" << std::endl;

    if (ProgramCounter > SROM_END)
    {
        ProgramCounter = ROM_START;
    }

    uint8_t MemoryAddressBytes[2];

    switch (Memory.Read(ProgramCounter))
    {
    case I_NOP:
        NOP();
        ProgramCounter += 1;
        break;
    case I_LDA:
        LDA(Memory.Read(ProgramCounter + 1));
        ProgramCounter += 2;
        break;
    case I_LDC:
        LDC(Memory.Read(ProgramCounter + 1));
        ProgramCounter += 2;
        break;
    case I_LDH:
        LDH(Memory.Read(ProgramCounter + 1));
        ProgramCounter += 2;
        break;
    case I_LDL:
        LDL(Memory.Read(ProgramCounter + 1));
        ProgramCounter += 2;
        break;
    case I_LDM:
        LDM(Memory.Read(ProgramCounter + 1), Memory.Read(ProgramCounter + 2));
        ProgramCounter += 3;
        break;
    case I_LDS:
        LDS(Memory.Read(ProgramCounter + 1));
        ProgramCounter += 2;
        break;
    case I_LDX:
        LDX(Memory.Read(ProgramCounter + 1));
        ProgramCounter += 2;
        break;
    case I_LDY:
        LDY(Memory.Read(ProgramCounter + 1));
        ProgramCounter += 2;
        break;
    case I_LDZ:
        LDZ(Memory.Read(ProgramCounter + 1));
        ProgramCounter += 2;
        break;
    case I_LRA:
        LRA(Memory.Read(ProgramCounter + 1));
        ProgramCounter += 2;
        break;
    case I_LRC:
        LRC(Memory.Read(ProgramCounter + 1));
        ProgramCounter += 2;
        break;
    case I_LRH:
        LRH(Memory.Read(ProgramCounter + 1));
        ProgramCounter += 2;
        break;
    case I_LRL:
        LRL(Memory.Read(ProgramCounter + 1));
        ProgramCounter += 2;
        break;
    case I_LRS:
        LRS(Memory.Read(ProgramCounter + 1));
        ProgramCounter += 2;
        break;
    case I_LRX:
        LRX(Memory.Read(ProgramCounter + 1));
        ProgramCounter += 2;
        break;
    case I_LRY:
        LRY(Memory.Read(ProgramCounter + 1));
        ProgramCounter += 2;
        break;
    case I_LRZ:
        LRZ(Memory.Read(ProgramCounter + 1));
        ProgramCounter += 2;
        break;
    case I_STA:
        MemoryAddressBytes[0] = Memory.Read(ProgramCounter + 1);
        MemoryAddressBytes[1] = Memory.Read(ProgramCounter + 2);
        STA(U8toU16(MemoryAddressBytes));
        ProgramCounter += 3;
        break;
    case I_STAM:
        STAM();
        ProgramCounter += 1;
        break;
    case I_STX:
        MemoryAddressBytes[0] = Memory.Read(ProgramCounter + 1);
        MemoryAddressBytes[1] = Memory.Read(ProgramCounter + 2);
        STX(U8toU16(MemoryAddressBytes));
        ProgramCounter += 3;
        break;
    case I_STY:
        MemoryAddressBytes[0] = Memory.Read(ProgramCounter + 1);
        MemoryAddressBytes[1] = Memory.Read(ProgramCounter + 2);
        STY(U8toU16(MemoryAddressBytes));
        ProgramCounter += 3;
        break;
    case I_STZ:
        MemoryAddressBytes[0] = Memory.Read(ProgramCounter + 1);
        MemoryAddressBytes[1] = Memory.Read(ProgramCounter + 2);
        STZ(U8toU16(MemoryAddressBytes));
        ProgramCounter += 3;
        break;
    case I_LMA:
        MemoryAddressBytes[0] = Memory.Read(ProgramCounter + 1);
        MemoryAddressBytes[1] = Memory.Read(ProgramCounter + 2);
        LMA(U8toU16(MemoryAddressBytes));
        ProgramCounter += 3;
        break;
    case I_LMAM:
        LMAM();
        ProgramCounter += 1;
        break;
    case I_LMX:
        MemoryAddressBytes[0] = Memory.Read(ProgramCounter + 1);
        MemoryAddressBytes[1] = Memory.Read(ProgramCounter + 2);
        LMX(U8toU16(MemoryAddressBytes));
        ProgramCounter += 3;
        break;
    case I_LMY:
        MemoryAddressBytes[0] = Memory.Read(ProgramCounter + 1);
        MemoryAddressBytes[1] = Memory.Read(ProgramCounter + 2);
        LMY(U8toU16(MemoryAddressBytes));
        ProgramCounter += 3;
        break;
    case I_LMZ:
        MemoryAddressBytes[0] = Memory.Read(ProgramCounter + 1);
        MemoryAddressBytes[1] = Memory.Read(ProgramCounter + 2);
        LMZ(U8toU16(MemoryAddressBytes));
        ProgramCounter += 3;
        break;
    case I_PHA:
        PHA();
        ProgramCounter += 1;
        break;
    case I_PHX:
        PHX();
        ProgramCounter += 1;
        break;
    case I_PHY:
        PHY();
        ProgramCounter += 1;
        break;
    case I_PHZ:
        PHZ();
        ProgramCounter += 1;
        break;
    case I_PPA:
        PPA();
        ProgramCounter += 1;
        break;
    case I_PPX:
        PPX();
        ProgramCounter += 1;
        break;
    case I_PPY:
        PPY();
        ProgramCounter += 1;
        break;
    case I_PPZ:
        PPZ();
        ProgramCounter += 1;
        break;
    case I_SWA:
        SWB(Memory.Read(ProgramCounter + 1));
        ProgramCounter += 2;
        break;
    case I_SWB:
        SWB(Memory.Read(ProgramCounter + 1));
        ProgramCounter += 2;
        break;
    case I_ADA:
        ADA();
        ProgramCounter += 1;
        break;
    case I_ADX:
        ADX();
        ProgramCounter += 1;
        break;
    case I_ADY:
        ADY();
        ProgramCounter += 1;
        break;
    case I_ADZ:
        ADZ();
        ProgramCounter += 1;
        break;
    case I_SBA:
        SBA();
        ProgramCounter += 1;
        break;
    case I_SBX:
        SBX();
        ProgramCounter += 1;
        break;
    case I_SBY:
        SBY();
        ProgramCounter += 1;
        break;
    case I_SBZ:
        SBZ();
        ProgramCounter += 1;
        break;
    case I_ANX:
        ANX();
        ProgramCounter += 1;
        break;
    case I_ANY:
        ANY();
        ProgramCounter += 1;
        break;
    case I_ANZ:
        ANZ();
        ProgramCounter += 1;
        break;
    case I_ORX:
        ORX();
        ProgramCounter += 1;
        break;
    case I_ORY:
        ORY();
        ProgramCounter += 1;
        break;
    case I_ORZ:
        ORZ();
        ProgramCounter += 1;
        break;
    case I_XRX:
        XRX();
        ProgramCounter += 1;
        break;
    case I_XRY:
        XRY();
        ProgramCounter += 1;
        break;
    case I_XRZ:
        XRZ();
        ProgramCounter += 1;
        break;
    case I_SLX:
        SLX();
        ProgramCounter += 1;
        break;
    case I_SLY:
        SLY();
        ProgramCounter += 1;
        break;
    case I_SLZ:
        SLZ();
        ProgramCounter += 1;
        break;
    case I_SRX:
        SRX();
        ProgramCounter += 1;
        break;
    case I_SRY:
        SRY();
        ProgramCounter += 1;
        break;
    case I_SRZ:
        SRZ();
        ProgramCounter += 1;
        break;
    case I_INM:
        INM();
        ProgramCounter += 1;
        break;
    case I_INX:
        INX();
        ProgramCounter += 1;
        break;
    case I_INY:
        INY();
        ProgramCounter += 1;
        break;
    case I_INZ:
        INZ();
        ProgramCounter += 1;
        break;
    case I_DEM:
        DEM();
        ProgramCounter += 1;
        break;
    case I_DEX:
        DEX();
        ProgramCounter += 1;
        break;
    case I_DEY:
        DEY();
        ProgramCounter += 1;
        break;
    case I_DEZ:
        DEZ();
        ProgramCounter += 1;
        break;
    case I_CPX:
        CPX(Memory.Read(ProgramCounter + 1));
        ProgramCounter += 2;
        break;
    case I_CPY:
        CPY(Memory.Read(ProgramCounter + 1));
        ProgramCounter += 2;
        break;
    case I_CPZ:
        CPZ(Memory.Read(ProgramCounter + 1));
        ProgramCounter += 2;
        break;
    case I_JMP:
        MemoryAddressBytes[0] = Memory.Read(ProgramCounter + 1);
        MemoryAddressBytes[1] = Memory.Read(ProgramCounter + 2);
        JMP(U8toU16(MemoryAddressBytes));
        break;
    case I_JNE:
        MemoryAddressBytes[0] = Memory.Read(ProgramCounter + 1);
        MemoryAddressBytes[1] = Memory.Read(ProgramCounter + 2);
        JNE(U8toU16(MemoryAddressBytes));
        break;
    case I_JB:
        MemoryAddressBytes[0] = Memory.Read(ProgramCounter + 1);
        MemoryAddressBytes[1] = Memory.Read(ProgramCounter + 2);
        JB(U8toU16(MemoryAddressBytes));
        break;
    case I_JE:
        MemoryAddressBytes[0] = Memory.Read(ProgramCounter + 1);
        MemoryAddressBytes[1] = Memory.Read(ProgramCounter + 2);
        JE(U8toU16(MemoryAddressBytes));
        break;
    case I_JA:
        MemoryAddressBytes[0] = Memory.Read(ProgramCounter + 1);
        MemoryAddressBytes[1] = Memory.Read(ProgramCounter + 2);
        JA(U8toU16(MemoryAddressBytes));
        break;
    case I_CALL:
        MemoryAddressBytes[0] = Memory.Read(ProgramCounter + 1);
        MemoryAddressBytes[1] = Memory.Read(ProgramCounter + 2);
        CALL(U8toU16(MemoryAddressBytes));
        break;
    case I_RET:
        RET();
        ProgramCounter += 1;
        break;
    default:
        std::cerr << "Paused: Unknown instruction [" << std::hex << std::setw(4) << std::setfill('0') << ProgramCounter << "] [" << (uint16_t)Memory.Read(ProgramCounter) << "], press any keys to ignore";
        std::cin.get();
        ProgramCounter += 1;
        break;
    }
}