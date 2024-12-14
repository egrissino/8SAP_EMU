/*
 *  EEPROM Emulator
 *  Evan Grissino 2024
 *  
 */

#pragma once

#include <lib/bus.h>
#include <stdint.h>
#include <stdlib.h>

class EEPROM : public IBusInput, public ITriStateBusOutput
{
public:

    EEPROM ();

    void latch ();
    void setAddress (uint16_t address);
    void setOutputEnable (bool enabled) override;

    size_t loadProgram (const uint8_t* prog, size_t size);

    static const size_t kMemSize {65536};
    static const size_t kMaxProgSize {0x100};

private:
    uint16_t address{0};
    uint8_t memory[kMemSize] = {0xFF};
};