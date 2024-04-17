#include "mbed.h"

// Initialize Serial object for UART communication
Serial pc(PTA2, PTA1); // TX, RX pins for UART
DigitalOut leds[] = {LED_RED,LED_GREEN,LED_BLUE};

char UART_STR[6]={0};
char i = 0;
static bool cmdflag = false;

void LED_OFF()
{
        leds[0]= 1;
        leds[1]= 1;
        leds[2]= 1;
}

void LEDRED_ON()
{
        leds[0]= 0;
        leds[1]= 1;
        leds[2]= 1;
}

void LEDGREEN_ON()
{
        leds[0]= 1;
        leds[1]= 0;
        leds[2]= 1;
}

void LEDBLUE_ON()
{
        leds[0]= 1;
        leds[1]= 1;
        leds[2]= 0;
}


void LED_CTRL(char* UART_STR)
{
    if (strcmp(UART_STR,"r on\r") == 0)
    {
        LEDRED_ON();
    }
    else if (strcmp(UART_STR,"g on\r") == 0)
    {
        LEDGREEN_ON();
    }
    else if (strcmp(UART_STR,"b on\r") == 0)
    {
        LEDBLUE_ON();
    }
    else if (strcmp(UART_STR,"r off\r") == 0)
    {
        LED_OFF();
    }
    else if (strcmp(UART_STR,"g off\r") == 0)
    {
        LED_OFF();
    }
    else if (strcmp(UART_STR,"b off\r") == 0)
    {
        LED_OFF();
    }
    else
    {        
        LED_OFF();
        pc.printf("\r\n invalid command \r\n");
    }
}

void STR_CLR(char * buffer, char size)
{
    for(char k = 0; k < size ; k++)
    {
        buffer[k] = '\0';
    }
}

void disp_cmd(void)
{
        if(cmdflag == false)
        {
            pc.printf("\r\nCommand List:\r\n\n 1.To on the Red LED press r on \r\n 2.To off the Red LED press r off \r\n 3.To on the Blue LED press b on \r\n 4.To off the Blue LED press b off \r\n 5.To on the Green LED press g on \r\n 6.To off the Green LED press g off \r\n 7.To on the Amber LED press a on \r\n 8.To off the Amber LED press a off \r\n\n ");
            cmdflag = true;
        }
}

void cmd_check(void)
{
        char c;
        if (pc.readable()) 
        {   // Check if data is available to read
            pc.read(&c,1); // Read a character from the serial terminal
            UART_STR[i++] = c;

            if ((c == '\r') || (i == 6)) 
            {   // Check for carriage return character
                char buffer[12];
                sprintf(buffer,"Received:%s\r\n",UART_STR);
                pc.write(buffer,strlen(buffer)); // Echo received character back to serial terminal
                i = 0;
                STR_CLR(buffer,sizeof(buffer));
                LED_CTRL(UART_STR); 
            }
        }
}

void app01 (void)
{
    LED_OFF();
    pc.baud(9600);

    while (true) 
    {
        disp_cmd();
        cmd_check();
    }
}
