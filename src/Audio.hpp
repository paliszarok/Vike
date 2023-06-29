#pragma once

#include "Memory.hpp"
#include "Other.hpp"

#define SAMPLE_RATE 32000

Wave SquareWave(float Frequency, float Duration, float Amplitude)
{
    int SampleCount = (int)(Duration * SAMPLE_RATE);
    float *Data = (float *)malloc(SampleCount * sizeof(float));

    int WaveLength = (int)((float)SAMPLE_RATE / Frequency);
    for (int i = 0; i < SampleCount; i++)
    {
        if (i % WaveLength < WaveLength / 2)
        {
            Data[i] = Amplitude;
        }
        else
        {
            Data[i] = -Amplitude;
        }
    }

    Wave wave = {
        .frameCount = SampleCount,
        .sampleRate = SAMPLE_RATE,
        .sampleSize = 32,
        .channels = 1,
        .data = Data,
    };

    return wave;
}

Wave SawtoothWave(float Frequency, float duration, float Amplitude)
{
    int SampleCount = (int)(duration * SAMPLE_RATE);
    float *Data = (float *)malloc(SampleCount * sizeof(float));

    for (int i = 0; i < SampleCount; i++)
    {
        float t = (float)i / SAMPLE_RATE;
        float value = Amplitude * (2 * (t * Frequency - floor(t * Frequency + 0.5f)));
        Data[i] = value;
    }

    Wave wave = {
        .frameCount = SampleCount,
        .sampleRate = SAMPLE_RATE,
        .sampleSize = 32,
        .channels = 1,
        .data = Data,
    };

    return wave;
}

Wave SineWave(float Frequency, float duration, float Amplitude)
{
    int SampleCount = (int)(duration * SAMPLE_RATE);
    float *Data = (float *)malloc(SampleCount * sizeof(float));

    for (int i = 0; i < SampleCount; i++)
    {
        float t = (float)i / SAMPLE_RATE;
        Data[i] = Amplitude * sin(2 * PI * Frequency * t);
    }

    Wave wave = {
        .frameCount = SampleCount,
        .sampleRate = SAMPLE_RATE,
        .sampleSize = 32,
        .channels = 1,
        .data = Data,
    };

    return wave;
}

Wave NoiseWave(float duration, float Amplitude)
{
    int SampleCount = (int)(duration * SAMPLE_RATE);
    float *Data = (float *)malloc(SampleCount * sizeof(float));

    for (int i = 0; i < SampleCount; i++)
    {
        Data[i] = Amplitude * ((float)rand() / RAND_MAX * 2 - 1);
    }

    Wave wave = {
        .frameCount = SampleCount,
        .sampleRate = SAMPLE_RATE,
        .sampleSize = 32,
        .channels = 1,
        .data = Data,
    };

    return wave;
}

void Play(Sound SquareSound1, Sound SquareSound2, Sound SquareSound3, Sound SawtoothSound1, Sound SawtoothSound2, Sound SineSound, Sound NoiseSound)
{
    uint8_t MemoryAddressBytes[2];
    MemoryAddressBytes[0] = Memory.SRAM[AUDIO_POINTER_HIGH - SRAM_START];
    MemoryAddressBytes[1] = Memory.SRAM[AUDIO_POINTER_LOW - SRAM_START];
    uint16_t Address = U8toU16(MemoryAddressBytes);

    if (Memory.SRAM[AUDIO_STATE - SRAM_START])
    {
        U16toU8(++Address, MemoryAddressBytes);
        Memory.SRAM[AUDIO_POINTER_HIGH - SRAM_START] = MemoryAddressBytes[0];
        Memory.SRAM[AUDIO_POINTER_LOW - SRAM_START] = MemoryAddressBytes[1];
    }
}