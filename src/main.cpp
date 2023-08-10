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

    uint8_t WindowScale = 1;

    if (IsFileExtension(argv[1], ".vsm"))
    {
        return Compile(argv[1]);
    }
    if (IsFileExtension(argv[1], ".vike"))
    {
        Filename = argv[1];
        Cartridge.Load(Filename);
    }
    for (uint8_t i = 2; i < argc; i++)
    {
        if (std::strncmp(argv[i], "ws:", 3) == 0)
        {
            WindowScale = std::stoi(argv[i] + 3);
        }
    }

    std::cout << Title << " - Loading..." << std::endl;
    InitWindow(256 * WindowScale, 192 * WindowScale, Title.c_str());

    Image Screen = GenImageColor(256, 192, BLACK);
    Texture ScreenShow = LoadTextureFromImage(Screen);

    std::cout << std::endl;

    while (!WindowShouldClose())
    {
        Memory.FindExternal();
        ProcessInput();
        Process();
        // ManageTools(WindowScale);
        DrawScreen(WindowScale, Screen, ScreenShow);
    }

    std::cout << "\nPress any key to close Vike";
    std::cin.get();
    std::cout << Title << "\nUnloading...\n";

    UnloadTexture(ScreenShow);
    UnloadImage(Screen);

    CloseWindow();
    return 0;
}
