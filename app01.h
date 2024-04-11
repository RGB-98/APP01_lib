#include "mbed.h"

// Initialize BufferedSerial object for UART communication
BufferedSerial pc(PTA2, PTA1); // TX, RX pins for UART
DigitalOut leds[] = {D13,D12,D11,D10};

void LED_OFF()
{
        leds[0]= 1;
        leds[1]= 1;
        leds[2]= 1;
        leds[3]= 1;
}

void LED1_ON()
{
        leds[0]= 0;
        leds[1]= 1;
        leds[2]= 1;
        leds[3]= 1;
}

void LED2_ON()
{
        leds[0]= 1;
        leds[1]= 0;
        leds[2]= 1;
        leds[3]= 1;
}

void LED3_ON()
{
        leds[0]= 1;
        leds[1]= 1;
        leds[2]= 0;
        leds[3]= 1;
}

void LED4_ON()
{
        leds[0]= 1;
        leds[1]= 1;
        leds[2]= 1;
        leds[3]= 0;
}

void LED_CTRL(char* UART_STR)
{
    if (strcmp(UART_STR,"1 on\r") == 0)
    {
        LED1_ON();
    }
    else if (strcmp(UART_STR,"2 on\r") == 0)
    {
        LED2_ON();
    }
    else if (strcmp(UART_STR,"3 on\r") == 0)
    {
        LED3_ON();
    }
    else if (strcmp(UART_STR,"4 on\r") == 0)
    {
        LED4_ON();
    }
    else
    {
        LED_OFF();
    }
}

void STR_CLR(char * buffer, char size)
{
    for(char k = 0; k < size ; k++)
    {
        buffer[k] = '\0';
    }
}