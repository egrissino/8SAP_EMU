/*
 *  Alu Emulator
 *  Evan Grissino 2024
 *  
 */

#include <alu.h>
#include <stdio.h>

ALU::ALU ()
{
    A.setOutputEnable (true);
    B.setOutputEnable (true);
} 

/* ============================================================== */

void ALU::setOutputEnable (bool enabled)
{
    if (enabled)
    {
        outValue = A.getOutput ();
    }
    else
    {
        outValue = 0;
    }

}

/* ============================================================== */

void ALU::loadA ()
{
    A.setInput (inValue);
    A.latch ();
}

/* ============================================================== */

void ALU::loadB ()
{
    B.setInput (inValue);
    B.latch ();
}

/* ============================================================== */

void ALU::add ()
{
    uint16_t res = (uint16_t)A.getOutput () + (uint16_t)B.getOutput ();

    if (res & 0xFF00)
        carry = true;
    else
        carry = false;
    
    if ((res & 0x00FF) == 0)
        zero = true;
    else
        zero = false;

    res += carry;
    printf (" %d + %d = %d\n", A.getOutput (), B.getOutput (), res);


    A.setInput ((res & 0xFF) + carry);
    A.latch ();
}

/* ============================================================== */

void ALU::subtract ()
{
    uint16_t res = ((int16_t)A.getOutput () + ((int16_t)B.getOutput () ^ 0xFF)+1) ;
    printf (" %d - %d = %d\n", A.getOutput (), (uint16_t)B.getOutput (), res&0xFF);
    A.setInput (res & 0xFF);
    A.latch ();

    if (res & 0xFF00)
        carry = true;
    else
        carry = false;
    
    if ((res & 0x00FF) == 0)
        zero = true;
    else
        zero = false;
}

/* ============================================================== */

void ALU::shift ()
{
    Ashift.setInput (A.getOutput ());
    A.setInput (Ashift.getOutput ());
    A.latch ();
}

