#pragma once

bool Tools = false;

enum Tool
{
    Nothing,
    Disassembler,
    MemoryViewer,
    RegisterViewer,
};

Tool CurrentTool = Nothing;

void ManageTools(uint8_t &WindowScale)
{
    if (IsKeyPressed(KEY_BACKSPACE))
    {
        if (!Tools)
        {
            SetWindowSize(256 * WindowScale * 1.5f, 192 * WindowScale);
            Tools = true;
        }
        else
        {
            SetWindowSize(256 * WindowScale, 192 * WindowScale);
            Tools = false;
        }
    }
}