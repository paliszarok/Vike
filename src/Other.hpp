#pragma once

uint16_t U8toU16(uint8_t *bytes)
{
    uint16_t value = static_cast<uint16_t>(bytes[0]) << 8 |
                     static_cast<uint16_t>(bytes[1]);
    return value;
}

void U16toU8(uint16_t value, uint8_t *bytes)
{
    bytes[0] = static_cast<uint8_t>((value >> 8) & 0xFF);
    bytes[1] = static_cast<uint8_t>(value & 0xFF);
}

void U24toU8(uint32_t value, uint8_t *bytes)
{
    bytes[0] = static_cast<uint8_t>((value >> 16) & 0xFF);
    bytes[1] = static_cast<uint8_t>((value >> 8) & 0xFF);
    bytes[2] = static_cast<uint8_t>(value & 0xFF);
}

void U32toU8(uint32_t value, uint8_t *bytes)
{
    bytes[0] = static_cast<uint8_t>((value >> 24) & 0xFF);
    bytes[1] = static_cast<uint8_t>((value >> 16) & 0xFF);
    bytes[2] = static_cast<uint8_t>((value >> 8) & 0xFF);
    bytes[3] = static_cast<uint8_t>(value & 0xFF);
}