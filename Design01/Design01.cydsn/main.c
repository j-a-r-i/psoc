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
#include <project.h>

CY_ISR_PROTO(Timer1ISR);
CY_ISR_PROTO(Spi1ISR);

static int gCounter = 0;


CY_ISR(Timer1ISR)
{
    gCounter++;
    
    switch (gCounter) {
    case 10:
        PinLedGreen_Write(1);
        PinLedBlue_Write(0);
        PinLedRed_Write(0);
        break;
    case 20:
        PinLedGreen_Write(0);
        PinLedBlue_Write(1);
        PinLedRed_Write(0);
        break;
    case 30:
        PinLedGreen_Write(0);
        PinLedBlue_Write(0);
        PinLedRed_Write(1);
        break;
        
    case 40:
        gCounter = 0;
        break;
    }       
}

CY_ISR(Spi1ISR)
{

}



int main()
{
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    spi_Init();
    timer1_Init();
    CyBle_Init();
    
    // Start interrupts
    //
    isrTimer1_StartEx(Timer1ISR);
    spi_SCB_IRQ_StartEx(Spi1ISR);
    
    CyGlobalIntEnable; /* Uncomment this line to enable global interrupts. */
    
    for(;;)
    {
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
