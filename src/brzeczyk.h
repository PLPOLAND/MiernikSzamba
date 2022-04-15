#ifndef BRZECZYK
#define BRZECZYK
#include <Arduino.h>
class Brzeczyk
{
private:
    byte pin;
    bool czy_alarm;
public:
    Brzeczyk(byte pin);

    void operator() ();
    void alarm();
};



#endif // !BRZECZYK