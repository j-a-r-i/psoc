/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#ifndef _HW_H
#define _HW_H

#include <stdint.h>

extern void port_set (uint8_t pin);
extern void port_clear (uint8_t pin);
extern void port_mode (uint8_t pin, uint8_t out);
extern uint8_t port_read (uint8_t pin);


extern void delay_us(uint16_t usDelay);
extern void delay_ms(uint16_t msDelay);

#define PIN_OW1 0

#endif
/* [] END OF FILE */
