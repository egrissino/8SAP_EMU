/*
 *  EEPROM Emulator
 *  Evan Grissino 2024
 *  
 */

#include "eeprom.h"
#include <stdio.h>
#include <string.h>
#include <algorithm>

/* ============================================================== */

EEPROM::EEPROM ()
{
    memset (memory, 0, kMemSize);
    address = 0xF0;
};

/* ============================================================== */

size_t EEPROM::loadProgram (const uint8_t* prog, size_t size)
{
    size_t sizeSel = std::min (size, (size_t)kMaxProgSize);
    memcpy (memory, prog, sizeSel);
    // printf ("0x%04x : 0x%02x\n", address, memory[address]);
    return sizeSel;
}

/* ============================================================== */

void EEPROM::setOutputEnable (bool enabled)
{
    this->enabled = enabled;
    if (enabled)
    {
        outValue = memory[this->address];
        // printf ("get : 0x%02x\n", outValue);
    }
    else
    {   
        outValue = 0;
    }
}

/* ============================================================== */

void EEPROM::latch ()
{
    if (enabled)
        return;

    memory[this->address] = inValue;
    // printf (" Write 0x%02x\n", memory[address]);
}

/* ============================================================== */

void EEPROM::setAddress (uint16_t address)
{
    this->address = address & 0x7FF;
    // printf (" set Addr: 0x%04x\n", address);
}