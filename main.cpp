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

const uint8_t* program{primesFinderB};
const size_t& size{primesFinderSize};

int main (int argc, char** argv)
{
    size_t ms{0};
    auto ret = emu.loadProgram (program, size);

    if (ret != size)
    {
        return 0;
    }

    emu.reset ();

    emu.run ();

    while (!emu.isHalted ())
    {
        usleep (1000);
        ms += 1;
    }

    emu.halt ();
    printf ("Finished in %lu milliseconds\n", ms);

    uint8_t buffer[EEPROM::kMemSize]{0};
    size_t bytes = emu.dumpMem (buffer, 0xFF+1);
    size_t primes{0};

    for (int i = 96; i < bytes-0x10; i++)
    {
        // printf ("0x%02x, ", buffer[i]);
        printf ("%5d, ", buffer[i]);

        if (buffer[i] != 0)
        {
            primes++;
        }

        if ((i % 8) == 7)
        {
            printf ("\n");
        }
    }

    printf ("Found %ld primnes in %lu ticks\n", primes, emu.getTicks ());

    return 0;
};
