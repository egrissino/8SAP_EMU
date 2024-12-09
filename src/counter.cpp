/*
 *  Program Counter Emulator
 *  Evan Grissino 2024
 *  
 */

#include "counter.h"
#include <stdio.h>

/* ============================================================== */

RingCounter RingCounter::operator++(int)
{
    uint8_t val = (cycle + 1) % kClkMax;
    cycle = static_cast<Cycle> (val);
    return *this;
}

/* ============================================================== */

void RingCounter::clear ()
{
    cycle = kClk0;
}

/* ============================================================== */

RingCounter::Cycle RingCounter::getCycle ()
{
    return cycle;
}

/* ============================================================== */

void ProgramCounter::count ()
{
    latchedValue++;
}

/* ============================================================== */

void ProgramCounter::reset ()
{
    latchedValue = 0;
}
