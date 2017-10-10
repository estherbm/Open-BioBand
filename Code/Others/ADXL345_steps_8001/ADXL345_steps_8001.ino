/*
    ADXL345 Triple Axis Accelerometer. Activity & Inactivity
    Read more: http://www.jarzebski.pl/arduino/czujniki-i-sensory/3-osiowy-akcelerometr-adxl345.html
    GIT: https://github.com/jarzebski/Arduino-ADXL345
    Web: http://www.jarzebski.pl
    (c) 2014 by Korneliusz Jarzebski
*/
#include <SPI.h>
#include <Wire.h>
#include <ADXL345.h>


#include <SPI.h>
#include "Adafruit_BLE_UART.h"

// Connect CLK/MISO/MOSI to hardware SPI
// e.g. On UNO & compatible: CLK = 13, MISO = 12, MOSI = 11
#define ADAFRUITBLE_REQ 10
#define ADAFRUITBLE_RDY 2     // This should be an interrupt pin, on Uno thats #2 or #3
#define ADAFRUITBLE_RST 9


Adafruit_BLE_UART BTLEserial = Adafruit_BLE_UART(ADAFRUITBLE_REQ, ADAFRUITBLE_RDY, ADAFRUITBLE_RST);

uint8_t sendbuffer[20];
String cadena;



int steps,flag=0;

ADXL345 accelerometer;

void setup(void) 
{
  Serial.begin(9600);
  pinMode(8, INPUT);
  digitalWrite(8, HIGH); 
  while(!Serial); // Leonardo/Micro should wait for serial init
  Serial.println(F("Adafruit Bluefruit Low Energy nRF8001 Print echo demo"));

 // BTLEserial.setDeviceName("LIGHT"); /* 7 characters max! */
  BTLEserial.begin();




  // Initialize ADXL345
  Serial.println("Initialize ADXL345");

  if (!accelerometer.begin())
  {
    Serial.println("Could not find a valid ADXL345 sensor, check wiring!");
    delay(500);
  }

  // Values for Activity and Inactivity detection
  accelerometer.setActivityThreshold(2.0);    // Recommended 2 g
  accelerometer.setInactivityThreshold(2.0);  // Recommended 2 g
  accelerometer.setTimeInactivity(5);         // Recommended 5 s

  // Set activity detection only on X,Y,Z-Axis
  accelerometer.setActivityXYZ(1);         // Check activity on X,Y,Z-Axis
  // or
  // accelerometer.setActivityX(1);        // Check activity on X_Axis
  // accelerometer.setActivityY(1);        // Check activity on Y-Axis
  // accelerometer.setActivityZ(1);        // Check activity on Z-Axis

  // Set inactivity detection only on X,Y,Z-Axis
  accelerometer.setInactivityXYZ(1);       // Check inactivity on X,Y,Z-Axis
  // or
  // accelerometer.setInactivityX(1);      // Check inactivity on X_Axis
  // accelerometer.setInactivityY(1);      // Check inactivity on Y-Axis
  // accelerometer.setInactivityZ(1);      // Check inactivity on Z-Axis

  // Select INT 1 for get activities
  accelerometer.useInterrupt(ADXL345_INT1);

  // Check settings
  checkSetup();
}
aci_evt_opcode_t laststatus = ACI_EVT_DISCONNECTED;

void checkSetup()
{
  Serial.print("Activity Threshold = "); Serial.println(accelerometer.getActivityThreshold());
  Serial.print("Inactivity Threshold = "); Serial.println(accelerometer.getInactivityThreshold());
  Serial.print("Time Inactivity = "); Serial.println(accelerometer.getTimeInactivity());

  Serial.print("Look activity on axis = "); 
  if (accelerometer.getActivityX()) { Serial.print(" X "); }
  if (accelerometer.getActivityY()) { Serial.print(" Y "); }
  if (accelerometer.getActivityZ()) { Serial.print(" Z ");}
  
  Serial.println();

  Serial.print("Look inactivity on axis = "); 
  if (accelerometer.getInactivityX()) { Serial.print(" X "); }
  if (accelerometer.getInactivityY()) { Serial.print(" Y "); }
  if (accelerometer.getInactivityZ()) { Serial.print(" Z "); }
  Serial.println();  
}

void loop(void) 
{
  delay(50); // slow down execution to 20 times per second
  
  // Tell the nRF8001 to do whatever it should be working on.
  BTLEserial.pollACI();

  // Ask what is our current status
  aci_evt_opcode_t status = BTLEserial.getState();

  if (status == ACI_EVT_CONNECTED) {
  // Read values for activities
  delay(50);
  Vector norm = accelerometer.readNormalize();

  // Read activities
  Activites activ = accelerometer.readActivites();

  if (activ.isActivity)
  {
    Serial.println("Activity Detected");
     if (accelerometer.getActivityZ() && flag==0) { Serial.print(" Z ");
      steps=steps+1;
       flag=1;
   }
    else   {flag=0;
    Serial.println('\n');
  Serial.print("steps=");
  Serial.println(steps);
   
String thisString = String(steps);

   sendData(thisString);

   }

  }

  if (activ.isInactivity)
  {
    Serial.println("Inactivity Detected");
  }
}
}
void sendData(String Send)
{
  Send.getBytes(sendbuffer, 20);
  char sendbuffersize = min(20, Send.length());
  // write the data
  BTLEserial.write(sendbuffer, sendbuffersize);
}


