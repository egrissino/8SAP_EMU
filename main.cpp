/*
 *  Emulator Application
 *  Evan Grissino 2024
 *  
 */


#include <src/emulator.h>
#include <unistd.h>
#include <primesfinder.h>
#include <stdio.h>

Emulator emu;

const uint8_t testprogram[]
{
    0x00, 0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80, 0x90, 0xA0, 0xB0, 0xC0,  0xD0, 0xE0, 0xF0,
};

const uint8_t* program{primesFinder};
const size_t& size{primesFinderSize};

int main (int argc, char** argv)
{
    auto ret = emu.loadProgram (program, size);

    if (ret != size)
    {
        return 0;
    }

    emu.reset ();

    emu.run ();

    usleep (500000);

    emu.halt ();

    uint8_t buffer[EEPROM::kMemSize]{0};
    size_t bytes = emu.dumpMem (buffer);

    for (int i = 64; i < bytes; i++)
    {
        printf ("0x%02x, ", buffer[i]);

        if ((i % 8) == 7)
        {
            printf ("\n");
        }
    }

    return 0;
};
