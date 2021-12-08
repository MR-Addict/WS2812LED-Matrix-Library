#include <FastLED.h>
#include <LEDMatrix.h>

const uint8_t LED_PIN = 18;
const uint8_t BRIGHTNESS = 10;
const uint8_t MATRIX_WIDTH = 16;
const uint8_t MATRIX_HEIGHT = 16;
const uint16_t NUM_LEDS = MATRIX_WIDTH * MATRIX_HEIGHT;

uint8_t ColorIndex;

CRGB leds[NUM_LEDS + 1];
cLEDMatrix LEDMatrix(leds, CUSTOM_MATRIX, MATRIX_WIDTH, MATRIX_HEIGHT);

void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.clear();
}

void loop() {
  for (uint8_t i = 0; i < 8; i++)LEDMatrix.DrawRectangle(i, i, 15 - i, 15 - i, CHSV(ColorIndex + i * 20, 255, 255));
  ColorIndex = beatsin16(10, 0, 512, 0, 0) + beatsin16(20, 0, 512, 0, 0);
  FastLED.show();
}
