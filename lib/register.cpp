/*
 *  Register emulator
 *  Evan Grissino 2024
 *  
 */

#include "register.h"
#include <stdio.h>

Register::Register (uint8_t init)
: latchedValue (init) 
{}

/* ============================================================== */

void Register::setOutputEnable (bool enabled)
{
    this->enabled = enabled;
    if (enabled)
    {
        outValue = latchedValue;
    }
    else
    {
        outValue = 0;
    }
}

/* ============================================================== */

void Register::latch ()
{
    latchedValue = inValue;
    setOutputEnable (this->enabled);
}

