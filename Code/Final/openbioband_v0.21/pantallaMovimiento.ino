/*******************************************************************************
   Pantalla Movimiento
 *******************************************************************************/

//!****************************************************************************
//!   Nombre: pantallaMovimiento
//!   Descripción: Pantalla de medición de parámetros asociados al acelerómetro
//!   Parámetro entrada: void
//!   Parámetro salida: void
//!   Ejemplo: pantallaMovimiento();
//!****************************************************************************

void pantallaMovimiento() {
 
  // Definición logos
  #define anchoIcono 11
  #define altoIcono  12

  static const unsigned char acc_img[] PROGMEM =
  {
    0x4, 0x0,
    0xe, 0x0,
    0x1f, 0x0,
    0x4, 0x0,
    0x4, 0x0,
    0xe, 0x0,
    0xa, 0x0,
    0xe, 0x0,
    0x11, 0x0,
    0xa0, 0xa0,
    0xc0, 0x60,
    0xe0, 0xe0
  };
  
  // Fuerza el tiempo de Standby para que no vaya a la pantalla principal
  tiempoStandby = millis() + tiempoActivo * 1000; 

  // Medición datos acelerómetro
  acelerometro.stepCalc(); 

  // Cálculo de pasos
  long_paso = 0.415 * altura; //cm
  calorias_milla = 0.57 * (peso * 2.2); //peso en kg
  pasos_milla = 160934.4 / long_paso; //160934.3 una milla en cm
  factor = calorias_milla / pasos_milla;
  calorias_quemadas = acelerometro.stepCount * factor; //cal
  distancia = (long_paso * acelerometro.stepCount) / 100; //m

  // Cálculo aceleración
  int valorGravedad = 30;
  float acelX = (1.0*acelerometro.x)/valorGravedad;
  float acelY = (1.0*acelerometro.y)/valorGravedad; 
  float acelZ = (1.0*acelerometro.z)/valorGravedad;

  // Visualización datos podómetro
  display.setCursor(10, 10);
  display.clearDisplay();
  display.setTextSize(1);
  display.print("Pasos: ");
  display.print(acelerometro.stepCount);
  display.setCursor(10, 25);
  display.print("Dist: ");
  display.print(distancia);
  display.println(" m");
  display.setCursor(10, 40);
  display.print("Cal: ");
  display.print(calorias_quemadas);

  // Visualización aceleraciones
  display.drawBitmap(10, 65, acc_img, anchoIcono, altoIcono, NEGRO);
  display.setCursor(30, 56);
  display.print("x "); 
  display.print(acelX);
  display.setCursor(30, 67);
  display.print("y "); 
  display.print(acelY);
  display.setCursor(30, 78);
  display.print("z "); 
  display.print(acelZ);

  // Control de vuelta a pantalla principal  
  if (botonCentral.wasPressed()) {
    acelerometro.stepCount = 0;
    paginaActual = 10; 
    botonCentral.read(); // Comprobación de pulsación
  }
}

/*******************************************************************************/


