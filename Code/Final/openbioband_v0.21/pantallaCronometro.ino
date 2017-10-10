/*******************************************************************************
   Pantalla Cronómetro
 *******************************************************************************/

//!****************************************************************************
//!   Nombre: pantallaCronometro
//!   Descripción: Pantalla de función cronómetro
//!   Parámetro entrada: void
//!   Parámetro salida: void
//!   Ejemplo: pantallaCronometro();
//!****************************************************************************

void pantallaCronometro() {
  
  // Definición logos
  #define anchoIcono 10
  #define altoIcono  10

  static const unsigned char play_img[] PROGMEM =
  {
    0xc0, 0x0,
    0xf0, 0x0,
    0xfc, 0x0,
    0xff, 0x0,
    0xff, 0x80,
    0xff, 0x80,
    0xff, 0x0,
    0xfc, 0x0,
    0xf0, 0x0,
    0xc0, 0x0
  };

  static const unsigned char pause_img[] PROGMEM =
  {
    0x73, 0x80,
    0x73, 0x80,
    0x73, 0x80,
    0x73, 0x80,
    0x73, 0x80,
    0x73, 0x80,
    0x73, 0x80,
    0x73, 0x80,
    0x73, 0x80,
    0x73, 0x80
  };

  static const unsigned char stop_img[] PROGMEM =
  {
    0xff, 0xc0,
    0xff, 0xc0,
    0xff, 0xc0,
    0xff, 0xc0,
    0xff, 0xc0,
    0xff, 0xc0,
    0xff, 0xc0,
    0xff, 0xc0,
    0xff, 0xc0,
    0xff, 0xc0
  };

  // Fuerza el tiempo de Standby para que no vaya a la pantalla principal
  tiempoStandby = millis() + tiempoActivo * 1000; 

  // Control del cronómetro
  display.drawBitmap(80, 80, stop_img, anchoIcono, altoIcono, NEGRO);

  if (botonArriba.wasPressed()) {
    paradaRelojActivo = !paradaRelojActivo;
    if (paradaRelojActivo) {
      display.drawBitmap(80, 80, play_img, anchoIcono, altoIcono, NEGRO);
    }
    else
      display.drawBitmap(80, 80, pause_img, anchoIcono, altoIcono, NEGRO);
  }
  
  if (botonAbajo.wasPressed()) {
    paradaRelojTimer = millis();
    paradaRelojMs = 0;
    display.drawBitmap(80, 80, stop_img, anchoIcono, altoIcono, NEGRO);
  }
  
  if (!paradaRelojActivo) paradaRelojTimer = millis() - paradaRelojMs;
  paradaRelojMs = millis() - paradaRelojTimer;

  // Refresco pantalla
  display.clearDisplay();

  // Visualización cronómetro
  dibujarDigito( 2, 20, ((paradaRelojMs / 60000) / 10), 0);
  dibujarDigito(24, 20, ((paradaRelojMs / 60000) % 10), 0);
  dibujarDigito(52, 20, (paradaRelojMs / 1000 % 60) / 10, 0);
  dibujarDigito(74, 20, (paradaRelojMs / 1000 % 60) % 10, 0);

  display.setCursor(4, 63);
  display.setTextColor(NEGRO, BLANCO);
  display.setTextSize(2);
  
  if (paradaRelojMs % 1000 < 10) display.print(0);
  if (paradaRelojMs % 1000 < 100) display.print(0);
  
  display.print(paradaRelojMs % 1000); display.print("ms");
  display.fillRect(46, 30, 4, 4, 0);
  display.fillRect(46, 46, 4, 4, 0);

  // Control de vuelta a pantalla principal
  if (botonCentral.wasPressed()) {
    paradaRelojActivo = false;
    paradaRelojMs = 0;
    paginaActual = 10;
    botonCentral.read(); // Comprobación de pulsación
  }
}

/*******************************************************************************/


