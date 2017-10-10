/*******************************************************************************
   Pantalla Ambiente
 *******************************************************************************/

//!****************************************************************************
//!   Nombre: pantallaAmbiente
//!   Descripción: Pantalla de visualización de parámetros ambientales
//!   Parámetro entrada: void
//!   Parámetro salida: void
//!   Ejemplo: pantallaAmbiente();
//!****************************************************************************

void pantallaAmbiente() {

  // Definición logos
  static const unsigned char temp_img[] PROGMEM =
  {
    0x30,
    0x30,
    0x30,
    0x38,
    0x30,
    0x38,
    0x30,
    0x78,
    0xfc,
    0x78,
    0x30
  };
  
  static const unsigned char alt_img[] PROGMEM =
  {
    0x8, 0x0,
    0x1c, 0x0,
    0x1c, 0x0,
    0x3e, 0x0,
    0x3e, 0x20,
    0x7f, 0x70,
    0x7f, 0xf8,
    0xff, 0xf8,
    0xff, 0xfc,
    0xff, 0xfe
  };
  
  static const unsigned char hum_img[] PROGMEM =
  {
    0x10,
    0x38,
    0x38,
    0x7c,
    0x7c,
    0xfe,
    0xfe,
    0xfe,
    0xfe,
    0x7c
  };
  
  static const unsigned char pres_img[] PROGMEM =
  {
    0x1f, 0x0,
    0x31, 0x80,
    0x60, 0xc0,
    0x42, 0x40,
    0x44, 0x40,
    0x40, 0x40,
    0x60, 0xc0,
    0x31, 0x80,
    0x1f, 0x0,
    0xa, 0x0,
    0xff, 0xe0,
    0xff, 0xe0
  };

  // Medición sensor parámetros ambientales
  temperatura = sensorAmbiente.readTempC();
  presion = sensorAmbiente.readFloatPressure();
  altitud = sensorAmbiente.readFloatAltitudeMeters();
  humedad = sensorAmbiente.readFloatHumidity();

  // Refresco pantalla
  display.clearDisplay();

  // Visualización parámetros ambientales
  display.setTextColor(NEGRO, BLANCO);
  
  display.drawBitmap(6, 20, temp_img, 6, 11, NEGRO);
  display.setCursor(21, 23);
  display.print("Temp:");
  display.print(temperatura-6.0, 2); display.print("C");

  display.drawBitmap(6, 35, hum_img, 7, 10, NEGRO);
  display.setCursor(21, 37);
  display.print("Hum:");
  display.print(humedad, 2); display.print("%");

  display.drawBitmap(3, 50, alt_img, 15, 10, NEGRO);
  display.setCursor(21, 52);
  display.print("Alt:");
  display.print(altitud, 2); display.print("m");

  display.drawBitmap(5, 65, pres_img, 11, 12, NEGRO);
  display.setCursor(21, 68);
  display.print("Pre:");
  display.print(presion / 1000, 2); display.print("KPa");

  delay(50);

  // Control de vuelta a pantalla principal
  if (botonCentral.wasPressed()) {
    paginaActual = 10;
    botonCentral.read(); // Comprobación de pulsación
  }
}

/*******************************************************************************/


