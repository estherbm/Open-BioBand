//Screen
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <Wire.h>
//Screen
#define OLED_RESET 0  // GPIO0
Adafruit_SSD1306 display(OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2
//////////

//Buttons
int buttonPushCounter = 1;   // counter for the number of button presses
int buttonState5 = 0;         // current state of the button
int buttonState6 = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button

const int  buttonPin = 11;    // the pin that the Up pushbutton is attached to

const int  buttonPin1 = 12;    // the pin that the Down pushbutton is attached to

void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
  pinMode(buttonPin, INPUT);
   
   pinMode(buttonPin1, INPUT);
   //OLED
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 64x48)
  // init done

  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
  delay(2000);

  // Clear the buffer.
  display.clearDisplay();
 // text display tests
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Steps");
 
   display.display();
   Serial.print(buttonPin);
   Serial.println(buttonPin1);

//////////////////

   
}

void loop() {
   buttonState5 = digitalRead(buttonPin);
   

  // compare the buttonState to its previous state

   if (buttonState5 != lastButtonState) {
     
     // if the state has changed, increment the counter
     
     if (buttonState5 == HIGH)
     {  
      buttonPushCounter++;
       Serial.print(buttonPin);
     Serial.println(buttonPin1);
   
     delay(1500);
     } 
     
   }
   // save the current state as the last state,
  //for next time through the loop
   lastButtonState = buttonState5;
   // read the pushbutton down input pin:
   buttonState6 = digitalRead(buttonPin1);
  // compare the buttonState to its previous state
 
     // if the state has changed, decrement the counter
     if (buttonState6 == HIGH)
     
     {
       
      buttonPushCounter-=1;
 delay(1500);
  
     }
      
        Serial.println(buttonPushCounter);   
         if (buttonPushCounter==1)
       
         {
                  display.clearDisplay();
          display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(20,0);
  display.println("1");
  display.display();
         }
         
         
         if (buttonPushCounter==2)
         
         {
            display.clearDisplay();
          display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(20,0);
  display.println("2");
   display.display();          
         }
          if (buttonPushCounter==3)
         
         {
            display.clearDisplay();
          display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(20,0);
  display.println("3");
    display.display();         
         }
               if (buttonPushCounter==4)
         
         {
            display.clearDisplay();
          display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(20,0);
  display.println("4");
    display.display();         
         }
         
         
         if (buttonPushCounter > 4)
         
         {
            buttonPushCounter=1;
           
         }
          if (buttonPushCounter <= 0)
         
         {
            buttonPushCounter=4;
           
         }
         
        
   
   
   
   // save the current state as the last state,

  //for next time through the loop

   lastButtonState = buttonState6; 
   

}
