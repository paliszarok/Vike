#pragma once

void ProcessInput()
{
    if (IsKeyPressed(KEY_COMMA))
    {
        Memory.DumpLoad();
    }
    if (IsKeyPressed(KEY_PERIOD))
    {
        Memory.DumpSave();
    }

    Memory.SROM[INPUT_BUTTON_UP - SROM_START] = IsKeyDown(KEY_UP);
    Memory.SROM[INPUT_BUTTON_DOWN - SROM_START] = IsKeyDown(KEY_DOWN);
    Memory.SROM[INPUT_BUTTON_LEFT - SROM_START] = IsKeyDown(KEY_LEFT);
    Memory.SROM[INPUT_BUTTON_RIGHT - SROM_START] = IsKeyDown(KEY_RIGHT);
    Memory.SROM[INPUT_BUTTON_A - SROM_START] = IsKeyDown(KEY_S);
    Memory.SROM[INPUT_BUTTON_B - SROM_START] = IsKeyDown(KEY_A);
    Memory.SROM[INPUT_BUTTON_L - SROM_START] = IsKeyDown(KEY_Q);
    Memory.SROM[INPUT_BUTTON_R - SROM_START] = IsKeyDown(KEY_W);
    Memory.SROM[INPUT_BUTTON_SELECT - SROM_START] = IsKeyDown(KEY_SPACE);
    Memory.SROM[INPUT_BUTTON_START - SROM_START] = IsKeyDown(KEY_ENTER);
}