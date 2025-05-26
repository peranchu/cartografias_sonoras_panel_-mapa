#include <Arduino.h>
#include <ResponsiveAnalogRead.h>
#include "clip.h"


//Param Potes
#define PotVolumen 35
#define PotTimeVar 33
#define PotPitchVar 34
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