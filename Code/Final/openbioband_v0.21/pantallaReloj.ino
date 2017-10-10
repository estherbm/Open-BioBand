/*******************************************************************************
   Pantalla Reloj
 *******************************************************************************/

//!****************************************************************************
//!   Nombre: pantallaAjustes
//!   Descripción: Pantalla de ajustes de parámetros de generales de navegación
//!   Parámetro entrada: void
//!   Parámetro salida: void
//!   Ejemplo: pantallaAjustes();
//!****************************************************************************

void pantallaReloj() {

  // Refresco pantalla
  display.clearDisplay();

  // Visualización de la hora
  dibujarDigito( 2, 20, d_hora, 0);
  dibujarDigito(24, 20, u_hora, 0);
  dibujarDigito(52, 20, d_minuto, 0);
  dibujarDigito(74, 20, u_minuto, 0);
  
  display.fillRect(46, 30, 4, 4, 0);
  display.fillRect(46, 46, 4, 4, 0);
  
  display.setCursor(4, 63);
  display.setTextColor(NEGRO, BLANCO);
  display.setTextSize(2);
  display.print(d_segundo); 
  display.print(u_segundo);

  // Control de la hora
  if (botonArriba.wasPressed() || botonArriba.pressedFor(500)) {
    u_minuto++;
  }
  if (botonAbajo.wasPressed() || botonAbajo.pressedFor(500)) {
    u_hora++;
  }
  
  // Control de vuelta a pantalla principal  
  if (botonCentral.wasPressed()) {
    paginaActual = 10; 
    botonCentral.read(); // Comprobación de pulsación
  }
}

/*******************************************************************************/


