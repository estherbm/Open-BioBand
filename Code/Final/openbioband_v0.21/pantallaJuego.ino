/*******************************************************************************
   Pantalla Juego
 *******************************************************************************/

//!****************************************************************************
//!   Nombre: pantallaJuego
//!   Descripción: Pantalla de juego similar a "Flappy bird"
//!   Parámetro entrada: void
//!   Parámetro salida: void
//!   Ejemplo: pantallaJuego();
//!****************************************************************************
void pantallaJuego() {
  
  // Fuerza el tiempo de Standby para que no vaya a la pantalla principal
  tiempoStandby = millis() + tiempoActivo * 1000; 

  // Refresco pantalla  
  display.clearDisplay();

  //Control juego
  static boolean activacionJuego = true;
  static float velocidadY = 0;
  static int py = 0;
  static boolean gameOver = false;
  static byte puntuacion = 0;
  static int posicionMuro[3] = {100, 143, 186};
  static int agujeroMuro[3] = {40, 60, 0};
  static unsigned long ultimoTiempo = millis();

  if (activacionJuego) {
    velocidadY = py = puntuacion = 0;
    posicionMuro[0] = 100;
    posicionMuro[1] = 143;
    posicionMuro[2] = 186;
    ultimoTiempo = millis();
    gameOver = false;
  }

  float deltaTime = float(millis() - ultimoTiempo);

  velocidadY += deltaTime / 80;
  py += velocidadY;

  // Visualización juego escenario
  for (int i = 0; i < 3; i++) { // draw walls
    display.fillRect(posicionMuro[i] - 10, 0, 10, agujeroMuro[i], 0);
    display.fillRect(posicionMuro[i] - 10, agujeroMuro[i] + 30, 10, 96, 0);

    // Detección muro
    if (posicionMuro[i] > 5 && posicionMuro[i] < 25) { 
      // Detección agujero
      if (agujeroMuro[i] > py - 5 || agujeroMuro[i] < py - 25) gameOver = true; 
    }

    // Reinicio muro
    if (posicionMuro[i] <= 0) { 
      posicionMuro[i] += 129;
      agujeroMuro[i] = random(5, 70);
      puntuacion++;
    }
    posicionMuro[i] -= deltaTime / 80; // move walls
  }

  // Visualización personaje
  py = constrain(py, 5, 91);
  display.fillCircle(10, py, 5, 0); 

  // Visualización puntuación
  display.setTextColor(NEGRO, BLANCO);
  display.setCursor(40, 2);
  display.print(F("SCORE: "));
  display.println(puntuacion);

  if (botonArriba.isPressed()) velocidadY = -3;
  ultimoTiempo = millis();

  // Visualización fin del juego
  if (gameOver) {
    activacionJuego = true;
    display.clearDisplay();
    display.setCursor(20, 30);
    display.println(F("GAME OVER"));
    display.setCursor(20, 40);
    display.print(F("SCORE:"));
    display.println(puntuacion);
    display.refresh();
    delay(3000);
  }
  else activacionJuego = false;

  // Control de vuelta a pantalla principal  
  if (botonCentral.wasPressed()) {
    activacionJuego = true;
    paginaActual = 10; 
    botonCentral.read(); // Comprobación de pulsación
  }
}

/*******************************************************************************/


