/* =========================================
 * Copyright Jari Ojanen All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 * =========================================*/
#include <project.h>

CY_ISR_PROTO(Timer1ISR);
CY_ISR_PROTO(Spi1ISR);

static int gCounter = 0;

#define LED_ON   0
#define LED_OFF  1

//------------------------------------------------------------------------------
void AppCallback(uint32 event, void* eventParam)
{
    switch (event) {
    case CYBLE_EVT_STACK_ON:
        break;
    case CYBLE_EVT_TIMEOUT:
        break;
    case CYBLE_EVT_HARDWARE_ERROR:
        break;
    case CYBLE_EVT_HCI_STATUS:
        break;
    /*case :
        break;
    case :
        break;
    case :
        break;*/
    }
}

//------------------------------------------------------------------------------
CY_ISR(Timer1ISR)
{
    gCounter++;
    
    switch (gCounter) {
    case 1:
        PinLedGreen_Write(LED_ON);
        PinLedBlue_Write(LED_OFF);
        PinLedRed_Write(LED_OFF);
        break;
    case 2:
        PinLedGreen_Write(LED_OFF);
        PinLedBlue_Write(LED_ON);
        PinLedRed_Write(LED_OFF);
        break;
    case 3:
        PinLedGreen_Write(LED_OFF);
        PinLedBlue_Write(LED_OFF);
        PinLedRed_Write(LED_ON);
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
    
    CyBle_Start(AppCallback);
    
    CyGlobalIntEnable; // enable global interrupts
    
    for(;;)
    {
        if(CyBle_GetState() == CYBLE_STATE_CONNECTED) {
            
        }
        CyBle_ProcessEvents();
    }
}
