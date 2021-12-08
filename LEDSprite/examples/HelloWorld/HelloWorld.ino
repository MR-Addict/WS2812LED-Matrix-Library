#include <FastLED.h>
#include <LEDMatrix.h>
#include <LEDText.h>
#include <LEDSprite.h>

#include "Sprites.h"

const uint8_t LED_PIN = 18;
const uint8_t BRIGHTNESS = 10;
const uint8_t MATRIX_WIDTH = 16;
const uint8_t MATRIX_HEIGHT = 16;
const uint16_t NUM_LEDS = MATRIX_WIDTH * MATRIX_HEIGHT;

CRGB leds[NUM_LEDS + 1];
cLEDMatrix LEDMatrix(leds, CUSTOM_MATRIX, MATRIX_WIDTH, MATRIX_HEIGHT);
cLEDText LEDText(leds, &LEDMatrix);
cLEDSprite LEDSprite(leds, &LEDMatrix);


void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.clear();
}

void loop() {
  for (uint8_t i = 0; i < 5; i++) {
    LEDSprite.Show(sprites[i], 16, 16, 0, 0);
    FastLED.show();
    delay(2000);
  }
}
