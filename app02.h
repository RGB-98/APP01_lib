#include "mbed.h"
#include <cstdint>
#include "TSISensor.h"

static DigitalOut sled[] = {D13,D12,D11,D10};
static TSISensor cap;

static void SLED_OFF(void);
static void SLED1_ON(void);
static void SLED2_ON(void);
static void SLED3_ON(void);
static void SLED4_ON(void);
static float cap_check(void);
static void cap_touch(void);

void SLED_OFF(void)
{
    sled[0]= 1;
    sled[1]= 1;
    sled[2]= 1;
    sled[3]= 1;
}

void SLED1_ON(void)
{
    sled[0]= 0;
    sled[1]= 1;
    sled[2]= 1;
    sled[3]= 1;
}

void SLED2_ON(void)
{
    sled[0]= 1;
    sled[1]= 0;
    sled[2]= 1;
    sled[3]= 1;
}

void SLED3_ON(void)
{
    sled[0]= 1;
    sled[1]= 1;
    sled[2]= 0;
    sled[3]= 1;
}

void SLED4_ON(void)
{
    sled[0]= 1;
    sled[1]= 1;
    sled[2]= 1;
    sled[3]= 0;
}

float cap_check(void)
{
    float BUFF = cap.readPercentage();
    return BUFF;
}

void cap_touch(void)
{
    float cap_check_buff = cap_check();

        if ( cap_check_buff == 0.00f )
        {
            SLED_OFF();
        }
        else if( cap_check_buff <= 0.50f )
        {
            if( cap_check_buff <= 0.25f )
            {
                SLED4_ON();
            }
            else
            {
                SLED3_ON();
            }
        }
        else
        {
            if( cap_check_buff >= 0.75f )
            {
                SLED1_ON();
            }
            else
            {
                SLED2_ON();
            }
        }
}

inline void app02 (void)
{
    while (true) 
    {
        cap_touch();
    }
}
