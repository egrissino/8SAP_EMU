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

bool Emulator::isHalted ()
{
    return ctl.isHalted ();
}

/* ============================================================== */

size_t Emulator::loadProgram (const uint8_t* prog, size_t size)
{
    return (progSize = rom.loadProgram (prog, size));
}

/* ============================================================== */

size_t Emulator::dumpMem (uint8_t* buffer, size_t bytes)
{
    for (int i = 0; i < bytes; i++)
    {
        rom.setAddress (i);
        rom.setOutputEnable (true);
        buffer[i] = rom.getOutput ();
        rom.setOutputEnable (false);
    }
    return bytes;
}

/* ============================================================== */

size_t Emulator::getTicks ()
{
    return ctl.getTicks ();
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
        // usleep (1);


        /* Clock Falling Edge */
        ctl.clk (false);
        // usleep (1);
    }
}
