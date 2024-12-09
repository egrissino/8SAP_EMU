/*
 *  Control Emulator
 *  Evan Grissino 2024
 *  
 */

#pragma once

#include <lib/register.h>
#include <src/counter.h>
#include <src/alu.h>
#include <src/eeprom.h>
#include <src/sram.h>

class Control : public ITriStateBusOutput
{
public:
    Control (ALU& alu, Register& mar, SRAM& ram, EEPROM& rom, ProgramCounter& pc, Register& out)
    : alu (alu), mar (mar), ram (ram), rom (rom), pc (pc), out (out) {};

    void clk (bool edge);

    void run ();
    void halt ();
    void reset ();
    void setOutputEnable (bool enabled) override;

    bool isHalted ();

    enum InstructionSet : uint8_t {
        NOP = 0,
        LDI,
        LDA,
        LDB,
        JMP,
        JPZ,
        JPC,
        STR,
        LDM,
        MOV,
        OUT,
        STM,
        ADD,
        SUB,
        SFT,
        HLT,
    };



private:
    uint8_t prog{0};

    ALU& alu;
    Register& mar;
    SRAM& ram;
    EEPROM& rom;
    ProgramCounter& pc;
    Register& out;

    RingCounter rc;
    Register instructionRegister;

    bool halted{true};
};


