void modeAccel(){
    /////Acc
    int envio=0;
  delay(50); // slow down execution to 20 times per second
  
  Vector norm = accelerometer.readNormalize();

  // Read activities
  Activites activ = accelerometer.readActivites();
 if (buttonPushCounter==2){
        display.clearDisplay();
 // text display tests
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(20,0);
  display.println("steps");
       buttonState5 = digitalRead(buttonPin);
  buttonState6 = digitalRead(buttonPin1);
    //Serial.println('\n');
  //Serial.print("steps=");


   // text display tests
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(10,28);
  display.println(steps);
   display.display();
 



   }
  
        /////Acc
  delay(50); // slow down execution to 20 times per second
  
if (activ.isActivity)
  {
    Serial.println("Activity Detected");
     if (accelerometer.getActivityZ() && flag==0) { Serial.print(" Z ");
      steps=steps+1;
       flag=1;
    String thisString = String(steps);
     Serial.println(steps);
//    Serial1.print(steps); 
 
 
   
 
   }
    else   {flag=0;
 
   
  }
    if (activ.isInactivity)
  {
    Serial.println("Inactivity Detected");
  }
  }
  /////////////////
}

