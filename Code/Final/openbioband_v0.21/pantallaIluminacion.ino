/*******************************************************************************
   Pantalla Iluminación
 *******************************************************************************/

//!****************************************************************************
//!   Nombre: pantallaIluminacion
//!   Descripción: Pantalla de medición y control de iluminación
//!   Parámetro entrada: void
//!   Parámetro salida: void
//!   Ejemplo: pantallaIluminacion();
//!****************************************************************************

void pantallaIluminacion() {
  
  static const unsigned char lint_img[] PROGMEM =
  {
    0x0, 0x0, 0x78,
    0x0, 0x1, 0xc8,
    0x0, 0x7, 0x48,
    0xff, 0xfe, 0x48,
    0xff, 0xf8, 0x48,
    0x80, 0x0, 0x48,
    0x80, 0x0, 0x48,
    0x81, 0xe0, 0x48,
    0x80, 0x0, 0x48,
    0x80, 0x0, 0x48,
    0xff, 0xf8, 0x48,
    0xff, 0xfe, 0x48,
    0x0, 0x7, 0x48,
    0x0, 0x1, 0xc8,
    0x0, 0x0, 0x78
  };
  static const unsigned char luz_img[] PROGMEM =
  {
    0x1, 0x0,
    0x41, 0x4,
    0x21, 0x8,
    0x10, 0x10,
    0x3, 0x80,
    0x6, 0xc0,
    0xc, 0x60,
    0xe8, 0x2e,
    0xc, 0x60,
    0x6, 0xc0,
    0x3, 0x80,
    0x10, 0x10,
    0x21, 0x8,
    0x41, 0x4,
    0x1, 0x0
  };

  // Refresco pantalla
  display.clearDisplay();

  // Control iluminación
  display.drawBitmap(10, 20, lint_img, 21, 15, NEGRO);
  display.drawBitmap(10, 53, luz_img, 15, 15, NEGRO);

  if (botonArriba.wasPressed()) menuIluminacion--;
  if (botonAbajo.wasPressed()) menuIluminacion++;

  if (menuIluminacion > 3 && menuIluminacion < 99) menuIluminacion = 1; 
  else if (menuIluminacion > 99) menuIluminacion = 3;

  // Visualización iluminación
  estadoIluminacion = menuIluminacion;
  display.setTextColor(NEGRO, BLANCO);

  display.setCursor(30, 57);
  display.print(lux);
  display.println("lux");

  switch (estadoIluminacion) {
    case 1:
      boolean good;
      display.setCursor(37, 24);
      display.print(F("Auto"));
      break;
    case 2:
      display.setCursor(37, 24);
      display.print(F("On"));
      break;
    case 3:
      display.setCursor(37, 24);
      display.print(F("Off"));
      break;
  }

  // Control de vuelta a pantalla principal  
  if (botonCentral.wasPressed()) {
    paginaActual = 10; 
    botonCentral.read(); // Comprobación de pulsación
  }
}

/*******************************************************************************/


