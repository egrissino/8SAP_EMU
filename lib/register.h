/*
 *  Register emulator
 *  Evan Grissino 2024
 *  
 */

#pragma once

#include "bus.h"
#include <stdint.h>

class Register : public IBusInput, public ITriStateBusOutput
{
public:
    Register (uint8_t init = 0);

    void latch ();
    void setOutputEnable (bool enabled) override;

protected:
    uint8_t latchedValue{0};
};
