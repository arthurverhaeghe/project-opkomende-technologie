#include <Arduino.h>
#include "HX711.h"
#include <string>
#include <iostream>
#include <FastLED.h>
#define NUM_LEDS 10

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 26;
const int LOADCELL_SCK_PIN = 18;
std::string gewicht = "";
int gewicht_waarde = 0;
int ADC_waarde = 0;
bool enter = false;
int correctiefactor = 0;

HX711 scale;

void setup()
{
  Serial.begin(57600);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  Serial.println("press enter when ready to continue to the next step");
  Serial.print("enter reference weight in grams:");
  while (enter == false)
  {
    if (Serial.available() != 0)
    {
      int getal = Serial.read();
      Serial.print((char)getal);
      gewicht += (char)getal;
      if (getal == 10)
      {
        gewicht_waarde = std::stoi(gewicht);
        enter = true;
      }
    }
  }
  enter = false;
  Serial.println("place referace weight on scale and press enter to continue");
  scale.set_scale(); // this value is obtained by calibrating the scale with known weights; see the README for details
  scale.tare();
  while (enter == false)
  {
    if (Serial.available() != 0)
    {
      int getal = Serial.read();
      if (getal == 10)
      {
        enter = true;
      }
    }
  }
  ADC_waarde = scale.get_units(10);
  Serial.print("correctionfactor: ");
  Serial.print(ADC_waarde);
  Serial.print(" / ");
  Serial.print(gewicht_waarde);
  Serial.print(" = ");
  correctiefactor = ADC_waarde / gewicht_waarde;
  Serial.println(correctiefactor);
  scale.set_scale(correctiefactor); // this value is obtained by calibrating the scale with known weights; see the README for details
}

void loop()
{
  Serial.print("one reading:\t");
  Serial.print(scale.get_units(), 1);
  Serial.print("\t| average:\t");
  Serial.println(scale.get_units(10), 1);

  scale.power_down(); // put the ADC in sleep mode
  delay(5000);
  scale.power_up();
}