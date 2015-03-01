#include <Sodaq_Mbili.h>

#define RELAY1 PD4
#define RELAY2 20
void setup()
{
    pinMode(LED1, OUTPUT);
    pinMode(RELAY1, OUTPUT); // eco
    pinMode(RELAY2, OUTPUT); // start

    digitalWrite(RELAY1, LOW);
    digitalWrite(RELAY2, LOW);
}

void loop()
{
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(RELAY1, HIGH);
    delay(750);
    digitalWrite(LED2, LOW);
    digitalWrite(RELAY1, LOW);
    digitalWrite(RELAY2, HIGH);
    delay(1000);
    digitalWrite(RELAY2, LOW);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    delay(30000);
}
