/*
 *  Emulator
 *  Evan Grissino 2024
 *  
 */

#include <stdio.h>
#include <unistd.h>
#include <algorithm>
#include <src/emulator.h>

/* ============================================================== */

void Emulator::reset ()
{
    ctl.reset ();
}

/* ============================================================== */

void Emulator::run ()
{
    ctl.run ();
    emuThread = std::thread (threadEntry, this);
}

/* ============================================================== */

void Emulator::halt ()
{
    ctl.halt ();
    emuThread.join ();
}

/* ============================================================== */

size_t Emulator::loadProgram (const uint8_t* prog, size_t size)
{
    return (progSize = rom.loadProgram (prog, size));
}

/* ============================================================== */

size_t Emulator::dumpMem (uint8_t* buffer, size_t bytes)
{
    size_t sizeSelect = std::min (bytes, progSize);

    for (int i = 0; i < sizeSelect; i++)
    {
        rom.setAddress (i);
        rom.setOutputEnable (true);
        buffer[i] = rom.getOutput ();
    }
    return sizeSelect;
}

/* ============================================================== */

void Emulator::threadEntry (void* args)
{
    Emulator* emu = reinterpret_cast<Emulator*> (args);
    emu->threadLoop ();
}

/* ============================================================== */

void Emulator::threadLoop ()
{
    while (!ctl.isHalted ())
    {
        /* Clock Rising Edge */
        ctl.clk (true);
        usleep (1000);


        /* Clock Falling Edge */
        ctl.clk (false);
        usleep (1000);
    }
}
