#include <iostream>

#include "raylib.h"
#include "raymath.h"

#define VIKE_MAJOR 0
#define VIKE_MINOR 0
#define VIKE_FIX 0

int main(int argc, char *argv[])
{
    std::string Title = "Vike " + std::to_string(VIKE_MAJOR) + "." + std::to_string(VIKE_MINOR) + "." + std::to_string(VIKE_FIX) + " by Veress Bence Gyula [KROMYTH]";
    std::cout << Title << std::endl;

    return 0;
}