/*
 *  Buffer Emulator
 *  Evan Grissino 2024
 *  
 */

#pragma once

#include <thread>
#include <src/control.h>

class Emulator
{
public:
    Emulator ()
    : ctl (alu, mar, ram, rom, pc, out) {};

    void reset ();
    void run ();
    void halt ();
    size_t dumpMem (uint8_t* buffer, size_t bytes = EEPROM::kMemSize);

    size_t loadProgram (const uint8_t* prog, size_t size);

private:
    static void threadEntry (void* args);
    void threadLoop ();
    size_t progSize{0};

    ALU alu;
    SRAM ram;
    EEPROM rom;
    Control ctl;
    Register mar;
    Register out;
    ProgramCounter pc;

    std::thread emuThread;
};
