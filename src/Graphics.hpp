#pragma once

std::map<uint8_t, Color> Colors{
    {0x0, {0, 0, 0, 255}},
    {0x1, {0, 0, 170, 255}},
    {0x2, {0, 170, 0, 255}},
    {0x3, {0, 170, 170, 255}},
    {0x4, {170, 0, 0, 255}},
    {0x5, {170, 0, 170, 255}},
    {0x6, {170, 85, 0, 255}},
    {0x7, {170, 170, 170, 255}},
    {0x8, {85, 85, 85, 255}},
    {0x9, {85, 85, 255, 255}},
    {0xA, {85, 255, 85, 255}},
    {0xB, {85, 255, 255, 255}},
    {0xC, {255, 85, 85, 255}},
    {0xD, {255, 85, 255, 255}},
    {0xE, {255, 255, 85, 255}},
    {0xF, {255, 255, 255, 255}},
};

void DrawScreen(uint8_t &WindowScale, Image &Screen, Texture &ScreenShow)
{
    for (uint16_t Address = VRAM_START; Address <= VRAM_END; Address++)
    {
        uint8_t X1 = ((Address - VRAM_START) * 2) % 256;
        uint8_t X2 = X1 + 1;
        uint8_t Y = ((Address - VRAM_START) * 2) / 256;

        uint8_t ColorIndex = Memory.VRAM[Address - VRAM_START];
        uint8_t Pixel1 = ColorIndex >> 4;
        uint8_t Pixel2 = ColorIndex & 0x0F;

        Color Color1 = Colors[Pixel1];
        Color Color2 = Colors[Pixel2];

        ImageDrawPixel(&Screen, X1, Y, Color1);
        ImageDrawPixel(&Screen, X2, Y, Color2);
    }
    UpdateTexture(ScreenShow, Screen.data);

    BeginDrawing();
    ClearBackground(BLACK);

    DrawTextureEx(ScreenShow, Vector2Zero(), 0.0f, (int)WindowScale, WHITE);

    DrawFPS(10, 10);
    EndDrawing();
}