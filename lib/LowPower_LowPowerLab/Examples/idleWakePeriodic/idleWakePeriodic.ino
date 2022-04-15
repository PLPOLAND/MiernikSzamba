// **** INCLUDES *****
#include "LowPower.h"

void setup()
{
    Serial.begin(9600);
}

void loop() 
{
  // Enter idle state for 8 s with the rest of peripherals turned off
  // Each microcontroller comes with different number of peripherals
  // Comment off line of code where necessary
  Serial.println("X");

  // LowPower.idle(SLEEP_1S, ADC_OFF, TIMER2_OFF, TIMER1_OFF, TIMER0_OFF, 
  //               SPI_OFF, USART0_OFF, TWI_OFF);

}

