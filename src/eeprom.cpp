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

size_t EEPROM::loadProgram (const uint8_t* prog, size_t size)
{
    size_t sizeSel = std::min (size, (size_t)kMemSize);
    memcpy (memory, prog, sizeSel);
    return sizeSel;
}

/* ============================================================== */

void EEPROM::setOutputEnable (bool enabled)
{
    this->enabled = enabled;
    if (enabled)
    {
        outValue = memory[address];
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

    memory[address] = inValue;
    printf (" Write 0x%02x\n", memory[address]);
}

/* ============================================================== */

void EEPROM::setAddress (uint16_t address)
{
    this->address = address & 0x7F;
    printf (" set Addr: 0x%04x\n", address);
}