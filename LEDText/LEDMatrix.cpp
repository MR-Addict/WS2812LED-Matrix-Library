
#include <FastLED.h>
#include <LEDMatrix.h>

#include "LEDText.h"

uint8_t cLEDText::Width() {
  return FontWidth;
}
uint8_t cLEDText::Height() {
  return FontHeight;
}
void cLEDText::SetCursor(int8_t x, int8_t y) {
  CursorX = x, CursorY = y;
}
void cLEDText::ScrollLeft() {
  CursorX--;
}
void cLEDText::ScrollRight() {
  CursorX--;
}
void cLEDText::ScrollUp() {
  CursorY--;
}
void cLEDText::ScrollDown() {
  CursorY++;
}
void cLEDText::PrintChar(int8_t DeltaX, int8_t DeltaY, uint8_t Char, CRGB Col) {
  for (uint8_t i = 0; i < FontHeight; i++) {
    for (uint8_t j = 0; j < FontWidth; j++) {
      boolean Value = bitRead(Font[i + FontHeight * Char + 2], 7 - j);
      if (Value)_leds[(*_LEDMatrix).GetXY(j + DeltaX, i + DeltaY)] = Col;
    }
  }
}
void cLEDText::Print(String string, CRGB Col) {
  uint8_t x = CursorX, y = CursorY;
  for (uint8_t i = 0; i < string.length(); i++, x += FontWidth) {
    PrintChar(x, y, string[i], Col);
  }
}