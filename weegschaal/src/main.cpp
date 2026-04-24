#include <Arduino.h>
#include "HX711.h"
#include <string>
#include <iostream>
#include <FastLED.h>
// ledstrip constants
const int aantal_leds = 3;
#define NUM_LEDS aantal_leds
#define LED_PIN 25
CRGB leds[NUM_LEDS];

// HX711 constants
const int LOADCELL_DOUT_PIN = 26;
const int LOADCELL_SCK_PIN = 18;
HX711 scale;

std::string gewicht = "";
int gewicht_waarde = 0;
int ADC_waarde = 0;
int correctiefactor = 0;
int gewicht_bak = 0;
float procentueel_gewicht = 0;
int leds_aan = 0;

bool enter = false;

void setup()
{
  Serial.begin(57600);

  FastLED.addLeds<WS2812, LED_PIN, RGB>(leds, NUM_LEDS);
  FastLED.setBrightness(10); // 0-255

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(); // this value is obtained by calibrating the scale with known weights; see the README for details
  scale.tare();

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
  enter = false;
  ADC_waarde = scale.get_units(10);
  Serial.print("correctionfactor: ");
  Serial.print(ADC_waarde);
  Serial.print(" / ");
  Serial.print(gewicht_waarde);
  Serial.print(" = ");
  correctiefactor = ADC_waarde / gewicht_waarde;
  Serial.println(correctiefactor);
  scale.set_scale(correctiefactor); // this value is obtained by calibrating the scale with known weights; see the README for details
  Serial.println("the scale is now calebrated put the toys on in the bin and press enter to confirm the bin is full");
  while (enter == false)
  {
    if (Serial.available() != 0)
    {
      int getal = Serial.read();
      if (getal == 10)
      {
        gewicht_bak = scale.get_units(10);
        enter = true;
      }
    }
  }
}

void loop()
{
  Serial.print("| average:\t");
  Serial.println(scale.get_units(10), 1);
  procentueel_gewicht = scale.get_units(10) / gewicht_bak;
  int leds_gewicht = procentueel_gewicht * aantal_leds;
  Serial.println(leds_gewicht);
  if (leds_aan < leds_gewicht)
  {
    leds_aan += 1;
    leds[leds_aan] = CRGB ::Red;
    FastLED.show();
    Serial.println(leds_aan);
  }
  if (leds_aan > leds_gewicht)
  {
    leds[leds_aan] = CRGB ::Black;
    FastLED.show();
    leds_aan -= 1;
  }
  scale.power_down(); // put the ADC in sleep mode
  delay(5000);
  scale.power_up();
}
/*
void serial_monitor()
{
  while (enter == false)
  {
    if (Serial.available() != 0)
    {
      char asci_char = Serial.read();
      Serial.print((char)asci_char);
      std::string serial_monitor_string_output;
      serial_monitor_string_output += (char)asci_char;
      if (getal == 10)
      {
        gewicht_waarde = std::stoi(gewicht);
        enter = true;
      }
    }
  }
}
  */