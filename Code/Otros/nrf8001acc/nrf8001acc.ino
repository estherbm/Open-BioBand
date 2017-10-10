/*
    ADXL345 Triple Axis Accelerometer. Tap & Double Tap
    Read more: http://www.jarzebski.pl/arduino/czujniki-i-sensory/3-osiowy-akcelerometr-adxl345.html
    GIT: https://github.com/jarzebski/Arduino-ADXL345
    Web: http://www.jarzebski.pl
    (c) 2014 by Korneliusz Jarzebski
*/

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

const int led = 3;
char val = 'x' ;
uint8_t sendbuffer[20];

ADXL345 accelerometer;

void setup(void) 
{
  Serial.begin(9600);
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

  // Set tap detection on Z-Axis
  accelerometer.setTapDetectionX(0);       // Don't check tap on X-Axis
  accelerometer.setTapDetectionY(0);       // Don't check tap on Y-Axis
  accelerometer.setTapDetectionZ(1);       // Check tap on Z-Axis
  // or
  // accelerometer.setTapDetectionXYZ(1);  // Check tap on X,Y,Z-Axis

  accelerometer.setTapThreshold(2.5);      // Recommended 2.5 g
  accelerometer.setTapDuration(0.02);      // Recommended 0.02 s
  accelerometer.setDoubleTapLatency(0.10); // Recommended 0.10 s
  accelerometer.setDoubleTapWindow(0.30);  // Recommended 0.30 s

  // Select INT 1 for get activities
  accelerometer.useInterrupt(ADXL345_INT1);

  // Check settings
  checkSetup();
}
aci_evt_opcode_t laststatus = ACI_EVT_DISCONNECTED;

void checkSetup()
{
  Serial.print("Look tap on axis = "); 
  if (accelerometer.getTapDetectionX()) { Serial.print(" X "); }
  if (accelerometer.getTapDetectionY()) { Serial.print(" Y "); }
  if (accelerometer.getTapDetectionZ()) { Serial.print(" Z "); }
  Serial.println();

  Serial.print("Tap Threshold = "); Serial.println(accelerometer.getTapThreshold());
  Serial.print("Tap Duration = "); Serial.println(accelerometer.getTapDuration());
  Serial.print("Double Tap Latency = "); Serial.println(accelerometer.getDoubleTapLatency());
  Serial.print("Double Tap Window = "); Serial.println(accelerometer.getDoubleTapWindow());
}

void loop(void) 
{
  delay(50); // slow down execution to 20 times per second
  
  // Tell the nRF8001 to do whatever it should be working on.
  BTLEserial.pollACI();

  // Ask what is our current status
  aci_evt_opcode_t status = BTLEserial.getState();

  if (status == ACI_EVT_CONNECTED) {
      
    // Lets see if there's any data for us!
    // OK while we still have something to read, get a character and print it out
   //while (BTLEserial.available()) {
    
  // Read values for activities
  delay(50);
  Vector norm = accelerometer.readNormalize();

  // Read activities
  Activites activ = accelerometer.readActivites();

  if (activ.isDoubleTap)
  {
    Serial.println("Double Tap Detected");
  } else
  if (activ.isTap)
  {
     sendData("/nTapDetected");
  }
    Serial.println("Tap Detected");
    
 // }
}
}

void sendData(String Send)
{
  Send.getBytes(sendbuffer, 20);
  char sendbuffersize = min(20, Send.length());
  // write the data
  BTLEserial.write(sendbuffer, sendbuffersize);
}


