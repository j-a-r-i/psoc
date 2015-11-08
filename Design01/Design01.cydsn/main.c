/* =========================================
 * Copyright Jari Ojanen All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 * =========================================*/
#include <project.h>
#include "hw.h"
#include <..\..\..\drivers\ds1820.h>
#include "ble1_hts.h"

CY_ISR_PROTO(Timer1ISR);
CY_ISR_PROTO(Spi1ISR);

static int gCounter = 0;
static int gEnabled = 0;
#define LED_ON   0
#define LED_OFF  1

//------------------------------------------------------------------------------
void AppCallback(uint32 event, void* eventParam)
{
    switch (event) {
    case CYBLE_EVT_STACK_ON:
        //WatchdogTimer_Stop();
        CyBle_GappStartAdvertisement(CYBLE_ADVERTISING_FAST);
        break;
    case CYBLE_EVT_TIMEOUT:
        break;
    case CYBLE_EVT_HARDWARE_ERROR:
        break;
    case CYBLE_EVT_HCI_STATUS:
        break;
        
    case CYBLE_EVT_GAPP_ADVERTISEMENT_START_STOP:
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
void HtsCallback(uint32 event, void* eventParam)
{
    switch (event) {
        case CYBLE_EVT_HTSS_INDICATION_ENABLED:
            gEnabled = 1;
            break;
        case CYBLE_EVT_HTSS_INDICATION_DISABLED:
            gEnabled = 0;
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
    case 4:
        ds1820_measure(PIN_OW1);
        break;
    case 5:
        ds1820_read_temp(PIN_OW1);
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
    
    ds1820_init(PIN_OW1);
    
    // Start interrupts
    //
    timer1_Start();
    //isrTimer1_StartEx(Timer1ISR);
    spi_SCB_IRQ_StartEx(Spi1ISR);
    
    CyBle_Start(AppCallback);
    CyBle_HtsRegisterAttrCallback(HtsCallback);
    
    CyGlobalIntEnable; // enable global interrupts
    
    for(;;)
    {
        if(CyBle_GetState() == CYBLE_STATE_CONNECTED) {
            
        }
        CyBle_ProcessEvents();
    }
}
