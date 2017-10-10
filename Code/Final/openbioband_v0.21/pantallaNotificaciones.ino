/*******************************************************************************
   Pantalla Notificaciones
 *******************************************************************************/

//!****************************************************************************
//!   Nombre: pantallaNotificaciones
//!   Descripción: Pantalla de indicación de notificaciones del teléfono
//!   Parámetro entrada: void
//!   Parámetro salida: void
//!   Ejemplo: pantallaNotificaciones();
//!****************************************************************************

void pantallaNotificaciones() {
  
  // Definición logos  
  static const unsigned char fb_img[] PROGMEM =
  {
    0xf, 0x0,
    0x3f, 0xc0,
    0x78, 0xe0,
    0x7b, 0xe0,
    0xfb, 0xf0,
    0xf0, 0xf0,
    0xfb, 0xf0,
    0xfb, 0xf0,
    0x7b, 0xe0,
    0x7b, 0xe0,
    0x3f, 0xc0,
    0xf, 0x0
  };
  
  static const unsigned char twit_img[] PROGMEM =
  {
    0xf, 0x0,
    0x3f, 0xc0,
    0x7f, 0xe0,
    0x73, 0xe0,
    0xf0, 0xf0,
    0xf0, 0xf0,
    0xf3, 0xf0,
    0xf0, 0xf0,
    0x70, 0xe0,
    0x7f, 0xe0,
    0x3f, 0xc0,
    0xf, 0x0
  };
  
  static const unsigned char text_img[] PROGMEM =
  {
    0xf, 0x0,
    0x3f, 0xc0,
    0x7f, 0xe0,
    0x40, 0x20,
    0xcf, 0x30,
    0xd6, 0xb0,
    0xd9, 0xb0,
    0xdf, 0xb0,
    0x40, 0x20,
    0x7f, 0xe0,
    0x3f, 0xc0,
    0xf, 0x0
  };

  static const unsigned char call_img[] PROGMEM =
  {
    0xf, 0x0,
    0x3f, 0xc0,
    0x7f, 0xe0,
    0x77, 0xe0,
    0xe7, 0xf0,
    0xe7, 0xf0,
    0xf3, 0xf0,
    0xf8, 0x70,
    0x7c, 0xe0,
    0x7f, 0xe0,
    0x3f, 0xc0,
    0xf, 0x0
  };

  static const unsigned char what_img[] PROGMEM =
  {
    0x1f, 0x80,
    0x70, 0xe0,
    0x40, 0x20,
    0xc8, 0x30,
    0x98, 0x10,
    0x98, 0x10,
    0x8c, 0x10,
    0x87, 0x90,
    0xc3, 0x30,
    0x40, 0x20,
    0xb0, 0xe0,
    0xdf, 0x80
  };

  // Refresco pantalla
  display.clearDisplay();

  // Visualización notificaciones
  display.drawBitmap(28, 10, fb_img, 12, 12, NEGRO);
  display.setCursor(45, 13);
  display.print("0");
  display.drawBitmap(28, 25, twit_img, 12, 12, NEGRO);
  display.setCursor(45, 28);
  display.print("0");
  display.drawBitmap(28, 40, what_img, 12, 12, NEGRO);
  display.setCursor(45, 43);
  display.print("0");
  display.drawBitmap(28, 55, text_img, 12, 12, NEGRO);
  display.setCursor(45, 58);
  display.print("0");
  display.drawBitmap(28, 70, call_img, 12, 12, NEGRO);
  display.setCursor(45, 73);
  display.print("0");

  // Control de vuelta a pantalla principal    
  if (botonCentral.wasPressed()) {
    paginaActual = 10; 
    botonCentral.read(); // Comprobación de pulsación
  }
}

/*******************************************************************************/


