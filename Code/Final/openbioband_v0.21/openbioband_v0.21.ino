/*
    Open BioBand is a biometric Open Source wristband with BLE (Bluetooth
    Low Energy) connectivity used to non-invasive monitorization of patients
    and their environment. It measure several parameters such as pulse, SPO2,
    body temperature, motion activity, pressure, humidity, temperature...

    It allow developers to investigate an learn about wereables and biometric
    sensors and artists to create new biological performances and projects.

    Created as final thesis Industrial Engineering project.

    This firmware manage all the circuits and sensors integrated in Open BioBand.
    Created by Esther Borao Moros, September 1, 2017.

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    Version:                  0.15
    Implementation:           Esther Borao Moros
*/

/*******************************************************************************
   Includes
 *******************************************************************************/

// Librerías generales Arduino
#include <Wire.h>
#include <SPI.h>
#include <Arduino.h>
#include <SoftwareSerial.h>

// Librería interrupciones
#include "PinChangeInterrupt.h"

// Librerías sensor parámetros ambientales BME280
#include <stdint.h>
#include "SparkFunBME280.h"

// Librerías sensor acelerómetro ADXL345
#include <SparkFun_ADXL345.h>
#include "pedometer.h"

// Librería sensor luz TSL2561
#include <SparkFunTSL2561.h>

// Librerías pantalla SharpMem
#include <Adafruit_GFX.h>
#include <Adafruit_SharpMem.h>

// Librería bajo consumo
#include <LowPower.h>

// Librería pulsadores
#include <Button.h>

// Librerías sensor biométrico MAX30105
#include "MAX30105.h"
#include "HeartRate.h"
#include "spo2_algorithm.h"

// Librerías módulo BLE MDBT40 (nRF51822)
#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_UART.h"

/*******************************************************************************/


/*******************************************************************************
   Defines y variables
 *******************************************************************************/

/*****************************************************************************
  Modo Debug: descomentar el siguiente comentario para activar el modo.
******************************************************************************/

//#define BIOBAND_DEBUG

// Define en que salida se imprime el Modo Debug
#define DEBUG_SERIAL Serial

// Configuración Modo Debug
#ifdef BIOBAND_DEBUG
#define DEBUG_PRINT(...) { DEBUG_DEBUG_PRINT(__VA_ARGS__); }
#define DEBUG_PRINTLN(...) { DEBUG_SERIAL.println(__VA_ARGS__); }
#else
#define DEBUG_PRINT(...) {}
#define DEBUG_PRINTLN(...) {}
#endif

/*****************************************************************************/

// Control módulo BLE MDBT40 (nRF51822)
#define LONGITUDBUFFER                 128   // Tamaño del buffer de recepción de datos
#define MODO_VERBOSE                   true  // Con valor "true" se activa el modo debug 
#define MODO_UART_PIN                  -1    // Pin de control de modo, a "-1

#define RESET_FABRICA_HABILITADO         1
#define VERSION_MINIMA_FIRMWARE    "0.6.6"
#define MODO_LED_AVISO          "MODE"

Adafruit_BluefruitLE_UART ble(Serial1, MODO_UART_PIN);

int datoRecibido;

// Control pantalla SharpMem
#define SCK 10
#define MOSI 11
#define SS 13

Adafruit_SharpMem display(SCK, MOSI, SS);

#define NEGRO 0
#define BLANCO 1

// Control pulsadores
#define MBOT 6
#define UBOT 9
#define DBOT 8

// Control batería
#define VBATPIN A2
#define CHGPIN 7

int porcentajeBateria = 0;
int estadoBateria;

// Control iluminación
#define ILUMINACION 1

byte menuIluminacion = 1;
byte estadoIluminacion = 3;
double lux;

// Control sensor temperatura
#define LMT70_TAO A1
#define LMT70_TON 5

float LMT70_AMul = -0.000000001809628;
float LMT70_BMul = -0.000003325395;
float LMT70_CMul = -0.1814103;
float LMT70_DMul = 205.5894;

// Control pulsadores
Button botonCentral(MBOT, true, true, 20);
Button botonArriba(UBOT, true, true, 20);
Button botonAbajo(DBOT, true, true, 20);

// Control sensor biométrico MAX30105
#define BRILLO_MAXIMO 255

MAX30105 sensorBiometrico;

#define MAX_BRIGHTNESS 255

const byte RATE_SIZE = 4; //Increase this for more averaging. 4 is good.
byte rates[RATE_SIZE]; //Array of heart rates
byte rateSpot = 0;
long lastBeat = 0; //Time at which the last beat occurred

float beatsPerMinute;
int beatAvg;

int counterSPO2;
int spoRandom;

float tempera;
// Control sensor parámetros ambientales BME280
BME280 sensorAmbiente;

float temperatura;
float presion;
float altitud;
float humedad;

// Control sensor luz TSL2561
SFE_TSL2561 sensorLuz;

boolean gananciaLuz;
unsigned int ms;

// Control navegación pantallas
unsigned long tiempoStandby;
byte tiempoActivo = 15;
boolean active = false;

byte paginaActual = 0;
byte menuVal = 0;
byte configVal = 0;

boolean flicker = false;
unsigned long paradaRelojTimer = 0;
boolean paradaRelojActivo = false;
unsigned long paradaRelojMs = 0;

// Control sensor batería
boolean visualizacionVoltaje = true;

// Control reloj
int u_hora = 0;
int u_minuto = 0;
int u_segundo = 0;
int d_hora = 0;
int d_minuto = 0;
int d_segundo = 0;
unsigned long timer1 = 0;
unsigned long timer2 = 0;

// Control sensor acelerómetro ADXL345
Pedometer acelerometro;

int peso = 50;    //kg
int altura = 160; //cm
float long_paso;
float calorias_milla;
float pasos_milla;
float calorias_quemadas;
float distancia;
float factor;

/*******************************************************************************/


/*******************************************************************************
   Inicialización
 *******************************************************************************/

void setup(void) {

  // Configuración puertos serie
 // Serial.begin(9600);
 tempera=20;

  // Configuración batería
  pinMode(CHGPIN, INPUT_PULLUP);
  //attachPCINT(digitalPinToPCINT(CHGPIN), despertarMicro, FALLING);

  // Configuración sensor luz TSL2561
  pinMode(ILUMINACION, OUTPUT);

  // Configuración sensor acelerómetro ADXL345
  acelerometro.init();

  // Configuración sensor biométrico MAX30105
  if (!sensorBiometrico.begin(Wire, I2C_SPEED_FAST))
  {
    DEBUG_PRINT("MAX30101 no fue encontrado. ");
    DEBUG_PRINTLN("Comprueba el cableado o la alimentacion ");
    while (1);
  }

  sensorBiometrico.setup(); //Configure sensor with default settings
  sensorBiometrico.setPulseAmplitudeRed(0x0A); //Turn Red LED to low to indicate sensor is running
  sensorBiometrico.setPulseAmplitudeGreen(0); //Turn off Green LED

  // Configuración sensor luz TSL2561
  unsigned char ID;
  gananciaLuz = 0;
  unsigned char tiempoLuz = 2;

  sensorLuz.begin();
  sensorLuz.getID(ID);
  sensorLuz.setTiming(gananciaLuz, tiempoLuz, ms);
  sensorLuz.setPowerUp();

  // Configuración y calibración sensor parámetros ambientales BME280
  sensorAmbiente.settings.commInterface = I2C_MODE;
  sensorAmbiente.settings.I2CAddress = 0x77;
  sensorAmbiente.settings.runMode = 3; // Modo Normal
  sensorAmbiente.settings.tStandby = 0; // Tiempo de Standby
  sensorAmbiente.settings.filter = 0;
  sensorAmbiente.settings.tempOverSample = 1;
  sensorAmbiente.settings.pressOverSample = 1;
  sensorAmbiente.settings.humidOverSample = 1;

  delay(10);  //Requiere 2ms para empezar
  sensorAmbiente.begin();
  sensorAmbiente.readRegister(BME280_CHIP_ID_REG);
  sensorAmbiente.readRegister(BME280_RST_REG);
  sensorAmbiente.readRegister(BME280_CTRL_MEAS_REG);
  sensorAmbiente.readRegister(BME280_CTRL_HUMIDITY_REG);

  uint8_t contadorMem = 0x80;
  uint8_t lecturaDatoTemp;

  for (int rowi = 8; rowi < 16; rowi++ )
  {
    DEBUG_PRINT("0x");
    DEBUG_PRINT(rowi, HEX);
    DEBUG_PRINT("0:");
    for (int coli = 0; coli < 16; coli++ )
    {
      lecturaDatoTemp = sensorAmbiente.readRegister(contadorMem);
      DEBUG_PRINT((lecturaDatoTemp >> 4) & 0x0F, HEX);// Imprimir primera parte en hexadecimal
      DEBUG_PRINT(lecturaDatoTemp & 0x0F, HEX);// Imprimir segunda parte en hexadecimal
      DEBUG_PRINT(" ");
      contadorMem++;
    }
    DEBUG_PRINT("\n");
  }

  sensorAmbiente.calibration.dig_T1;
  sensorAmbiente.calibration.dig_T2;
  sensorAmbiente.calibration.dig_T3;

  sensorAmbiente.calibration.dig_P1;
  sensorAmbiente.calibration.dig_P2;
  sensorAmbiente.calibration.dig_P3;
  sensorAmbiente.calibration.dig_P4;
  sensorAmbiente.calibration.dig_P5;
  sensorAmbiente.calibration.dig_P6;
  sensorAmbiente.calibration.dig_P7;
  sensorAmbiente.calibration.dig_P8;
  sensorAmbiente.calibration.dig_P9;

  sensorAmbiente.calibration.dig_H1;
  sensorAmbiente.calibration.dig_H2;
  sensorAmbiente.calibration.dig_H3;
  sensorAmbiente.calibration.dig_H4;
  sensorAmbiente.calibration.dig_H5;
  sensorAmbiente.calibration.dig_H6;

  // Configuración pantalla SharpMem
  display.begin();
  display.setRotation(0);
  display.clearDisplay();

  display.setCursor(52, 4);
  display.setTextColor(NEGRO, BLANCO);
  display.print("porcentajeBateria");


  // Configuración sensor temperatura
  pinMode(LMT70_TON, OUTPUT);

  // Configuración pulsadores
  pinMode(MBOT, INPUT_PULLUP);
  pinMode(UBOT, INPUT_PULLUP);
  pinMode(DBOT, INPUT_PULLUP);

  attachInterrupt(2, despertarMicro, FALLING);

  botonCentral.read();
  botonArriba.read();
  botonAbajo.read();

  // Configuración módulo BLE MDBT40 (nRF51822)
  if ( !ble.begin(MODO_VERBOSE) ) {
    error(F("No se puede conectar con el módulo"));
  }
  DEBUG_PRINTLN( F("Conexion correcta") );

  if ( RESET_FABRICA_HABILITADO ) {
    // Reset de fábrica para inicializar los valores
    DEBUG_PRINTLN(F("Reset de fabrica: "));
    if ( ! ble.factoryReset() ) {
      error(F("No es posible el reseteo"));
    }
  }
  // Deshabilita el comando "echo"
  ble.echo(false);

  // Activación led de indicaciones
  ble.verbose(false);

  // Configura en modo DATA
  //ble.setMode(BLUEFRUIT_MODE_DATA);

  // Configuración e inicializacion actualización pantalla
  tiempoStandby = millis() + tiempoActivo * 1000;

}

/*******************************************************************************/


/*******************************************************************************
   Bucle Principal
 *******************************************************************************/

void loop(void) {

  // Comprobación estado carga batería
  int carga = digitalRead(CHGPIN);

  // Comprobación si está activa la navegación
  active = (millis() <= tiempoStandby);

  //  // Comprobación conexión módulo BLE MDBT40 (nRF51822)
  //  if (ble.isConnected()) {
  //    ble.print("AT+BLEUARTTX=");
  //    ble.println("Connected");
  //    // Comprobación de envío correcto de comando
  //    if (! ble.waitForOK() ) {
  //      DEBUG_PRINTLN(F("Fallo al enviar"));
  //    }
  //
  //    // Comprobación de datos entrantes
  //    ble.println("AT+BLEUARTRX");
  //    ble.readline();
  //    if (strcmp(ble.buffer, "OK") == 0) {
  //      return;
  //    }
  //
  //    // Datos recibidos. Almacenados en el buffer
  //    DEBUG_PRINT(F("[Recv] "));
  //    DEBUG_PRINTLN(ble.buffer);
  //    ble.waitForOK();
  //  }

  // Lectura botón central
  botonCentral.read();

  // Reseteo del Timer de actualización de pantalla si se detecta pulsación
  if (active && (botonArriba.read() || botonAbajo.read()))
  {
    tiempoStandby = millis() + tiempoActivo * 1000;
  }

  // Comprobación finalización navegación pantallas y reinicio
  if (paginaActual == 0 && botonCentral.wasPressed()) {
    paginaActual = 10;
    menuVal = 0;
    botonCentral.read();
  }

  // Conteo de segundos
  un_seg ();

  // Actualización reloj
  contador();

  // Actualización navegación pantallas
  if (paginaActual == 0 || !active) pantallaPrincipal();
  else if (paginaActual == 10) pantallaMenu();
  else if (paginaActual == 1) pantallaSalud();
  else if (paginaActual == 2) pantallaAmbiente();
  else if (paginaActual == 3) pantallaMovimiento();
  else if (paginaActual == 4) pantallaCronometro();
  else if (paginaActual == 5) pantallaAjustes();
  else if (paginaActual == 6) pantallaJuego();
  else if (paginaActual == 7) pantallaIluminacion();
  else if (paginaActual == 8) pantallaReloj();
  else if (paginaActual == 9) pantallaNotificaciones();
  else display.clearDisplay();

  // Medición sensor luz TSL2561
  unsigned int data0, data1;

  sensorLuz.getData(data0, data1);
  sensorLuz.getLux(gananciaLuz, ms, data0, data1, lux);

  // Comprobación estado iluminación
  switch (estadoIluminacion) {
    case 1:
      if (lux < 0.05) {
        digitalWrite(ILUMINACION, HIGH);
      }
      if (lux> 4.0){ digitalWrite(ILUMINACION, LOW);}
      //else  digitalWrite(ILUMINACION, HIGH);
      break;
    case 2:
      digitalWrite(ILUMINACION, HIGH);
      break;
    case 3:
      digitalWrite(ILUMINACION, LOW);
      break;
  }

  // Refresco pantalla
  display.refresh();

  // Comprobación tiempo Stanby y activación modo bajo consumo
  if (!active) {
    paginaActual = 0;
    LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
  }
  else if (!flicker) digitalWrite(SCK, HIGH); // Elimina error por "flicker"

}

/*******************************************************************************/


/*******************************************************************************
   Otras funciones
 *******************************************************************************/

//!****************************************************************************
//!   Nombre: despertarMicro
//!   Descripción: Despierta el microcontrolador del modo de bajo consumo
//!   Parámetro entrada: void
//!   Parámetro salida: void
//!   Ejemplo: despertarMicro();
//!****************************************************************************

void despertarMicro() {

  noInterrupts();
  tiempoStandby = millis() + tiempoActivo * 1000; // Resetea Timer Standby
  interrupts();
}

/*****************************************************************************/

//!****************************************************************************
//!   Nombre: un_seg
//!   Descripción: Rutina para el conteo de segundos
//!   Parámetro entrada: void
//!   Parámetro salida: void
//!   Ejemplo: un_seg();
//!****************************************************************************

//Reloj
void un_seg() {

  //Rutina para cada segundo
  timer2 = (millis() / 1000);
  if ( timer1 != timer2 ) {
    timer1 = timer2;
    u_segundo++;
  }
}
/*****************************************************************************/


//!****************************************************************************
//!   Nombre: contador
//!   Descripción: Rutina que lleva el conteo del reloj
//!   Parámetro entrada: void
//!   Parámetro salida: void
//!   Ejemplo: contador();
//!****************************************************************************

void contador() {

  // Rutina de segundos
  if ( u_segundo == 10 ) {
    u_segundo = 0;
    d_segundo++;
  }
  if ( ( d_segundo == 6 ) && ( u_segundo == 0 ) ) {
    d_segundo = 0;
    u_minuto++;
  }

  // Rutina de minutos
  if ( u_minuto == 10 ) {
    u_minuto = 0;
    d_minuto++;
  }
  if ( ( d_minuto == 6 ) && ( u_minuto == 0 ) ) {
    d_minuto = 0;
    u_hora++;
  }

  // Rutina de horas
  if ( u_hora == 10 ) {
    u_hora = 0;
    d_hora++;
  }
  if ( (d_hora == 2) &&  (u_hora == 4) ) {
    u_hora = 0;
    d_hora = 0;
  }
}

/*****************************************************************************/


//!****************************************************************************
//!   Nombre: dibujarDigito
//!   Descripción: Dibuja en la pantalla un dígito
//!   Parámetro entrada: int posición X, int posición Y, int dígito, bool color
//!   Parámetro salida: void
//!   Ejemplo: dibujarDigito(10,20,7,1);
//!****************************************************************************

void dibujarDigito(int posX, int posY, int digito, boolean col) {

  switch (digito) {
    case 0:
      display.fillRect(posX, posY, 20, 8, col);
      display.fillRect(posX, posY, 7, 40, col);
      display.fillRect(posX + 13, posY, 7, 40, col);
      display.fillRect(posX, posY + 32, 20, 8, col);
      break;
    case 1:
      display.fillRect(posX + 13, posY, 7, 40, col);
      break;
    case 2:
      display.fillRect(posX, posY, 20, 8, col);
      display.fillRect(posX, posY + 16, 20, 8, col);
      display.fillRect(posX, posY + 24, 7, 8, col);
      display.fillRect(posX + 13, posY, 7, 16, col);
      display.fillRect(posX, posY + 32, 20, 8, col);
      break;
    case 3:
      display.fillRect(posX, posY, 20, 8, col);
      display.fillRect(posX, posY + 16, 20, 8, col);
      display.fillRect(posX + 13, posY, 7, 40, col);
      display.fillRect(posX, posY + 32, 20, 8, col);
      break;
    case 4:
      display.fillRect(posX, posY, 7, 16, col);
      display.fillRect(posX, posY + 16, 20, 8, col);
      display.fillRect(posX + 13, posY, 7, 40, col);
      break;
    case 5:
      display.fillRect(posX, posY, 20, 8, col);
      display.fillRect(posX, posY + 16, 20, 8, col);
      display.fillRect(posX + 13, posY + 24, 7, 8, col);
      display.fillRect(posX, posY, 7, 16, col);
      display.fillRect(posX, posY + 32, 20, 8, col);
      break;
    case 6:
      display.fillRect(posX, posY, 20, 8, col);
      display.fillRect(posX, posY + 16, 20, 8, col);
      display.fillRect(posX + 13, posY + 24, 7, 8, col);
      display.fillRect(posX, posY, 7, 40, col);
      display.fillRect(posX, posY + 32, 20, 8, col);
      break;
    case 7:
      display.fillRect(posX, posY, 20, 8, col);
      display.fillRect(posX + 13, posY, 7, 40, col);
      break;
    case 8:
      display.fillRect(posX, posY, 20, 8, col);
      display.fillRect(posX, posY, 7, 40, col);
      display.fillRect(posX, posY + 16, 20, 8, col);
      display.fillRect(posX + 13, posY, 7, 40, col);
      display.fillRect(posX, posY + 32, 20, 8, col);
      break;
    case 9:
      display.fillRect(posX, posY, 20, 8, col);
      display.fillRect(posX, posY, 7, 16, col);
      display.fillRect(posX, posY + 16, 20, 8, col);
      display.fillRect(posX + 13, posY, 7, 40, col);
      display.fillRect(posX, posY + 32, 20, 8, col);
      break;
  }
}

/*****************************************************************************/


//!****************************************************************************
//!   Nombre: error
//!   Descripción: Imprime el error de inicialización del módulo BLE
//!   Parámetro entrada: cost Respuesta del módulo tras inicialización
//!   Parámetro salida: void
//!   Ejemplo: error(FlashStringHelper);
//!****************************************************************************

//Control inicialización BLE (Bluetooth Low Energy)
void error(const __FlashStringHelper*err) {

  DEBUG_PRINT(err);
  //while (1);
}

/*****************************************************************************/


//!****************************************************************************
//!   Nombre: leerVoltage
//!   Descripción: Lee el valor de la batería Vcc y lo transforma en mv
//!   Parámetro entrada: void
//!   Parámetro salida: long valor en mv de la batería
//!   Ejemplo: leerVoltage();
//!****************************************************************************

long leerVoltage() {

  int resultado;
  float voltageMedido = analogRead(VBATPIN);
  voltageMedido *= 2;    // Multiplica por 2
  voltageMedido *= 3.3;  // Multiplica por 3.3, la referencia de tensión
  voltageMedido /= 1024; // Convierte en tensión
  DEBUG_PRINT("VBat: " ); DEBUG_PRINTLN(voltageMedido);

  resultado = voltageMedido * 1000; // Calcula Vcc (en mV); 1125300 = 1.1*1023*1000
  return resultado; // Devuelve Vcc en mV
}

/*****************************************************************************/


