void modeEnv(){
  //Each loop, take a reading.
  //Start with temperature, as that data is needed for accurate compensation.
  //Reading the temperature updates the compensators of the other functions
  //in the background.
  temperatura=mySensor.readTempC();
  presion=mySensor.readFloatPressure();
  altitud=mySensor.readFloatAltitudeMeters();
  humedad=mySensor.readFloatHumidity();

  if (buttonPushCounter==1){
     buttonState5 = digitalRead(buttonPin);
  buttonState6 = digitalRead(buttonPin1);
      temperatura=mySensor.readTempC();
  presion=mySensor.readFloatPressure();
  altitud=mySensor.readFloatAltitudeMeters();
  humedad=mySensor.readFloatHumidity();
   Serial.print("Temperature: ");
  Serial.print(temperatura, 2);
  Serial.println(" degrees C");

  Serial.print("Pressure: ");
  Serial.print(presion, 2);
  Serial.println(" Pa");

  Serial.print("Altitude: ");
  Serial.print(altitud, 2);
  Serial.println("m"); 

  Serial.print("%RH: ");
  Serial.print(humedad, 2);
  Serial.println(" %");
  
  Serial.println();
   display.clearDisplay();

   // text display tests
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,5);
  display.println(temperatura,2);
   display.setCursor(0,15);
  display.println(humedad,2);
   display.setCursor(0,25);
  display.println(altitud,2);
   display.setCursor(0,35);
  display.println(presion,2);
   display.display();
  delay(1000);
  }
 
}
