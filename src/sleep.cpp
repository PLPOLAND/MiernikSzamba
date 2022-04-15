#include <sleep.h>

void  Sleep::sleepFor(int sleepTimeMins)
{

    for (int i = 0; i < sleepTimeMins; i++)
    {
        for (size_t i = 0; i < 8; i++)
        {
            LowPower.idle(SLEEP_8S, ADC_OFF, TIMER2_OFF, TIMER1_OFF, TIMER0_OFF, SPI_OFF, USART0_OFF, TWI_OFF);
        }
        LowPower.idle(SLEEP_4S, ADC_OFF, TIMER2_OFF, TIMER1_OFF, TIMER0_OFF, SPI_OFF, USART0_OFF, TWI_OFF);
    }
    

}
