#ifndef CZUJNIK_H
#define CZUJNIK_H
#include <Arduino.h>

class Czujnik
{
private:
    byte pin_trigg;
    byte pin_echo;
public:
    Czujnik(byte trigg, byte echo);
    ~Czujnik();
    ///Zmierz raz
    int zmierz();
    ///Zmierz trzy razy i wyciągnij wartość.
    int zmierzBetter();
};


#endif // !CZUJNIK_H