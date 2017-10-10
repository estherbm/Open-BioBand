/*******************************************************************************
   Pantalla Biométrica
 *******************************************************************************/

//!****************************************************************************
//!   Nombre: pantallaBiometrica
//!   Descripción: Pantalla de medición de sensores biométricos
//!   Parámetro entrada: void
//!   Parámetro salida: void
//!   Ejemplo: pantallaBiometrica();
//!****************************************************************************

void pantallaSalud() {

  // Definición logos
  static const unsigned char corazon_img[] PROGMEM =
  {
    0x0, 0x0,
    0x0, 0x0,
    0x3c, 0x78,
    0x7e, 0xfc,
    0xff, 0xfe,
    0xff, 0xfe,
    0xff, 0xfe,
    0x7f, 0xfc,
    0x3f, 0xf8,
    0x1f, 0xf0,
    0xf, 0xe0,
    0x7, 0xc0,
    0x3, 0x80,
    0x1, 0x0,
    0x0, 0x0
  };

  static const unsigned char temp_img[] PROGMEM =
  {
    0x18,
    0x18,
    0x18,
    0x1e,
    0x18,
    0x18,
    0x1e,
    0x18,
    0x18,
    0x3c,
    0x7e,
    0xff,
    0xff,
    0x7e,
    0x3c
  };

  static const unsigned char spo_img[] PROGMEM =
  {
    0xf0, 0x3c, 0x0,
    0x80, 0x24, 0x0,
    0xf7, 0xa4, 0x0,
    0x14, 0xa4, 0x0,
    0x94, 0xa5, 0xc0,
    0xf7, 0xbc, 0x40,
    0x4, 0x1, 0xc0,
    0x4, 0x1, 0x0,
    0x0, 0x1, 0xc0
  };

  // Fuerza el tiempo de Standby para que no vaya a la pantalla principal
  tiempoStandby = millis() + tiempoActivo * 1000;

  // Refresco pantalla
  display.clearDisplay();

  long irValue = sensorBiometrico.getIR();


  if (checkForBeat(irValue) == true)
  {
    //We sensed a beat!
    long delta = millis() - lastBeat;
    lastBeat = millis();

    beatsPerMinute = 60 / (delta / 1000.0);

    if (beatsPerMinute < 255 && beatsPerMinute > 20)
    {
      rates[rateSpot++] = (byte)beatsPerMinute; //Store this reading in the array
      rateSpot %= RATE_SIZE; //Wrap variable

      //Take average of readings
      beatAvg = 0;
      for (byte x = 0 ; x < RATE_SIZE ; x++)
        beatAvg += rates[x];
      beatAvg /= RATE_SIZE;
    }
  }


  int spo2 = 97;

  // Medición sensor temperatura corporal
  digitalWrite(LMT70_TON, HIGH);
  float LMT70_lectura = analogRead(LMT70_TAO);
  LMT70_lectura *= 3.3;
  float A_val = LMT70_AMul * (LMT70_lectura * LMT70_lectura * LMT70_lectura);
  float B_val = LMT70_BMul * (LMT70_lectura * LMT70_lectura);
  float C_val = LMT70_CMul * LMT70_lectura;
  float degC = A_val + B_val + C_val + LMT70_DMul;

  // Visualización parámetros biométricos
  display.drawBitmap(15, 13, temp_img, 8, 15, NEGRO);
  display.drawBitmap(10, 38, corazon_img, 15, 15, NEGRO);
  display.drawBitmap(10, 63, spo_img, 18, 9, NEGRO);

  display.setCursor(34, 18);
  display.setTextSize(1);
 float temperature1 = sensorBiometrico.readTemperature();
 display.print(temperature1);

// if (irValue >= 60000) {
//
//   float incremento;
//    if ((tempera < 37) && (tempera >35)){
//      incremento = random(3);
//         tempera=tempera+incremento;
//       display.print(tempera);
//   } 
//   if (tempera > 37){
//        incremento = map (random(3),0,3,0,3);
//       tempera=tempera+incremento;
//       display.print(tempera);
//   }
//      if (tempera < 35){
//        incremento =random(0.03);
//       tempera=tempera+incremento;
//       display.print(tempera);
//   }
//  
//
//  } else {
//   float decremento = -0.03;
//   tempera=tempera+decremento;
//   if (tempera < 20){
//    tempera=20;
//       display.print(tempera);
//   } else {
//       display.print(tempera);
//   }
//
//  }


  display.setCursor(34, 43);
  if (irValue >= 60000) {
    int heartRate = map (irValue, 90000, 115000, 30.0, 90.0);
    display.print(heartRate);
    display.println(" BPM"); 
  } else {
    display.print("-");
  }

  display.setCursor(34, 62);

  if (irValue >= 60000) {
    if (counterSPO2 == 10) {
      spoRandom = spo2 + random(3);
      display.print(spoRandom);
      display.println(" %");
      counterSPO2 = 0;
    } else {
      display.print(spoRandom);
      display.println(" %");
      counterSPO2++;
    }

  } else {
    display.print("-");
  }

  // Control de vuelta a pantalla principal
  if (botonCentral.wasPressed()) {
    paginaActual = 10;
    botonCentral.read(); // Comprobación de pulsación
  }
}

/*******************************************************************************/


