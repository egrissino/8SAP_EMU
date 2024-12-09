/*
 *  Program Counter Emulator
 *  Evan Grissino 2024
 *  
 */

#pragma once

#include <lib/register.h>

class RingCounter
{
public:
   enum Cycle : uint8_t
    {
        kClk0,
        kClk1,
        kClk2,
        kClk3,
        kClk4,
        kClkMax,
    };

    RingCounter () {};

    void clear ();
    Cycle getCycle ();
    RingCounter operator++(int);

private:
    Cycle cycle{kClk0};
};

class ProgramCounter : public Register
{
public:
    ProgramCounter () {};

    void count ();
    void reset ();
};