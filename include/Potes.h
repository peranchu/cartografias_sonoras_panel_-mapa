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
"Potes.h": 
Lectura Potenciometros - Ajuste y filtrado Señales Potenciometros
*/

#include <Arduino.h>
#include <OSCMessage.h>
#include <ResponsiveAnalogRead.h>
#include "clip.h"


//Param Potes
#define PotVolumen 34
#define PotTimeVar 35
#define PotPitchVar 33
#define NumPots 3


int valPotes[NumPots] = {0};
int valPotes_scale[NumPots] = {0};  // escalado para pintar en Pantalla

int readingPot = 0;
int PotCState[NumPots] = {0};
int PotPState[NumPots] = {0};
int pinPotes[NumPots] = {PotVolumen, PotTimeVar, PotPitchVar};
const char *envioPot[NumPots] = {"/PotVol", "/PotTime", "/PotPitch"};

int potVar = 0;
const int TIMEOUT_POT = 300;
const byte varthresholdPot = 1;
bool potMoving = true;
unsigned long PTimePot[NumPots] = {0};
unsigned long timerPot[NumPots] = {0};

int pot_min = 0;
int pot_max = 1023;
///////////////////////////////////////////////

//Resposive analog Read
float snapMultipler = 0.01;
ResponsiveAnalogRead resposivePot[NumPots] = {};
///////////////////////////

//Lectura Potenciómetros
void Lectura_potenciometros(){
    for (int i = 0; i < NumPots; i++){
        readingPot = analogRead(pinPotes[i]);
        resposivePot[i].update(readingPot);
        PotCState[i] = resposivePot[i].getValue();

        PotCState[i] = clipValue(PotCState[i], pot_min, pot_max);

        potVar = abs(PotCState[i] - PotPState[i]);

        if(potVar > varthresholdPot){
            PTimePot[i] = millis();
        }
        timerPot[i] = millis() - PTimePot[i];

        if(timerPot[i] < TIMEOUT_POT){
            potMoving = true;
        }
        else{
            potMoving = false;
        }
        if(potMoving == true){
            valPotes_scale[i] = map(PotCState[i], 0, 1023, 0, 11);
            valPotes[i] = PotCState[i];
            Serial.print(i);
            Serial.print(" Potenciometro: ");
            Serial.print(PotCState[i]);

            Serial.println();



            PotPState[i] = PotCState[i];
        }
    }
}
////// FIN LECTURA POTENCIOMETROS /////////

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