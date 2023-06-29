#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <cstring>
#include <cstdint>
#include <vector>
#include <map>
#include <unordered_map>
#include "C:\Dev\raylib\raylib.h"
#include "C:\Dev\raylib\raymath.h"

#include "Audio.hpp"
#include "Cartridge.hpp"
#include "Compiler.hpp"
#include "Graphics.hpp"
#include "Input.hpp"
#include "Memory.hpp"
#include "Other.hpp"
#include "Processor.hpp"
#include "Tools.hpp"

#define VIKE_MAJOR 0
#define VIKE_MINOR 0
#define VIKE_FIX 0

std::string Filename;

int main(int argc, char *argv[])
{
    std::string Title = "Vike " + std::to_string(VIKE_MAJOR) + "." + std::to_string(VIKE_MINOR) + "." + std::to_string(VIKE_FIX) + " by Veress Bence Gyula " + __DATE__;

    std::vector<std::pair<std::string, uint8_t>> ArgumentPriority;

    uint8_t WindowScale = 1;

    if (argc < 2)
    {
        return false;
    }
    else if (argc >= 2)
    {
        for (int i = 1; i < argc; i++)
        {
            if (IsFileExtension(argv[i], ".vike"))
            {
                ArgumentPriority.push_back({argv[i], 1});
            }
            if (IsFileExtension(argv[i], ".vsm"))
            {
                ArgumentPriority.push_back({argv[i], 2});
            }
            if (std::string(argv[i]).substr(0, 3) == "ws:")
            {
                ArgumentPriority.push_back({argv[i], 0});
            }
        }
    }

    std::sort(ArgumentPriority.begin(), ArgumentPriority.end(), [](const std::pair<std::string, uint8_t> &a, const std::pair<std::string, uint8_t> &b)
              { return a.second > b.second; });

    for (auto &Argument : ArgumentPriority)
    {
        if (IsFileExtension(Argument.first.c_str(), ".vike"))
        {
            Filename = Argument.first;
            Cartridge.Load(Filename);
        }
        if (IsFileExtension(Argument.first.c_str(), ".vsm"))
        {
            return Compile(Argument.first);
        }
        if (Argument.first.substr(0, 3) == "ws:")
        {
            WindowScale = std::stoi(Argument.first.substr(3));
        }
    }

    std::cout << Title << " - Loading..." << std::endl;
    InitWindow(256 * WindowScale, 192 * WindowScale, Title.c_str());
    InitAudioDevice();

    Sound SquareSound1 = LoadSoundFromWave(SquareWave(440, 1.0f, 0.1f));
    Sound SquareSound2 = LoadSoundFromWave(SquareWave(440, 1.0f, 0.1f));
    Sound SquareSound3 = LoadSoundFromWave(SquareWave(440, 1.0f, 0.1f));
    Sound SawtoothSound1 = LoadSoundFromWave(SawtoothWave(440, 1.0f, 0.1f));
    Sound SawtoothSound2 = LoadSoundFromWave(SawtoothWave(440, 1.0f, 0.1f));
    Sound SineSound = LoadSoundFromWave(SineWave(440, 1.0f, 0.1f));
    Sound NoiseSound = LoadSoundFromWave(NoiseWave(1.0f, 0.1f));

    Image Screen = GenImageColor(256, 192, BLACK);
    Texture ScreenShow = LoadTextureFromImage(Screen);

    std::cout << std::endl;

    while (!WindowShouldClose())
    {
        Play(SquareSound1, SquareSound2, SquareSound3, SawtoothSound1, SawtoothSound2, SineSound, NoiseSound);
        DrawScreen(WindowScale, Screen, ScreenShow);
        ProcessInput();
        Memory.FindExternal();
        Process();
        ManageTools(WindowScale);
    }

    std::cout << "\nPress any key to close Vike";
    std::cin.get();
    std::cout << Title << "\nUnloading...\n";

    UnloadTexture(ScreenShow);
    UnloadImage(Screen);

    UnloadSound(NoiseSound);
    UnloadSound(SineSound);
    UnloadSound(SawtoothSound2);
    UnloadSound(SawtoothSound1);
    UnloadSound(SquareSound3);
    UnloadSound(SquareSound2);
    UnloadSound(SquareSound1);

    CloseAudioDevice();

    CloseWindow();
    return 0;
}
