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
Pantalla.h: Gestiona 3 pantallas SSD1306 128x32
Multiplexor I2C TCA9548A
*/

#include <Arduino.h>
#include <Wire.h>
#include <RoxTCA9548A.h>
#include <U8g2lib.h>

// instancia 3 pantallas
U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2_1(U8G2_R0);
U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2_2(U8G2_R0);
U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2_3(U8G2_R0);

// Intancia Multiplexor I2C
RoxTCA9548A<1> mux;

// Dibujo Pantalla 1 PITCH VARIATION
void DibujoPantalla_1(int Pv)
{
    u8g2_1.setFont(u8g2_font_streamline_interface_essential_action_t);
    u8g2_1.drawGlyph(0, 26, 0x39);

    u8g2_1.setFont(u8g2_font_freedoomr25_tn);
    u8g2_1.setCursor(34, 32);
    u8g2_1.print(Pv);
}

// Dibujo Pantalla 2 TIME VARIATION
void DibujoPantalla_2(int Tv)
{
    u8g2_2.setFont(u8g2_font_streamline_interface_essential_loading_t);
    u8g2_2.drawGlyph(0, 26, 0x3D);

    u8g2_2.setFont(u8g2_font_freedoomr25_tn);
    u8g2_2.setCursor(34, 32);
    u8g2_2.print(Tv);
}

// Dibujo Pantalla 3 VOLUME
void DibujoPantalla_3(int Vo)
{
    u8g2_3.setFont(u8g2_font_streamline_interface_essential_audio_t);
    u8g2_3.drawGlyph(0, 26, 0x34);

    u8g2_3.setFont(u8g2_font_freedoomr25_tn);
    u8g2_3.setCursor(34, 32);
    u8g2_3.print(Vo);
}