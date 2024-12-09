/*
 *  SRAM Emulator
 *  Evan Grissino 2024
 *  
 */

#pragma once

#include <lib/bus.h>

class SRAM : public IBusInput, public ITriStateBusOutput
{
public:
    SRAM () {};

    void setAddress (uint16_t address);

    void setInput (uint8_t value) override;
    uint8_t getOutput () override;
    void setOutputEnable (bool enabled) override;
    
};