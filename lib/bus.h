/*
 *  Bus Interface
 *  Evan Grissino 2024
 *  
 */

#pragma once

#include <stdint.h>

struct IBusInput
{
public:
    virtual void setInput (uint8_t value) { inValue = value; }

protected:
    uint8_t inValue{0};
};

struct IBusOutput
{
public:
    virtual uint8_t getOutput () { return outValue; }

protected:
    uint8_t outValue{0};
};

struct ITriStateBusOutput : public IBusOutput
{
public:
    virtual void setOutputEnable (bool enabled) = 0;

protected:
    bool enabled{false};
};
