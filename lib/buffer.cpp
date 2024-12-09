/*
 *  Buffer Emulator
 *  Evan Grissino 2024
 *  
 */

#include "buffer.h"

/* ============================================================== */

void Buffer::setOutputEnable (bool enabled)
{
    this->enabled = enabled;
    if (enabled)
    {
        outValue = inValue;
    }
    else
    {
        outValue = 0;
    }
}
