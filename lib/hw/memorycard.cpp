/*
 *  ALU Card HW Interface
 *  Evan Grissino 2024
 *
 */

#include <memorycard.h>
#include <../arduino/cores/Arduino.h>

using namespace SAP8;
using namespace HW;


MemoryBoard::MemoryBoard()
{
    pinMode()

}

// ============================================================== //

uint8_t readWatch()
{
    // Triggered when MemOut goes high

    // Watch Data lines for value
    read();
    return 0;
}

// ============================================================== //

uint16_t setAddressWatch()
{
    return 0;

}

// ============================================================== //

uint8_t writeWatch()
{
    return 0;
}

// ============================================================== //

uint8_t read(uint16_t address)
{
    enableChip(true);

    // Load Address into MAR
    writeDataLines(address);
    enableMarLoad(true);
    enableMarLoad(false);

    // Read out data
    enableOut(true);
    readDataLines(value);
    enableWrite(false);

    enableChip(false);
}

// ============================================================== //

void write(uint8_t address, uint8_t value)
{
    enableChip(true);

    // Load Address into MAR
    writeDataLines(address);
    enableMarLoad(true);
    enableMarLoad(false);

    // Write out data
    enableWrite(true);
    writeDataLines(value);
    enableWrite(false);

    enableChip(false);
}

// ============================================================== //

static void setDataLinesPinMode(PinDirection direction)
{
    switch (direction)
    {
    case kInput:
        for (auto pin : datPins)
            pinMode(pin, INPUT);
        break;
    case kOutput:
        for (auto pin : datPins)
            pinMode(pin, OUTPUT);
        break;
    }
}

// ============================================================== //

static uint8_t readDataLines()
{
    uint8_t value{0};
    for (size_t i = 0; i < ;i++)
        value |= digitalRead(datPins[i]) << i;
    return value;
}

// ============================================================== //

static void writeDataLines(uint8_t value)
{
    for (size_t i = 0; i < ;i++)
        digitalWrite(datPins[i], (value >> i));
}

// ============================================================== //

void disableOut()
{
    pinMode(OutputEnablePin, INPUT);
}

// ============================================================== //

void enableOut(bool state)
{
    pinMode(OutputEnablePin, OUTPUT);
    digitalWrite(OutputEnablePin, state);
}

// ============================================================== //

void enableWrite(bool state)
{
    pinMode(WriteEnablePin, OUTPUT);
    digitalWrite(WriteEnablePin, state);
}

// ============================================================== //

void disableWrite()
{
    pinMode(OutputEnablePin, INPUT);
}

// ============================================================== //

void enableChip(bool state)
{
    pinMode(ChipEnablePin, OUTPUT);
    digitalWrite(ChipEnablePin, state);
}

// ============================================================== //

void disableChip()
{
    pinMode(ChipEnablePin, INPUT);
}

// ============================================================== //

void enableMarLoad(bool state)
{
    pinMode(MarLoadPin, OUTPUT);
    digitalWrite(MarLoadPin, state);
}

// ============================================================== //

void disableMarLoad()
{
    pinMode(MarLoadPin, INPUT);
}

// ============================================================== //

void outHandler(bool state)
{

}

// ============================================================== //

void writeHandler(bool state)
{

}

// ============================================================== //

void chipHandler(bool state)
{

}

// ============================================================== //

void marHandler(bool state)
{

}