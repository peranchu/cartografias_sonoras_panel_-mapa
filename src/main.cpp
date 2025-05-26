/*
              _ _______
    /\        | |__   __|
   /  \   _ __| |_ | | ___  ___
  / /\ \ | '__| __|| |/ _ \/ __|
 / ____ \| |  | |_ | |  __/ (__
/_/    \_\_|   \__||_|\___|\___|

CARTOGRAFÍAS SONORAS
Honorino García Mayo 2025

Panel Gestión MAPA - PITCH VARIATION - TIME VARIATION - VOLUME
*/

#include <Arduino.h>
#include "pantalla.h"
#include "Potes.h"

void setup()
{
  Serial.begin(115200);
  delay(100);

  analogReadResolution(10);
  delay(100);

  mux.begin(true);         // Inicia Multiplexor I2C "pantalla.h"
  mux.setAddress(0, 0x70); // Direccion Miltiplexor i2C
  delay(100);

  // Inicia Pantallas
  mux.select(0); // Puerto 0 Multiplexor I2C
  u8g2_1.begin();
  u8g2_1.clearBuffer();

  mux.select(1); // Puerto 1 Multiplexor I2C
  u8g2_2.begin();
  u8g2_2.clearBuffer();

  mux.select(2); // Puerto 2 Miltiplexor I2C
  u8g2_3.begin();
  u8g2_3.clearBuffer();
  ///////////////////////
  delay(100);

  ConexionWiFi();

  for (int i = 0; i < NumPots; i++)
  {
    resposivePot[i] = ResponsiveAnalogRead(pinPotes[i], true, snapMultipler);
  }
}

void loop()
{
  if (conexion)
  {
    // Lectura Potenciometros
    Lectura_potenciometros();

    // Dibujo Pantalla 1
    mux.select(0);
    u8g2_1.firstPage();
    do
    {
      DibujoPantalla_1(valPotes_scale[0]);
    } while (u8g2_1.nextPage());

    // Dibujo Pantalla 2
    mux.select(1);
    u8g2_2.firstPage();
    do
    {
      DibujoPantalla_2(valPotes_scale[1]);
    } while (u8g2_2.nextPage());

    // Dibujo Pantalla 3
    mux.select(2);
    u8g2_3.firstPage();
    do
    {
      DibujoPantalla_3(valPotes_scale[2]);
    } while (u8g2_3.nextPage());
  }
}

/*
  _____           _                         __ _              _____
 / ____|         | |                       / _(_)            / ____|
| |     __ _ _ __| |_ ___   __ _ _ __ __ _| |_ _  __ _ ___  | (___   ___  _ __   ___  _ __ __ _ ___
| |    / _` | '__| __/ _ \ / _` | '__/ _` |  _| |/ _` / __|  \___ \ / _ \| '_ \ / _ \| '__/ _` / __|
| |___| (_| | |  | || (_) | (_| | | | (_| | | | | (_| \__ \  ____) | (_) | | | | (_) | | | (_| \__ \
 \_____\__,_|_|   \__\___/ \__, |_|  \__,_|_| |_|\__,_|___/ |_____/ \___/|_| |_|\___/|_|  \__,_|___/
                            __/ |
                           |___/

 Honorino García Mayo 2025
*/