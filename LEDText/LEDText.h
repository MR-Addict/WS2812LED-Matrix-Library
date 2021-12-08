#ifndef _LEDTEXT_H_
#define _LEDTEXT_H_

#include <FastLED.h>
#include <LEDMatrix.h>
#include "Font4x6.h"

class cLEDText {
  public:
    CRGB *_leds;
    cLEDMatrix *_LEDMatrix;
    int8_t CursorX, CursorY;
    uint8_t FontWidth, FontHeight;
    uint8_t MATRIX_WIDTH, MATRIX_HEIGHT;
    cLEDText(CRGB *_leds, cLEDMatrix *_LEDMatrix) {
      FontWidth = Font[0];
      FontHeight = Font[1];
      CursorX = 0, CursorY = 0;
      this ->_leds = _leds;
      this ->_LEDMatrix = _LEDMatrix;
      MATRIX_WIDTH = (*_LEDMatrix).Width(), MATRIX_HEIGHT = (*_LEDMatrix).Height();
    }
    uint8_t Width() {
      return FontWidth;
    }
    uint8_t Height() {
      return FontHeight;
    }
    void SetCursor(int8_t x, int8_t y) {
      CursorX = x, CursorY = y;
    }
    void ScrollLeft() {
      CursorX--;
    }
    void ScrollRight() {
      CursorX++;
    }
    void ScrollUp() {
      CursorY--;
    }
    void ScrollDown() {
      CursorY++;
    }
    void Print(String string, CRGB Col) {
      uint8_t x = CursorX, y = CursorY;
      for (uint8_t i = 0; i < string.length(); i++, x += FontWidth) {
        PrintChar(x, y, string[i], Col);
      }
    }
  private:
    void PrintChar(int8_t DeltaX, int8_t DeltaY, uint8_t Char, CRGB Col) {
      for (uint8_t i = 0; i < FontHeight; i++) {
        for (uint8_t j = 0; j < FontWidth; j++) {
          boolean Value = bitRead(Font[i + FontHeight * Char + 2], 7 - j);
          if (Value)_leds[(*_LEDMatrix).GetXY(j + DeltaX, i + DeltaY)] = Col;
        }
      }
    }
};

#endif
