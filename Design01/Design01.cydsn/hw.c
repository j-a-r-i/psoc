/* =========================================
 * Copyright Jari Ojanen All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 * =========================================*/
#include <project.h>
#include "hw.h"

// Do nothing. This function is not needed with PSOC.
//
void config_port_mode (uint8_t pin, uint8_t out)
{
}

void delay_us(uint16_t usDelay)
{
    CyDelayUs(usDelay);
}

void config_port_set (uint8_t pin)
{
    switch (pin)
    {
        case PIN_OW1:
            PinOW1_Write(1);
            break;
        
        default:
            break;
    }
}

void config_port_clear (uint8_t pin)
{
    switch (pin)
    {
        case PIN_OW1:
            PinOW1_Write(0);
            break;
        
        default:
            break;
    }
}

uint8_t config_port_read (uint8_t pin)
{
    uint8_t ret = 0;
    
    switch (pin)
    {
        case PIN_OW1:
            ret = PinOW1_Read();
            break;
        
        default:
            break;
    }
    return ret;
}