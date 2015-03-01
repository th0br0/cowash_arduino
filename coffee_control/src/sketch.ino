#include <WunderbarBridge.h>

Bridge bridge = Bridge(115200);
static char dataOut[18];
const uint8_t leds[] = {108, 101, 100};

int on = 1;
bool helo = false;
void setup()
{  
  bridge.setBridgePort(3);
  if(bridge.begin()) 
  Serial.println("Bridge connected\n");
  else
  Serial.println("Bridge Not Connected\n");
  Serial.println("go.");

  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);

  pinMode(39, OUTPUT);
  digitalWrite(39, LOW);

  snprintf(dataOut, 18, "input. %d", 42);
}

void checkRx() {
    static bridge_payload_t rxPayload;
    
    rxPayload = bridge.getData();
    Serial.println((char*)rxPayload.payload);

    if(memcmp(leds, rxPayload.payload, 3) == 0) {
        digitalWrite(39, on ? LOW: HIGH);
        on = !on;
    }

    delay(100);
}

void serialEvent3() {
    Serial.println("serialEvent3!");
    bridge.processSerial();
}

void loop()
{
    delay(25000);
    digitalWrite(39, HIGH);
    delay(60000);

  /*  delay(750);
    if(bridge.newData) {
        Serial.println("Data received!");
        checkRx();
        delay(100);
    }
    
    if(bridge.checkConnection()) {
        if(!helo) {
            helo = true;
            Serial.println("Helo.");
            int i = 0;
            while(i < 5) {
                bridge.sendData((uint8_t*) dataOut, 1+i);
                delay(1000);
                i++;
            }
        }
    }
*/
    bridge.processSerial();
}
