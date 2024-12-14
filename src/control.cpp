/*
 *  Control Emulator
 *  Evan Grissino 2024
 *  
 */

#include "control.h"
#include <stdio.h>

/* ============================================================== */

void Control::reset ()
{
    pc.reset ();
    rc.clear ();
    instructionRegister.setOutputEnable (true);
}

/* ============================================================== */

void Control::run ()
{
    halted = false;
    tickCount = 0;
}

/* ============================================================== */

void Control::halt ()
{
    halted = true;
}

/* ============================================================== */

bool Control::isHalted ()
{
    return halted;
}

/* ============================================================== */

size_t Control::getTicks ()
{
    return tickCount;
}

/* ============================================================== */

void Control::clk (bool edge)
{
    static uint8_t inst{0}, imm{0};
    if (edge)
    {
        tickCount++;
        // Rising Edge
        switch (rc.getCycle ())
        {
        case RingCounter::kClk0:
            // printf ("Clk0 Rising\n");
            pc.setOutputEnable (true);
            rom.setAddress (pc.getOutput () | (prog << 8));
            break;
        case RingCounter::kClk1:
            // printf ("Clk1 Rising\n");
            break;
        case RingCounter::kClk2:
            // printf ("Clk2 Rising\n");
            rom.setOutputEnable (true);
            instructionRegister.setInput (rom.getOutput ());
            instructionRegister.latch ();
            break;
        case RingCounter::kClk3:
            inst = (instructionRegister.getOutput () & 0xF0) >> 4;
            imm = (instructionRegister.getOutput () & 0x0F);
            switch (inst)
            {
                case NOP:
                    // printf ("NOP\n");
                    break;
                case LDI:
                    // printf ("LDI: 0x%02x\n", imm);
                    alu.setInput (imm);
                    alu.loadA ();
                    break;
                case LDA:
                case LDB:
                case JMP:
                case JPZ:
                case JPC:
                case STR:
                    rom.setAddress (imm | (prog << 8));
                    break;
                case LDM:
                    alu.setOutputEnable (true);
                    rom.setAddress (alu.getOutput () | (prog << 8));
                    break;
                case MOV:
                    alu.setOutputEnable (true);
                    alu.setInput (alu.getOutput ());
                    alu.loadB ();
                    // printf ("MOV: 0x%02x\n", alu.getOutput ());
                    break;
                case OUT:
                    alu.setOutputEnable (true);
                    out.setInput (alu.getOutput ());
                    out.latch ();
                    // printf ("OUT: 0x%02x\n", alu.getOutput ());
                    break;
                case STM:
                    alu.setOutputEnable (true);
                    rom.setAddress (alu.getOutput ());
                    // printf ("STM: \n");
                    break;
                case ADD:
                    // printf ("ADD\n");
                    alu.add ();
                    break;
                case SUB:
                    // printf ("SUB\n");
                    alu.subtract ();
                    break;
                case SFT:
                    // printf ("SFT !\n");
                    alu.shift ();
                    break;
                case HLT:
                    printf ("HLT\n");
                    halt ();
                    break;
            }
            // printf ("Clk3 Rising\n");
            break;
        case RingCounter::kClk4:
            switch (inst)
            {
                case NOP:
                    break;
                case LDI:
                    break;
                case LDA:
                    rom.setOutputEnable (true);
                    alu.setInput (rom.getOutput ());
                    alu.loadA ();
                    // printf ("LDA: 0x%02x\n", rom.getOutput ());
                    break;
                case LDB:
                    rom.setOutputEnable (true);
                    alu.setInput (rom.getOutput ());
                    alu.loadB ();
                    // printf ("LDB: 0x%02x\n", rom.getOutput ());
                    break;
                case JMP:
                    rom.setOutputEnable (true);
                    pc.setInput (rom.getOutput ());
                    pc.latch ();
                    // printf ("JMP: 0x%02x\n", rom.getOutput ());
                    break;
                case JPZ:
                    // printf ("JPZ\n");
                    if (alu.isZeroSet ())
                    {
                        rom.setOutputEnable (true);
                        pc.setInput (rom.getOutput ());
                        pc.latch ();
                    }
                    break;
                case JPC:
                    // printf ("JPC\n");
                    if (alu.isCarrySet ())
                    {
                        rom.setOutputEnable (true);
                        pc.setInput (rom.getOutput ());
                        pc.latch ();
                    }
                    break;
                case STR:
                    // printf ("STR: 0x%02x\n", imm);
                    alu.setOutputEnable (true);
                    rom.setInput (alu.getOutput ());
                    rom.latch ();
                    break;
                case LDM:
                    rom.setOutputEnable (true);
                    alu.setInput (rom.getOutput ());
                    alu.loadA ();
                    // printf ("LDM: 0x%02x\n", rom.getOutput ());
                    break;
                case STM:
                    alu.add ();
                    alu.setOutputEnable (true);
                    rom.setInput (alu.getOutput ());
                    rom.latch ();
                    break;
                case SFT:
                    break;
                case HLT:
                    halt ();
                    break;
            }
            // printf ("Clk4 Rising\n");
            break;
        }
    }
    else
    {
        // Falling Edge
        switch (rc.getCycle ())
        {
        case RingCounter::kClk0:
            // printf ("Clk0 Falling\n");
            pc.setOutputEnable (false);
            break;
        case RingCounter::kClk1:
            // printf ("Clk1 Falling\n");
            pc.count ();
            break;
        case RingCounter::kClk2:
            // printf ("Clk2 Falling\n");
            rom.setOutputEnable (false);
            break;
        case RingCounter::kClk3:
            // printf ("Clk3 Falling\n");
            switch (inst)
            {
                case NOP:
                    break;
                case LDI:
                    break;
                case LDA:
                    break;
                case LDB:
                    break;
                case JMP:
                    break;
                case JPZ:
                    break;
                case JPC:
                    break;
                case STR:
                    break;
                case LDM:
                case MOV:
                case OUT:
                case STM:
                    alu.setOutputEnable (false);
                    break;
                case ADD:
                    break;
                case SUB:
                    break;
                case SFT:
                    break;
                case HLT:
                    halt ();
                    break;
            }
            break;
        case RingCounter::kClk4:
            // printf ("Clk4 Falling\n");
            switch (inst)
            {
                case NOP:
                    break;
                case LDI:
                    break;
                case LDA:
                case LDB:
                case JMP:
                case LDM:
                    rom.setOutputEnable (false);
                    break;
                case JPZ:
                    if (alu.isZeroSet ())
                    {
                        rom.setOutputEnable (false);
                    }
                    break;
                case JPC:
                    if (alu.isCarrySet ())
                    {
                        rom.setOutputEnable (false);
                    }
                    break;
                case STR:
                case STM:
                    alu.setOutputEnable (false);
                    break;
                case MOV:
                    break;
                case OUT:
                    break;
                case ADD:
                    break;
                case SUB:
                    break;
                case SFT:
                    break;
                case HLT:
                    break;
            }
            break;
        }
        // Incriment Ring Counter
        rc++;
    }

}

/* ============================================================== */

void Control::setOutputEnable (bool enabled)
{
    if (enabled)
    {
        outValue = instructionRegister.getOutput () & 0x0F;
    }
    else
    {
        outValue = 0;
    }
}