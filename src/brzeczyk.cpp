#include <brzeczyk.h>

Brzeczyk::Brzeczyk(byte pin)
{
    this->pin = pin;
    czy_alarm = false;
}

void Brzeczyk::operator() (){
    if (czy_alarm)
    {
        
    }
    
}