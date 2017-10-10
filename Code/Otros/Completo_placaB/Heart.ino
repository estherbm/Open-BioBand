void modeHeart(){
  
if (buttonPushCounter==3){
  long irValue = particleSensor.getIR();
Serial.println(checkForBeat(irValue));
  if (checkForBeat(irValue) == true)
  {
    //We sensed a beat!
    long delta = millis() - lastBeat;
    lastBeat = millis();
     Serial.println(delta);
    beatsPerMinute = 60 / (delta / 1000.0);

    if (beatsPerMinute < 255 && beatsPerMinute > 20)
    {
      rates[rateSpot++] = (byte)beatsPerMinute; //Store this reading in the array
      rateSpot %= RATE_SIZE; //Wrap variable
      Serial.println("hola");
      //Take average of readings
      beatAvg = 0;
      for (byte x = 0 ; x < RATE_SIZE ; x++)
        beatAvg += rates[x];
      beatAvg /= RATE_SIZE;
    }
  }
  Serial.print("IR=");
  Serial.print(irValue);
  Serial.print(", BPM=");
  Serial.print(beatsPerMinute);
  Serial.print(", Avg BPM=");
  Serial.print(beatAvg);


  Serial.println();
  
   buttonState5 = digitalRead(buttonPin);
  buttonState6 = digitalRead(buttonPin1);


  
  

  Serial.println();
  
  display.clearDisplay();

   // text display tests
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(10,28);
  display.println(beatAvg);
   display.display();
   if (irValue < 50000)
    Serial.print(" No finger?");


  Serial.println();
   }
 
  }
