//#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <SparkFun_ADXL345.h>
#include <SimpleTimer.h>

ADXL345 adxl = ADXL345();             // USE FOR I2C COMMUNICATION

/****************** VARIABLES ******************/
/*                                             */
int gotUpFlag = 0;                        // Flags first occurance
int wentDownFlag = 0;                     // Flags first occurance
int gotUp = 0;                            // Variable for number of times baby up
unsigned long babyMovingStartTime = 0;    // Will store time when baby starts moving
unsigned long babySleepingStartTime = 0;  // Will store time when baby starts sleeping
unsigned long babySleepingEndTime = 0;    // Will store time when baby wakes up
long TimeLimit = 180000;                  // Notification in 3 minutes when awake
double minutesTimeS = 0;                  // For minute conversion
double minutesTimeA = 0;                  // For minute conversion

SimpleTimer timer;


void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);


  // Notify immediately on startup
  Serial.println("Device Started");           // Notification to smartphone

  // Setup a function to be called every minute
 // timer.setInterval(60000L, refreshTime);

  adxl.powerOn();                     // Power on the ADXL345

  adxl.setRangeSetting(8);            // Give the range settings
                                      // Accepted values are 2g, 4g, 8g or 16g
                                      // Higher Values = Wider Measurement Range
                                      // Lower Values = Greater Sensitivity

  // Set values to zero
  gotUpFlag = 0;
  wentDownFlag = 0;
  gotUp = 0;


 Serial.println("  BABY MONITOR   ");
  
}

void loop() {
  // put your main code here, to run repeatedly:
// ADXL345 Accelerometer Readings
  int x,y,z;   
  adxl.readAccel(&x, &y, &z);         // Read the accelerometer values in variables x,y,z
 // Monitoring Up and Down Time
  if (y >= 50 && y <= 200) {
    if (wentDownFlag == 1){
      babySleepingEndTime = millis();   // Stopped sleeping time            
    }

    
    if (gotUpFlag == 0) {             // If first time baby has gotten up  
      babyMovingStartTime = millis(); // Baby moving start time
      gotUpFlag = 1;                  
      gotUp = gotUp + 1;              // Count the number of times the baby gets up
                                      //  in the middle of the night
    } else {
      checkBaby();
    }
  } else if (y <= 30) {

    
    // Print to VIRTUAL_LCD:

    Serial.println("  BABY SLEEPING  ");

    
    if (wentDownFlag == 0) {
      babySleepingStartTime = millis(); // Baby sleeping start time 
      wentDownFlag = 1;
    } else {
      babySleepingEndTime = millis();   // Stopped sleeping time
    }
    
    if (gotUpFlag == 1) {
      wentDownFlag = 0;                 // Reset flag if baby went back down   
      gotUpFlag = 0;                   
    }
  } else {
    // do nothing                     
  }

  // Write number of times baby has gotten up to Blynk
  //Serial.print(babyMoving)
  Serial.print("gotup");
  Serial.println(gotUp);
  sleepTime();                          // Time aleep
}

/***************** BABY IS AWAKE ***************/
/*             Time to get them yet?           */
void checkBaby() {
  long currentTime = millis();        // Current time
  long upTime = currentTime - babyMovingStartTime; // Time baby awake
  minutesTimeA = upTime * 1.6667E-5;  // Time conversion to minutes

  // Print to VIRTUAL_LCD:
  
 Serial.println( "  BABY MOVING AROUND   ");
  

  // Check to see if baby has been awake for a while 
  if (upTime >= TimeLimit) {
    Serial.println("BABY IS AWAKE!");   // Notification to smartphone
  } else {
    // do nothing
  }

  // Baby awake time
   Serial.print("minutesTimeA");
   Serial.println(minutesTimeA);
// Serial.println(aswakeTime); 
}

/***************** BABY IS Asleep ***************/
/*                But for how long?             */
void sleepTime(){
  // Calculat down time in millis and minutes
  long downTime = babySleepingEndTime - babySleepingStartTime;
  minutesTimeS = downTime * 1.6667E-5;

  // Baby sleeping time
 Serial.print("minutesTimeS");
 Serial.println(minutesTimeS);
//  Serial.println(asleepTimeS); 
}
