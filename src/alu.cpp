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

    
    // printf (" %d + %d = %d\n", A.getOutput (), B.getOutput (), res);
    A.setInput ((res & 0xFF));
    A.latch ();
}

/* ============================================================== */

void ALU::subtract ()
{
    uint8_t result = 0;
    bool borrow = false;

    for (int i = 0; i < 8; ++i) {
        // Extract bits of A and B at position i
        bool bitA = (A.getOutput () >> i) & 1;
        bool bitB = (B.getOutput () >> i) & 1;

        // Perform bit subtraction with borrow handling
        bool diff = bitA ^ bitB ^ borrow;
        borrow = (!bitA && bitB) || (borrow && (!bitA || bitB));

        // Set the result bit
        result |= (diff << i);
    }

    // Handle unsigned wraparound for recovery
    if (borrow) {
        result = (256 + result); // Equivalent to wrapping in 8-bit unsigned space
    }

    // uint16_t res = ((int16_t)A.getOutput () + ((int16_t)B.getOutput () ^ 0xFF)+1) ;
    // printf (" %d - %d = %d : %d\n", A.getOutput (), (uint16_t)B.getOutput (), result&0xFF, result);
    A.setInput (result & 0xFF);
    A.latch ();

    carry = borrow;
    
    if ((result & 0x00FF) == 0)
        zero = true;
    else
        zero = false;
}

/* ============================================================== */

void ALU::shift ()
{
    
    Ashift.setInput ( A.getOutput () << 1 );
    A.setInput (Ashift.getOutput ());
    A.latch ();
}

