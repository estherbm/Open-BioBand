void modeAccel(){
  
    if (buttonPushCounter==2){
digitalWrite(12, HIGH);
 xl.readXYZTData(XValue, YValue, ZValue, Temperature);  
  Serial.print("XVALUE=");
  Serial.print(XValue);   
  Serial.print("\tYVALUE=");
  Serial.print(YValue);  
  Serial.print("\tZVALUE=");
  Serial.print(ZValue);  
  Serial.print("\tTEMPERATURE=");
  Serial.println(Temperature);  
        display.clearDisplay();
 // text display tests
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("x");
       buttonState5 = digitalRead(buttonPin);
  buttonState6 = digitalRead(buttonPin1);
     display.setCursor(0,15);
  display.println("y");
   display.setCursor(0,30);
  display.println("z");
  display.setCursor(30,0);
  display.println(XValue);
display.setCursor(30,15);
  display.println(YValue);
display.setCursor(30,30);
     display.println(ZValue);
   display.display();
  
   digitalWrite(12, LOW);
   
    digitalWrite(12, HIGH);
   }
   }


