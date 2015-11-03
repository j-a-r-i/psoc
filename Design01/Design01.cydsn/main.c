/* =========================================
 * Copyright Jari Ojanen All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 * =========================================*/
#include <project.h>

CY_ISR_PROTO(Timer1ISR);
CY_ISR_PROTO(Spi1ISR);

static int gCounter = 0;

//------------------------------------------------------------------------------
CY_ISR(Timer1ISR)
{
    gCounter++;
    
    switch (gCounter) {
    case 1:
        PinLedGreen_Write(0);
        PinLedBlue_Write(1);
        PinLedRed_Write(1);
        break;
    case 2:
        PinLedGreen_Write(1);
        PinLedBlue_Write(0);
        PinLedRed_Write(1);
        break;
    case 3:
        PinLedGreen_Write(1);
        PinLedBlue_Write(1);
        PinLedRed_Write(0);
        gCounter = 0;
        break;
    }       
}

//------------------------------------------------------------------------------
CY_ISR(Spi1ISR)
{

}

//------------------------------------------------------------------------------
int main()
{
    spi_Init();
    timer1_Init();
    CyBle_Init();
    
    // Start interrupts
    //
    timer1_Start();
    isrTimer1_StartEx(Timer1ISR);
    spi_SCB_IRQ_StartEx(Spi1ISR);
    
    CyGlobalIntEnable; /* enable global interrupts. */
    
    for(;;)
    {
        /* Place your application code here. */
    }
}
