/*
 *  Alu Emulator
 *  Evan Grissino 2024
 *  
 */

#pragma once

#include <lib/bus.h>
#include <lib/register.h>
#include <lib/buffer.h>

class ALU : public IBusInput, public ITriStateBusOutput
{
public:
    ALU ();

    void setOutputEnable (bool enabled) override;

    void loadA ();
    void loadB ();
    void add ();
    void subtract ();
    void shift ();

    bool isZeroSet () { return zero; }
    bool isCarrySet () { return carry; }

private:
    Register A;
    Register B;

    Buffer Ashift;
    Buffer AOut;

    bool carry{false}, zero{true}, carryIn{false};
};