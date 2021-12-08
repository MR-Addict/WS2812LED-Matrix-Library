#include <FastLED.h>
#include <LEDMatrix.h>

const uint8_t LED_PIN = 18;
const uint8_t BRIGHTNESS = 10;
const uint8_t MATRIX_WIDTH = 16;
const uint8_t MATRIX_HEIGHT = 16;
const uint16_t NUM_LEDS = MATRIX_WIDTH * MATRIX_HEIGHT;

uint32_t Millis;
const uint8_t Radius = 1;
int8_t DeltaX = -2, DeltaY = 1;
uint8_t x = 10, y = 8;

CRGB leds[NUM_LEDS + 1];
cLEDMatrix LEDMatrix(leds, CUSTOM_MATRIX, MATRIX_WIDTH, MATRIX_HEIGHT);

void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.clear();
}

void loop() {
  FastLED.clear();
  LEDMatrix.DrawFilledRectangle(x, y, x + Radius, y + Radius, CRGB::Blue);
  if (millis() - Millis >= 200) {
    x += DeltaX, y += DeltaY;
    if (x + Radius >= LEDMatrix.Width()) {
      DeltaX = -DeltaX;
      x = LEDMatrix.Width() - 2;
    }
    else if (x <= 0) {
      DeltaX = -DeltaX;
      x = 0;
    }
    if (y + Radius >= LEDMatrix.Height()) {
      DeltaY = -DeltaY;
      y = LEDMatrix.Height() - 2;
    }
    else if (y <= 0) {
      DeltaY = -DeltaY;
      y = 0;
    }
    Millis = millis();
  }
  FastLED.show();
}
