#ifndef _LEDTEXT_H_
#define _LEDTEXT_H_

#include "Font4x6.h"

class cLEDText {
  private:
    CRGB *_leds;
    cLEDMatrix *_LEDMatrix;
    int8_t CursorX, CursorY;
    uint8_t FontWidth, FontHeight;
    uint8_t MATRIX_WIDTH, MATRIX_HEIGHT;
    void PrintChar(int8_t DeltaX, int8_t DeltaY, uint8_t Char, CRGB Col);
  public:
    cLEDText(CRGB *_leds, cLEDMatrix *_LEDMatrix) {
      FontWidth = Font[0];
      FontHeight = Font[1];
      CursorX = 0, CursorY = 0;
      this ->_leds = _leds;
      this ->_LEDMatrix = _LEDMatrix;
      MATRIX_WIDTH = (*_LEDMatrix).Width(), MATRIX_HEIGHT = (*_LEDMatrix).Height();
    }
    uint8_t Width();
    uint8_t Height();
    void SetCursor(int8_t x, int8_t y);
    void ScrollLeft();
    void ScrollRight();
    void ScrollUp();
    void ScrollDown();
    void Print(String string, CRGB Col);
};

#endif
