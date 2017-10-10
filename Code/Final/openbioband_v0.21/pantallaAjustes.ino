/*******************************************************************************
   Pantalla Ajustes
 *******************************************************************************/

//!****************************************************************************
//!   Nombre: pantallaAjustes
//!   Descripción: Pantalla de ajustes de parámetros de generales de navegación
//!   Parámetro entrada: void
//!   Parámetro salida: void
//!   Ejemplo: pantallaAjustes();
//!****************************************************************************

void pantallaAjustes() {
  
  // Fuerza el tiempo de Standby para que no vaya a la pantalla principal
  tiempoStandby = millis() + tiempoActivo * 1000; 

  // Variable de control de ajustes
  static int valorAjustes = 0;
  if (botonCentral.wasPressed()) valorAjustes++;

  // Refresco pantalla
  display.clearDisplay();
  
  display.setCursor(0, 2);

  // Visualización de ajuste de tiempo activo
  if (valorAjustes == 0) {
    if (botonArriba.wasPressed() || botonArriba.pressedFor(500)) tiempoActivo++;
    if (botonAbajo.wasPressed() || botonAbajo.pressedFor(500)) tiempoActivo--;
    display.setTextColor(BLANCO, NEGRO);
    if (tiempoActivo > 60) tiempoActivo = 30;
    else if (tiempoActivo < 5) tiempoActivo = 5;
  }
  else display.setTextColor(NEGRO, BLANCO);
  
  // Visualización de ajuste de tiempo activo
  display.print(F("Standby: "));
  display.print(tiempoActivo);
  display.println("s");

  // Control de ajuste de indicación de voltaje
  if (valorAjustes == 1) {
    if (botonArriba.wasPressed() || botonAbajo.wasPressed()) visualizacionVoltaje = !visualizacionVoltaje;
    display.setTextColor(BLANCO, NEGRO);
  }
  else display.setTextColor(NEGRO, BLANCO);

  
  // Visualización de ajuste de indicación de voltaje
  display.print(F("Voltaje: "));
  if (visualizacionVoltaje) {
    display.println("ON");
  }
  else {
    display.println("OFF");
  }

  // Control de ajuste de peso
  if (valorAjustes == 2) {
    if (botonArriba.wasPressed() || botonArriba.pressedFor(500)) peso++;
    if (botonAbajo.wasPressed() || botonAbajo.pressedFor(500)) peso--;
    display.setTextColor(BLANCO, NEGRO);
  }
  else display.setTextColor(NEGRO, BLANCO);

  // Visualización de ajuste de peso
  display.print(F("Peso: "));
  display.print(peso);
  display.println("kg");

  // Control de ajuste de altura
  if (valorAjustes == 3) {
    if (botonArriba.wasPressed() || botonArriba.pressedFor(500)) altura++;
    if (botonAbajo.wasPressed() || botonAbajo.pressedFor(500)) altura--;
    display.setTextColor(BLANCO, NEGRO);
  }
  else display.setTextColor(NEGRO, BLANCO);

  // Visualización de ajuste de altura
  display.print(F("Altura: "));
  display.print(altura);
  display.println("cm");

  // Control y visualización de ajuste de general
  display.setTextColor((valorAjustes == 4), (valorAjustes != 4));
  display.println(F("OK"));

  // Control de vuelta a pantalla principal
  if (botonCentral.wasPressed() && valorAjustes == 5) {
    valorAjustes = 0;
    paginaActual = 10;
    menuVal = 4;
    botonCentral.read(); // Comprobación de pulsación
  }
}

/*******************************************************************************/


