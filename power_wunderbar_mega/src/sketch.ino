#include <EmonLib.h> 
#include <WunderbarBridge.h>
  
Bridge bridge = Bridge(115200);
static bridge_payload_t rxPayload;
  
EnergyMonitor emon;             // Create an instance

  void setup() {	  
    delay(10000);
    if(bridge.begin())
    Serial.print("Bridge Connected\n");
    else
    Serial.print("Bridge Not Connected\n");
    emon.voltage(13, 234.26, 1.7);  // Voltage: input pin, calibration, phase_shift
    emon.current(15, 29);       // Current: input pin, calibration.
  }
  
    static char data[18];
  void sendValue(char t, float d) {
        unsigned char *out = (unsigned char*) data;
        int d100 = (int)(d * 100.0f);
        int size = snprintf(data, 18, "%d", d100);
        bridge.sendData(out, size);
    
    }
  void loop() {
    delay(750);
    //when we receive new data from the cloud on the down channel
    if (bridge.newData){		
      Serial.println("Data Received!\n");  
      rxPayload = bridge.getData();	
      delay(100);
    }
  
    if(bridge.checkConnection()) {
    
    emon.calcVI(20,2000);         // Calculate all. No.of half wavelengths (crossings), time-out
    emon.serialprint();
    
    
//    sendValue('r', (float) emon.realPower);
    sendValue(NULL, (float) emon.apparentPower);
//    sendValue('p', (float) emon.powerFactor);
 //   sendValue('V', (float) emon.Vrms);
  //  sendValue('I', (float) emon.Irms);
   // sendValue('-', 512.0f);
    } else {
    Serial.println("not connected. waiting 2.5s");
    delay(2500);
    }
    //Updates the bridge module with the data it receives on the UART
    if(Serial1.available())
    {
       bridge.processSerial();
    }

    
  }
