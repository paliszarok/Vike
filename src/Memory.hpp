#pragma once

#define ROM_START 0x0000
#define ROM_END 0x1FFF
#define BROM1_START 0x2000
#define BROM1_END 0x3FFF
#define BROM2_START 0x4000
#define BROM2_END 0x5FFF
#define VRAM_START 0x6000
#define VRAM_END 0xBFFF
#define RAM_START 0xC000
#define RAM_END 0xF7FF
#define STACK_START 0xF800
#define STACK_END 0xF8FF
#define EXTERNAL_START 0xF900
#define EXTERNAL_END 0xF9FF
#define SROM_START 0xFA00
#define SROM_END 0xFA0F
#define SRAM_START 0xFA10
#define SRAM_END 0xFA1F

#define INPUT_BUTTON_UP 0xFA00
#define INPUT_BUTTON_DOWN 0xFA01
#define INPUT_BUTTON_LEFT 0xFA02
#define INPUT_BUTTON_RIGHT 0xFA03
#define INPUT_BUTTON_A 0xFA04
#define INPUT_BUTTON_B 0xFA05
#define INPUT_BUTTON_L 0xFA06
#define INPUT_BUTTON_R 0xFA07
#define INPUT_BUTTON_SELECT 0xFA08
#define INPUT_BUTTON_START 0xFA09
#define EXTERNAL_CARTRIDGE 0xFA0A
#define AUDIO_POINTER_HIGH 0xFA10
#define AUDIO_POINTER_LOW 0xFA11
#define AUDIO_STATE 0xFA12

extern std::string Filename;

struct Memory
{
    uint8_t ROM[0x2000];
    uint8_t BROM1[0x2000];
    uint8_t BROM2[0x2000];
    uint8_t VRAM[0x6000];
    uint8_t RAM[0x3800];
    uint8_t Stack[0x100];
    uint8_t SROM[0x10];
    uint8_t SRAM[0x10];

    uint8_t Read(uint16_t Address)
    {
        if (Address >= ROM_START && Address <= ROM_END)
        {
            return ROM[Address - ROM_START];
        }
        else if (Address >= BROM1_START && Address <= BROM1_END)
        {
            return BROM1[Address - BROM1_START];
        }
        else if (Address >= BROM2_START && Address <= BROM2_END)
        {
            return BROM2[Address - BROM2_START];
        }
        else if (Address >= VRAM_START && Address <= VRAM_END)
        {
            return VRAM[Address - VRAM_START];
        }
        else if (Address >= RAM_START && Address <= RAM_END)
        {
            return RAM[Address - RAM_START];
        }
        else if (Address >= STACK_START && Address <= STACK_END)
        {
            return Stack[Address - STACK_START];
        }
        else if (Address >= EXTERNAL_START && Address <= EXTERNAL_END)
        {
            std::ifstream File("ext.bin", std::ios::binary);

            if (File.is_open())
            {
                File.seekg(Address - EXTERNAL_START);
                uint8_t Data;
                File.read(reinterpret_cast<char *>(&Data), sizeof(Data));
                File.close();

                return Data;
            }

            return 0;
        }
        else if (Address >= SROM_START && Address <= SROM_END)
        {
            return SROM[Address - SROM_START];
        }
        else if (Address >= SRAM_START && Address <= SRAM_END)
        {
            return SRAM[Address - SRAM_START];
        }
        else
        {
            std::cerr << "Error (Read): Address out of range [" << std::hex << std::setw(4) << std::setfill('0') << Address << "]" << std::endl;
            return 0;
        }
    }

    void Write(uint16_t Address, uint8_t Data)
    {
        if (Address >= ROM_START && Address <= ROM_END)
        {
            std::cerr << "Error (Write): Cannot write to ROM [" << std::hex << std::setw(4) << std::setfill('0') << Address << "]" << std::endl;
            return;
        }
        else if (Address >= BROM1_START && Address <= BROM1_END)
        {
            std::cerr << "Error (Write): Cannot write to BROM1 [" << std::hex << std::setw(4) << std::setfill('0') << Address << "]" << std::endl;
            return;
        }
        else if (Address >= BROM2_START && Address <= BROM2_END)
        {
            std::cerr << "Error (Write): Cannot write to BROM2 [" << std::hex << std::setw(4) << std::setfill('0') << Address << "]" << std::endl;
            return;
        }
        else if (Address >= VRAM_START && Address <= VRAM_END)
        {
            VRAM[Address - VRAM_START] = Data;
        }
        else if (Address >= RAM_START && Address <= RAM_END)
        {
            RAM[Address - RAM_START] = Data;
        }
        else if (Address >= STACK_START && Address <= STACK_END)
        {
            Stack[Address - STACK_START] = Data;
        }
        else if (Address >= EXTERNAL_START && Address <= EXTERNAL_END)
        {
            std::fstream File("ext.bin", std::ios::binary | std::ios::in | std::ios::out);

            if (File.is_open())
            {
                File.seekp(Address - EXTERNAL_START);
                File.write(reinterpret_cast<char *>(&Data), sizeof(Data));
                File.close();
            }
        }
        else if (Address >= SROM_START && Address <= SROM_END)
        {
            std::cerr << "Error (Write): Cannot write to SROM [" << std::hex << std::setw(4) << std::setfill('0') << Address << "]" << std::endl;
            return;
        }
        else if (Address >= SRAM_START && Address <= SRAM_END)
        {
            SRAM[Address - SRAM_START] = Data;
        }
        else
        {
            std::cerr << "Error (Write): Address out of range [" << std::hex << std::setw(4) << std::setfill('0') << Address << "]" << std::endl;
            return;
        }
    }

    void FindExternal()
    {
        std::ifstream File("ext.bin", std::ios::binary | std::ios::ate);

        if (File.is_open())
        {
            std::streampos FileSize = File.tellg();

            if (FileSize == 0x100)
            {
                SROM[EXTERNAL_CARTRIDGE - SROM_START] = 1;
            }

            File.close();
        }
        else
        {
            SROM[EXTERNAL_CARTRIDGE - SROM_START] = 0;
        }
    }

    void DumpLoad()
    {
        std::ifstream File("dump.bin", std::ios::binary);
        if (!File.is_open())
        {
            std::cerr << "Error (DumpLoad): Failed to open file for loading" << std::endl;
            return;
        }
        uint8_t Value;
        for (uint16_t Address = 0; Address <= SROM_END && File.read(reinterpret_cast<char *>(&Value), sizeof(Value)); Address++)
        {
            Write(Address, Value);
        }
        File.close();
    }

    void DumpSave()
    {
        std::ofstream File("dump.bin", std::ios::binary);
        if (!File.is_open())
        {
            std::cerr << "Error (DumpSave): Failed to open file for dumping" << std::endl;
            return;
        }
        for (uint16_t Address = 0; Address <= SROM_END; Address++)
        {
            uint8_t Value = Read(Address);
            File.write(reinterpret_cast<const char *>(&Value), sizeof(Value));
        }
        File.close();
    }
} Memory;