/*
 *  Buffer Emulator
 *  Evan Grissino 2024
 *  
 */

#pragma once

#include "bus.h"

class Buffer : public IBusInput, public ITriStateBusOutput
{
public:
    Buffer () {};

    void setOutputEnable (bool enabled) override;

private:
    uint8_t inValue{0};
    uint8_t outValue{0};
    
};
