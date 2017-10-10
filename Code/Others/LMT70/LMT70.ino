#include <Adafruit_GFX.h>
#include <Adafruit_SharpMem.h>

#define SCK 10
#define MOSI 11
#define SS 13

Adafruit_SharpMem display(SCK, MOSI, SS);

#define BLACK 0
#define WHITE 1

//LMT70
float LMT70_AMul = -0.000000001809628;
float LMT70_BMul = -0.000003325395;
float LMT70_CMul = -0.1814103;
float LMT70_DMul = 205.5894;
int LMT70_TON=5;
int LMT70_TAO=A1;

void setup(){
  //Serial.begin(9600);
  pinMode(LMT70_TON, OUTPUT);
 display.begin();
  display.clearDisplay();

  // draw a single pixel
  display.drawPixel(10, 10, BLACK);
  display.refresh();
  delay(500);
  display.clearDisplay();
}

void loop(){
     display.setTextSize(1);
  display.setTextColor(BLACK);
 

  digitalWrite(LMT70_TON, HIGH);

  delay(100);

  float voltage_reading = analogRead(LMT70_TAO);
  float  LMT70_reading = (voltage_reading * 3.3)/1024.0;
  float  LMT70_readingmV = LMT70_reading*1000.0;
  float LMT70_readingC = (LMT70_reading - 0.5) * 100.0;

  float t1 = LMT70_reading - 302.8;  // get rid of voltage offset
  float t2 = t1 * (150.0 + 55.0) / (1375.2 - 302.8); // match range
  float temperatureC = 150 - t2;  // negate and offset.
  
  float A_val = LMT70_AMul * (LMT70_readingmV * LMT70_readingmV * LMT70_readingmV);
  float B_val = LMT70_BMul * (LMT70_readingmV * LMT70_readingmV);
  float C_val = LMT70_CMul * LMT70_readingmV;
  float degC = A_val + B_val + C_val + LMT70_DMul;

  //float Tfinal=((9/5)*degC)+32;
  
  display.setCursor(1, 1);

    display.println(LMT70_readingC);
  display.println(degC);
 
   display.println(temperatureC);
delay(100);
           display.refresh();
    display.clearDisplay();
    

}
