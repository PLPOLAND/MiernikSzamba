#include <czujnik.h>

Czujnik::Czujnik(byte trigg, byte echo)
{
    this->pin_echo = echo;
    this->pin_trigg = trigg;
    pinMode(pin_echo,INPUT);
    pinMode(pin_trigg,OUTPUT);
}

Czujnik::~Czujnik()
{
}

int Czujnik::zmierz(){
    delayMicroseconds(5);
    // Trigger the sensor by setting the trigPin high for 10 microseconds:
    digitalWrite(pin_trigg, HIGH);
    delayMicroseconds(10);
    digitalWrite(pin_trigg, LOW);

    // Read the echoPin. pulseIn() returns the duration (length of the pulse) in microseconds:
    int duration = pulseIn(pin_echo, HIGH);

    // Calculate and return the distance:
    return duration * 0.034 / 2;
}

int Czujnik::zmierzBetter(){
    int tmp[] = { 0, 0, 0 };
    for (byte i = 0; i < 3; i++)
    {
        tmp[i] = zmierz();
    }
    for (byte i = 0; i < 3; i++)
    {
        for (byte j = 0; j < 2; j++)
        {
            if (tmp[i]>tmp[i+1])
            {
                int tmptmp = tmp[i];
                tmp[i] = tmp[i+1];
                tmp[i+1] = tmptmp;
            }
            
        }
        
    }
    return tmp[1];
}