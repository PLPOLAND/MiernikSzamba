#if !defined(SLEEP)
#define SLEEP
#include <Arduino.h>
#include <LowPower.h>

#define HOURS(X) 60*X
#define DAYS(X) HOURS(24)*X

class Sleep
{
private:
    
public:
    ///Usypia Arduino na podaną liczbę minut
    static void sleepFor(int sleepTimeMins);
};



#endif // SLEEP
