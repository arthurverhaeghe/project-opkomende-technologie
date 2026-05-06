#include <Arduino.h>
#include <string>
#include <iostream>

// ledstrip constants
#include <FastLED.h>
const int LED_amount = 166;
#define NUM_LEDS LED_amount
#define LED_PIN 25
CRGB LEDs[NUM_LEDS];

// HX711 constants
#include "HX711.h"
const int LOADCELL_DOUT_PIN = 26;
const int LOADCELL_SCK_PIN = 18;
HX711 scale;
int const_correctionfactor = 0;

const int buttonPin = 27;
const int tolarance = 2;

void blink(CRGB color, int time, int first_number, int final_number)
{
  for (int i = first_number - 1; i <= final_number - 1; i++)
  {
    LEDs[i] = color;
  }
  FastLED.show();
  delay(time);
  for (int i = first_number - 1; i <= final_number - 1; i++)
  {
    LEDs[i] = CRGB ::Black;
  }
  FastLED.show();
}

void fill(CRGB color, int first_number, int final_number)
{
  for (int i = 0; i + 1 <= LED_amount; i++)
  {
    if (i + 1 >= first_number && i + 1 <= final_number)
    {
      LEDs[i] = color;
    }
    else
    {
      LEDs[i] = CRGB ::Black;
    }
  }
  FastLED.show();
}

int loadcell_setup()
{
  int correctionfactor = 0;
  String start = "start";
  while (start != Serial.readString()) // type start and send as text to start this program
  {
    delay(100);
  }
  Serial.println("Place your referance weight on the scale and enter the weight in grams.");
  int gewicht_int = 0;
  while (gewicht_int == 0)
  {
    if (Serial.available() != 0)
    {
      gewicht_int = (Serial.readString()).toInt(); // Serial.println(gewicht_int);
      int gewicht_ADC = scale.get_units(20);
      correctionfactor = gewicht_ADC / gewicht_int;
      Serial.println("correctionfactor: " + String(gewicht_ADC) + "/" + String(gewicht_int) + " = " + String(correctionfactor));
      scale.set_scale(correctionfactor);
      Serial.println("the scale is now calebrated");
    }
    delay(100);
  }
  return correctionfactor;
}

void setup()
{
  Serial.begin(57600);
  pinMode(buttonPin, INPUT_PULLUP);

  // led setup
  FastLED.addLeds<WS2812, LED_PIN, RGB>(LEDs, NUM_LEDS);
  FastLED.setBrightness(100); // valeu between 0-255
  fill_solid(LEDs, NUM_LEDS, CRGB::Black);
  FastLED.show();

  // loadcell setup
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale();
  scale.tare();
}

void loop()
{
  blink(CRGB::Blue, 500, 1, LED_amount);
  float full_bin = scale.get_units(20); // Serial.print(full_bin); //testcode
  while (digitalRead(buttonPin) != 0)
  {
    int gewicht = scale.get_units(5);
    // Serial.println(gewicht);
    int amount_leds_on = round((LED_amount * (gewicht / full_bin))); // Serial.println(amount_leds_on); // testcode
    if (amount_leds_on >= LED_amount - tolarance && amount_leds_on <= LED_amount + tolarance)
    {
      fill_solid(LEDs, NUM_LEDS, CRGB::Red);
      FastLED.show();
      // Serial.println("perfect");
    }
    else if (amount_leds_on > LED_amount + tolarance)
    {
      blink(CRGB::Green, 500, 1, LED_amount);
      // Serial.println("te veel");
    }
    else if (amount_leds_on < -tolarance)
    {
      fill(CRGB::Yellow, 1, amount_leds_on);
      blink(CRGB::Yellow, 500, amount_leds_on + 1, amount_leds_on + 1);
      // Serial.println("te weinig");
    }
    else
    {
        }
  }
  delay(100);
}