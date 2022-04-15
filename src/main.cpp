#include <Arduino.h>
#include <czujnik.h>
#include <RF24.h>
#include <LowPower.h>
#include "printf.h"
#include <sleep.h>

#define PAYLOADSIZE 5
#define NADAJNIK
// #define ODBIORNIK

#ifdef NADAJNIK

Czujnik czujnik(2, 3);
RF24 radio(9, 10);
#define POWER_SENSOR_PIN 5
#define POWER_RADIO_PIN 6

const uint8_t adress[][6] = { "1Node", "2Node" }; //TODO zmienić adresy??
//funkcja inicjujaca moduł radiowy
void radioSetup(){
    if (!radio.begin()) {
        Serial.println(F("radio hardware is not responding!!"));
    }
    else{
        Serial.println(F("radio hardware possibly ok"));
    }
    radio.setPALevel(RF24_PA_MIN);
    radio.setDataRate(RF24_250KBPS);
    radio.setRetries(15,10);
    radio.setPayloadSize(PAYLOADSIZE);
    radio.openWritingPipe(adress[1]);
    radio.openReadingPipe(1, adress[0]);
    radio.stopListening();

    // printf_begin(); // needed only once for printing details
    // radio.printDetails(); // (smaller) function that prints raw register values
    // radio.printPrettyDetails(); // (larger) function that prints human readable data
}

void setup()
{
    Serial.begin(9600);

    pinMode(POWER_RADIO_PIN,OUTPUT);
    pinMode(POWER_SENSOR_PIN,OUTPUT);

    // radioSetup();
    // // For debugging info
    // printf_begin(); // needed only once for printing details
    // radio.printDetails(); // (smaller) function that prints raw register values
    // radio.printPrettyDetails(); // (larger) function that prints human readable data
}
int i =0;
void loop()
{


    digitalWrite(POWER_SENSOR_PIN, HIGH); //uruchom sensor
    char buff[3];
    String t(czujnik.zmierz());
    digitalWrite(POWER_SENSOR_PIN, LOW); // wyłącz sensor odległości

    if (t.length() >= 3) {
        for (size_t i = 0; i < 3; i++) {
            buff[i] = t.charAt(i);
        }
    } else if (t.length() == 2) {
        buff[0] = '0';
        for (size_t i = 0; i < 2; i++) {
            buff[i] = t.charAt(i);
        }
    } else if (t.length() == 1) {
        buff[0] = '0';
        buff[1] = '0';
        buff[2] = t.charAt(0);
    }

    digitalWrite(POWER_RADIO_PIN, LOW); //uruchom moduł radiowy
    delay(500);
    // delay(1000);
    radioSetup(); //inicjuj go
    delay(500);
    if (!radio.write(&buff, 3)) {
        // radio.reUseTX();
        Serial.print("Error on sending: ");
        Serial.println(buff);
        Serial.flush();
    }
    else{
        Serial.print("Sent: ");
        Serial.println(buff);
        Serial.flush();
    }
    radio.flush_tx();
    radio.flush_rx();
    // delay(1000);
    digitalWrite(POWER_RADIO_PIN, HIGH); //wylacz moduł radiowy

    
    // i++;
    // if (i==10)
    // {
    //     i=0;

    //     printf_begin(); // needed only once for printing details
    //     radio.printPrettyDetails(); // (larger) function that prints human readable data
    // }
    
    // delay(100);
     Sleep::sleepFor(DAYS(0.5));
    // Sleep::sleepFor(1);
    // LowPower.idle(SLEEP_4S, ADC_OFF, TIMER2_OFF, TIMER1_OFF, TIMER0_OFF, SPI_OFF, USART0_OFF, TWI_OFF);
}

#endif // NADAJNIK


#ifdef ODBIORNIK
RF24 radio(9, 10);

const uint8_t adress[][6] = { "1Node", "2Node" };

int aktualna_odleglosc = 0;

const int min_odleglosc = 50;
const int max_odleglosc = 300;

void setup()
{
    Serial.begin(9600);

    if (!radio.begin()) {
        Serial.println(F("radio hardware is not responding!!"));
    }
    radio.setPALevel(RF24_PA_LOW);
    radio.setPayloadSize(PAYLOADSIZE);
    radio.openWritingPipe(adress[0]);
    radio.openReadingPipe(1, adress[1]);
    radio.startListening();

    // For debugging info
    printf_begin(); // needed only once for printing details
    radio.printDetails(); // (smaller) function that prints raw register values
    radio.printPrettyDetails(); // (larger) function that prints human readable data
}
void loop()
{
    if (radio.available()) {
        char buff[15];
        radio.read(&buff, 15);
        aktualna_odleglosc = String(buff).toInt();
        Serial.print("Otrzymalem: ");
        Serial.println(buff);
    }
    if (aktualna_odleglosc <= min_odleglosc)
    {
      //alarm
    }
    
}
#endif // ODBIORNIK


