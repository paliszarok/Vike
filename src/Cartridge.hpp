#pragma once

#include "Memory.hpp"

uint8_t Bank1 = 0;
uint8_t Bank2 = 0;

struct Cartridge
{
    std::vector<uint8_t> ROM;
    uint8_t Banks;

    void BankSwitch1(uint8_t BankSwitch)
    {
        if (BankSwitch <= Banks)
        {
            Bank1 = BankSwitch;
            std::size_t Offset = Bank1 * 0x2000;
            std::size_t Elements = std::min(ROM.size() - Offset, static_cast<std::size_t>(0x2000));
            std::memcpy(Memory.BROM1, &ROM[Offset], Elements);
            std::cout << "BankSwitch1: Bank " << static_cast<int>(Bank1) << " switched successfully." << std::endl;
        }
        else
        {
            std::cerr << "Error (BankSwitch1): Invalid bank switch" << std::endl;
        }
    }

    void BankSwitch2(uint8_t BankSwitch)
    {
        if (BankSwitch <= Banks)
        {
            Bank2 = BankSwitch;
            std::size_t Offset = Bank2 * 0x2000;
            std::size_t Elements = std::min(ROM.size() - Offset, static_cast<std::size_t>(0x2000));
            std::memcpy(Memory.BROM2, &ROM[Offset], Elements);
            std::cout << "BankSwitch2: Bank " << static_cast<int>(Bank2) << " switched successfully." << std::endl;
        }
        else
        {
            std::cerr << "Error (BankSwitch2): Invalid bank switch" << std::endl;
        }
    }

    uint8_t CalculateBanks(uint32_t VectorSize)
    {
        if (VectorSize <= 0x2000)
        {
            return 0;
        }
        else
        {
            return static_cast<uint8_t>((VectorSize - 0x2000) / 0x2000);
        }
    }

    void Load(std::string Filename)
    {
        std::ifstream File(Filename, std::ios::binary);
        if (!File)
        {
            std::cerr << "Error (Load): Failed to load file" << std::endl;
            return;
        }

        File.seekg(0, std::ios::end);
        std::streampos FileSize = File.tellg();
        File.seekg(0, std::ios::beg);

        ROM.resize(FileSize);
        File.read(reinterpret_cast<char *>(ROM.data()), FileSize);

        Banks = CalculateBanks(FileSize);
        ROM.resize(0x2000 + 0x2000 * Banks);

        std::memcpy(Memory.ROM, ROM.data(), 0x2000);

        std::cout << "Cartridge loaded successfully!" << std::endl;
    }

    void Create(std::string Filename, std::vector<uint8_t> &Data)
    {
        Banks = CalculateBanks(Data.size());
        Data.resize(0x2000 + 0x2000 * Banks);

        std::ofstream File(Filename, std::ios::binary);
        if (!File)
        {
            std::cerr << "Error (Create): Failed to create file" << std::endl;
            return;
        }

        File.write(reinterpret_cast<const char *>(Data.data()), Data.size());

        std::cout << "Cartridge file created successfully!" << std::endl;
    }
} Cartridge;