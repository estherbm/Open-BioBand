/*******************************************************************************
   Pantalla Principal
 *******************************************************************************/

//!****************************************************************************
//!   Nombre: pantallaPrincipal
//!   Descripción: Pantalla principal de inicio y estado reposo
//!   Parámetro entrada: void
//!   Parámetro salida: void
//!   Ejemplo: pantallaPrincipal();
//!****************************************************************************

void pantallaPrincipal() {
  
  // Definición logos  
  #define anchoBleno 11
  #define altoBleno 14

  static const unsigned char bleno_img[] PROGMEM =
  {
    0xc, 0x0,
    0xa, 0x20,
    0x9, 0x60,
    0x8, 0xe0,
    0x49, 0xc0,
    0x2b, 0x80,
    0x1f, 0x0,
    0xe, 0x0,
    0x1e, 0x0,
    0x39, 0x0,
    0x78, 0x80,
    0xe9, 0x0,
    0xca, 0x0,
    0x8c, 0x0
  };

  #define anchoBlesi 10
  #define altoBlesi 14

  static const unsigned char blesi_img[] PROGMEM =
  {
    0xc, 0x0,
    0xa, 0x0,
    0x9, 0x0,
    0x8, 0x80,
    0x49, 0x0,
    0x2a, 0x0,
    0x1c, 0x0,
    0x1c, 0x0,
    0x2a, 0x0,
    0x49, 0x0,
    0x8, 0x80,
    0x9, 0x0,
    0xa, 0x0,
    0xc, 0x0
  };

  #define anchoBat 22
  #define altoBat 11

  static const unsigned char bat0_img[] PROGMEM =
  {
    0xff, 0xff, 0xf0,
    0xff, 0xff, 0xf0,
    0xc0, 0x0, 0x30,
    0xc0, 0x0, 0x3c,
    0xc0, 0x0, 0x3c,
    0xc0, 0x0, 0x3c,
    0xc0, 0x0, 0x3c,
    0xc0, 0x0, 0x3c,
    0xc0, 0x0, 0x30,
    0xff, 0xff, 0xf0,
    0xff, 0xff, 0xf0
  };

  static const unsigned char bat1_img[] PROGMEM =
  {
    0xff, 0xff, 0xf0,
    0xff, 0xff, 0xf0,
    0xc0, 0x0, 0x30,
    0xd8, 0x0, 0x3c,
    0xd8, 0x0, 0x3c,
    0xd8, 0x0, 0x3c,
    0xd8, 0x0, 0x3c,
    0xd8, 0x0, 0x3c,
    0xc0, 0x0, 0x30,
    0xff, 0xff, 0xf0,
    0xff, 0xff, 0xf0
  };

  static const unsigned char bat2_img[] PROGMEM =
  {
    0xff, 0xff, 0xf0,
    0xff, 0xff, 0xf0,
    0xc0, 0x0, 0x30,
    0xd9, 0x80, 0x3c,
    0xd9, 0x80, 0x3c,
    0xd9, 0x80, 0x3c,
    0xd9, 0x80, 0x3c,
    0xd9, 0x80, 0x3c,
    0xc0, 0x0, 0x30,
    0xff, 0xff, 0xf0,
    0xff, 0xff, 0xf0
  };

  static const unsigned char bat3_img[] PROGMEM =
  {
    0xff, 0xff, 0xf0,
    0xff, 0xff, 0xf0,
    0xc0, 0x0, 0x30,
    0xd9, 0x98, 0x3c,
    0xd9, 0x98, 0x3c,
    0xd9, 0x98, 0x3c,
    0xd9, 0x98, 0x3c,
    0xd9, 0x98, 0x3c,
    0xc0, 0x0, 0x30,
    0xff, 0xff, 0xf0,
    0xff, 0xff, 0xf0
  };

  static const unsigned char bat4_img[] PROGMEM =
  {
    0xff, 0xff, 0xf0,
    0xff, 0xff, 0xf0,
    0xc0, 0x0, 0x30,
    0xd9, 0x99, 0xbc,
    0xd9, 0x99, 0xbc,
    0xd9, 0x99, 0xbc,
    0xd9, 0x99, 0xbc,
    0xd9, 0x99, 0xbc,
    0xc0, 0x0, 0x30,
    0xff, 0xff, 0xf0,
    0xff, 0xff, 0xf0
  };

  static const unsigned char rayo_img[] PROGMEM =
  {
    0x1f, 0x80,
    0x3f, 0x0,
    0x3e, 0x0,
    0x7c, 0x0,
    0x78, 0x0,
    0xfe, 0x0,
    0xfe, 0x0,
    0x1c, 0x0,
    0x38, 0x0,
    0x30, 0x0,
    0x60, 0x0,
    0x40, 0x0
  };

  static const unsigned char logo_img[] PROGMEM =
  {
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x7, 0xf8, 0x0, 0x0, 0x3f, 0xc0, 0x0,
    0x0, 0xf, 0xff, 0x0, 0x0, 0x7f, 0xf0, 0x0,
    0x0, 0x3f, 0xff, 0x80, 0x1, 0xff, 0xfc, 0x0,
    0x0, 0xff, 0xff, 0xe0, 0x7, 0xff, 0xfe, 0x0,
    0x1, 0xff, 0xff, 0xf0, 0xf, 0xff, 0xff, 0x0,
    0x3, 0xff, 0xff, 0xf8, 0x1f, 0xff, 0xff, 0x80,
    0x3, 0xff, 0xff, 0xf8, 0x1f, 0xff, 0xff, 0xc0,
    0x3, 0xff, 0xff, 0xfc, 0x3f, 0xff, 0xff, 0xc0,
    0x7, 0xff, 0xff, 0xfe, 0x7f, 0xff, 0xff, 0xe0,
    0x7, 0xff, 0xff, 0xfe, 0x7f, 0xff, 0xff, 0xe0,
    0xf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
    0xf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
    0xf, 0xff, 0xff, 0x7f, 0xff, 0xff, 0xff, 0xf0,
    0xf, 0xff, 0xfe, 0x3f, 0xff, 0xff, 0xff, 0xf0,
    0x1f, 0xff, 0xfc, 0x3f, 0xff, 0xff, 0xff, 0xf8,
    0x1f, 0xff, 0xfc, 0x1f, 0xff, 0xff, 0xff, 0xf8,
    0x1f, 0xff, 0xfc, 0x1f, 0xff, 0xff, 0xff, 0xf8,
    0x1f, 0xff, 0xf8, 0x1f, 0xff, 0xff, 0xff, 0xf8,
    0x1f, 0xff, 0xf8, 0x1f, 0xff, 0xff, 0xff, 0xf8,
    0x1f, 0xff, 0xf0, 0x1f, 0xff, 0x81, 0xff, 0xf8,
    0xf, 0xff, 0xf0, 0x9f, 0xff, 0x80, 0xff, 0xf0,
    0xf, 0xff, 0xf1, 0x9f, 0xff, 0x0, 0xff, 0xf0,
    0xf, 0xff, 0xf1, 0x8f, 0x80, 0x0, 0xff, 0xf0,
    0xf, 0xff, 0xf1, 0x8f, 0x0, 0x0, 0xff, 0xf0,
    0x0, 0x0, 0x3, 0xcf, 0x0, 0x0, 0xff, 0xf0,
    0x0, 0x0, 0x7, 0xc6, 0x3f, 0x0, 0xff, 0xe0,
    0x3f, 0xff, 0xff, 0xe6, 0x3f, 0x80, 0xff, 0xc0,
    0x7f, 0xff, 0xff, 0xe6, 0x3f, 0x81, 0xff, 0xc0,
    0x7f, 0xff, 0xff, 0xe0, 0x3f, 0xff, 0xff, 0x80,
    0x7f, 0xff, 0xff, 0xe0, 0x7f, 0xff, 0xff, 0x80,
    0x3f, 0xff, 0xff, 0xe0, 0x7f, 0xff, 0xff, 0x0,
    0x0, 0x7f, 0xff, 0xe0, 0x7f, 0xff, 0xfe, 0x0,
    0x0, 0x1f, 0xff, 0xf0, 0xff, 0xff, 0xfc, 0x0,
    0x0, 0xf, 0xff, 0xf0, 0xff, 0xff, 0xf8, 0x0,
    0x0, 0x7, 0xff, 0xf0, 0xff, 0xff, 0xf0, 0x0,
    0x0, 0x3, 0xff, 0xf0, 0xff, 0xff, 0xc0, 0x0,
    0x0, 0x1, 0xff, 0xf9, 0xff, 0xff, 0x80, 0x0,
    0x0, 0x0, 0xff, 0xff, 0xff, 0xff, 0x0, 0x0,
    0x0, 0x0, 0x7f, 0xff, 0xff, 0xfe, 0x0, 0x0,
    0x0, 0x0, 0x3f, 0xff, 0xff, 0xf8, 0x0, 0x0,
    0x0, 0x0, 0xf, 0xff, 0xff, 0xf0, 0x0, 0x0,
    0x0, 0x0, 0x7, 0xff, 0xff, 0xe0, 0x0, 0x0,
    0x0, 0x0, 0x3, 0xff, 0xff, 0xc0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0xff, 0xff, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x7f, 0xfe, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x3f, 0xfc, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x1f, 0xf8, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0xf, 0xf0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x7, 0xe0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x7, 0xe0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x3, 0xc0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x1, 0x80, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0
  };

  // Refresco pantalla
  display.clearDisplay();

  // Visualización pantalla principal
  display.drawBitmap(18, 20, logo_img, 62, 54, NEGRO);
  display.setCursor(12, 78);
  display.setTextSize(1);
  display.print("Open Bioband");
  if ( ble.isConnected()){
  display.drawBitmap(3, 2, blesi_img, anchoBlesi, altoBlesi, NEGRO);}
  else  display.drawBitmap(3, 2, bleno_img, anchoBleno, altoBleno, NEGRO);

  // Visualización nivel de batería
  //  4.2 = 100% (máximo voltaje, máxima carga)
  //  3.2 = 0%   (mínimo voltaje de seguridad)
  if (visualizacionVoltaje) {
    // Evitamos valores negativos
    if (porcentajeBateria <= 0)
    {
      porcentajeBateria = 0;
    }

    // Comprobación estado carga batería
    int carga = digitalRead(CHGPIN);

    // Cálculo de nivel de batería
    if (carga == HIGH) {
      unsigned int batVoltage = leerVoltage();
      porcentajeBateria = ((batVoltage * 0.1) - 320); // Fórmula para mostrar el porcentaje de carga

      // Visualización de nivel de batería
      display.setCursor(52, 4);
      display.setTextColor(NEGRO, BLANCO);
      display.print(porcentajeBateria); 
      display.print("%");
      
     
      if (porcentajeBateria <= 10)
      { 
        display.drawBitmap(72, 2, bat0_img, anchoBat, altoBat, NEGRO);
        estadoBateria = 0;
      }

      if ((porcentajeBateria > 10) && (porcentajeBateria < 26)) {
        display.drawBitmap(72, 2, bat1_img, anchoBat, altoBat, NEGRO);
        estadoBateria = 1;
      }

      if ((porcentajeBateria > 25) && (porcentajeBateria < 51)) {
        display.drawBitmap(72, 2, bat2_img, anchoBat, altoBat, NEGRO);
        estadoBateria = 2;
      }
      if ((porcentajeBateria > 50) && (porcentajeBateria < 76)) {
        display.drawBitmap(72, 2, bat3_img, anchoBat, altoBat, NEGRO);
        estadoBateria = 3;
      }

      if ((porcentajeBateria > 75) && (porcentajeBateria < 101)) {
        display.drawBitmap(72, 2, bat4_img, anchoBat, altoBat, NEGRO);
        estadoBateria = 4;
      }
    }

    // Visualización carga batería
    if (carga == LOW) {
      // Inicializacion actualización pantalla
      tiempoStandby = millis() + tiempoActivo * 1000; 

      // Visualización logo nivel de batería
      display.drawBitmap(61, 2, rayo_img, 9, 12, NEGRO);
      estadoBateria++;
      
      if (estadoBateria > 4) {
        estadoBateria = 0;
      }
      
      switch (estadoBateria) {
        case 0:
          display.drawBitmap(72, 2, bat0_img, anchoBat, altoBat, NEGRO);
          delay(100);
          break;
        case 1:
          display.drawBitmap(72, 2, bat1_img, anchoBat, altoBat, NEGRO);
          delay(100);
          break;
        case 2:
          display.drawBitmap(72, 2, bat2_img, anchoBat, altoBat, NEGRO);
          delay(100);
          break;
        case 3:
          display.drawBitmap(72, 2, bat3_img, anchoBat, altoBat, NEGRO);
          delay(100);
        case 4:
          display.drawBitmap(72, 2, bat4_img, anchoBat, altoBat, NEGRO);
          delay(200);
          break;
      }
    }
  }
}

/*******************************************************************************/


