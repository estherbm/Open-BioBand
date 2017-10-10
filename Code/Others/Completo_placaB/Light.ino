void modeLight(){
  ////////Light Sensor
/* Get a new sensor event */ 
  sensors_event_t event;
  tsl.getEvent(&event);
 if (buttonPushCounter==4){
   buttonState5 = digitalRead(buttonPin);
  buttonState6 = digitalRead(buttonPin1);
    sensors_event_t event;
  tsl.getEvent(&event);
  if (event.light)
  {
    Serial.print(event.light); Serial.println(" lux");
      display.clearDisplay();

   // text display tests
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(10,0);
  display.println(event.light);
   display.display();
  delay(1000);
  }
  else
  {
    /* If event.light = 0 lux the sensor is probably saturated
       and no reliable data could be generated! */
    Serial.println("Sensor overload");
  }}

  }
