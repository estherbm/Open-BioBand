#define LDR_Pin A0 //analog pin 0

#define LIGHTSENSORPIN A1 //Ambient light sensor reading 


#include <SparkFunTSL2561.h>
#include <Wire.h>

SFE_TSL2561 light;

boolean gain;     // Gain setting, 0 = X1, 1 = X16;
unsigned int ms;  // Integration ("shutter") time in milliseconds

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("lux example sketch");
  pinMode(LIGHTSENSORPIN,  INPUT);  
  pinMode(LDR_Pin,  INPUT);  

    light.begin();
      unsigned char ID;
  
  if (light.getID(ID))
  {
    Serial.print("Got factory ID: 0X");
    Serial.print(ID,HEX);
    Serial.println(", should be 0X5X");
  }
    else
  {
    byte error = light.getError();
    printError(error);
  }
    gain = 0;
    
  unsigned char time = 2;
    Serial.println("Set timing...");
  light.setTiming(gain,time,ms);

  // To start taking measurements, power up the sensor:
  
  Serial.println("Powerup...");
  light.setPowerUp();

}

void loop() {
  // put your main code here, to run repeatedly:
  float LDRReading = analogRead(LDR_Pin);
float  LDRReading1=map(LDRReading,0, 1024, 255, 0);
  float reading = analogRead(LIGHTSENSORPIN); //Read light level
   float reading1=map(reading,0, 1024, 0, 255);
  delay(ms);
   unsigned int data0, data1;
  
  if (light.getData(data0,data1))
  {
    // getData() returned true, communication was successful
    
  int   data2=map(data1,0, 5000, 0, 255);
   Serial.print(" data1: ");
   Serial.print(data1);
    Serial.print(" ");
    Serial.println(data2);
    Serial.print("LDR: ");
    Serial.print(LDRReading);
    Serial.print(" ");
    Serial.println(LDRReading1);
    Serial.print("TEMT6000: ");
     Serial.print(reading); 
     Serial.print(" ");
    Serial.println(reading1);  

 }
  else
  {
    // getData() returned false because of an I2C error, inform the user.

    byte error = light.getError();
    printError(error);
  }
}

void printError(byte error)
  // If there's an I2C error, this function will
  // print out an explanation.
{
  Serial.print("I2C error: ");
  Serial.print(error,DEC);
  Serial.print(", ");
  
  switch(error)
  {
    case 0:
      Serial.println("success");
      break;
    case 1:
      Serial.println("data too long for transmit buffer");
      break;
    case 2:
      Serial.println("received NACK on address (disconnected?)");
      break;
    case 3:
      Serial.println("received NACK on data");
      break;
    case 4:
      Serial.println("other error");
      break;
    default:
      Serial.println("unknown error");
  }
}

