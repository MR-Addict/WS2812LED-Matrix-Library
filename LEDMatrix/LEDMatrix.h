#ifndef _LEDMATRIX_H_
#define _LEDMATRIX_H_

#include <FastLED.h>

enum MatrixType {
    HORIZONTAL_MATRIX,
    VERTICAL_MATRIX,
    HORIZONTAL_ZIGZAG_MATRIX,
    VERTICAL_ZIGZAG_MATRIX,
    CUSTOM_MATRIX,
};

class cLEDMatrix {
  public:
    uint16_t NUM_LEDS;
    uint8_t MATRIX_WIDTH, MATRIX_HEIGHT;
    MatrixType myType;
    CRGB *_leds;
    cLEDMatrix(CRGB *_leds,MatrixType myType, uint8_t MATRIX_WIDTH, uint8_t MATRIX_HEIGHT) {
      this ->_leds = _leds;
      this ->myType = myType;
      this ->MATRIX_WIDTH = MATRIX_WIDTH, this ->MATRIX_HEIGHT = MATRIX_HEIGHT;
      NUM_LEDS = MATRIX_WIDTH * MATRIX_HEIGHT;
    }
    uint16_t Size() {
      return NUM_LEDS;
    }
    uint8_t Width() {
      return MATRIX_WIDTH;
    }
    uint8_t Height() {
      return MATRIX_HEIGHT;
    }
    uint16_t GetXY(int8_t x, int8_t y) {
      if(myType == HORIZONTAL_MATRIX){
        if (x >= MATRIX_WIDTH || x < 0 || y >= MATRIX_HEIGHT || y < 0)
          return NUM_LEDS;
        return (x + y * MATRIX_WIDTH);
      }
      else if(myType == VERTICAL_MATRIX){
        if (x >= MATRIX_WIDTH || x < 0 || y >= MATRIX_HEIGHT || y < 0)
          return NUM_LEDS;
        return (y + x * MATRIX_HEIGHT);
      }
      else if(myType == HORIZONTAL_ZIGZAG_MATRIX){
        if (x >= MATRIX_WIDTH || x < 0 || y >= MATRIX_HEIGHT || y < 0)
          return NUM_LEDS;
        if (y % 2 == 0)return (y * 8 + x);
          else return ((y + 1) * 8 - x - 1);
      }
      else if(myType == VERTICAL_ZIGZAG_MATRIX){
        if (x >= MATRIX_WIDTH || x < 0 || y >= MATRIX_HEIGHT || y < 0)
          return NUM_LEDS;
        if (x % 2 == 0)return (x * 8 + y);
          else return ((x + 1) * 8 - y - 1);
      }
      else if(myType == CUSTOM_MATRIX){
        if (x >= MATRIX_WIDTH || x < 0 || y >= MATRIX_HEIGHT || y < 0)
          return NUM_LEDS;
        if (y < MATRIX_HEIGHT / 2) {
          if (x % 2 == 0)return (x * 8 + y);
          else return ((x + 1) * 8 - y - 1);
        } else {
          if (x % 2 == 0)return (MATRIX_HEIGHT * MATRIX_WIDTH / 2 + x * 8 + (y - 8));
          else return (MATRIX_HEIGHT * MATRIX_WIDTH / 2 + (x + 1) * 8 - (y - 8) - 1);
        }
      }
    }
    void ShiftLeft() {
      for (uint8_t i = 0; i < MATRIX_WIDTH - 1; i++) {
        for (uint8_t j = 0; j < MATRIX_HEIGHT; j++)
          _leds[GetXY(i, j)] = _leds[GetXY(i + 1, j)];
      }
      for (uint8_t i = 0; i < MATRIX_HEIGHT; i++)
        _leds[GetXY(MATRIX_WIDTH - 1, i)] = CRGB::Black;
    }
    void ShiftRight() {
      for (uint8_t i = MATRIX_WIDTH - 1; i > 0; i--) {
        for (uint8_t j = 0; j < MATRIX_HEIGHT; j++)
          _leds[GetXY(i, j)] = _leds[GetXY(i - 1, j)];
      }
      for (uint8_t i = 0; i < MATRIX_HEIGHT; i++)
        _leds[GetXY(0, i)] = CRGB::Black;
    }
    void ShiftDown() {
      for (uint8_t i = MATRIX_HEIGHT - 1; i > 0; i--) {
        for (uint8_t j = 0; j < MATRIX_WIDTH; j++)
          _leds[GetXY(j, i)] = _leds[GetXY(j, i - 1)];
      }
      for (uint8_t i = 0; i < MATRIX_WIDTH; i++)
        _leds[GetXY(i, 0)] = CRGB::Black;
    }
    void ShiftUp() {
      for (uint8_t i = 0; i < MATRIX_HEIGHT - 1; i++) {
        for (uint8_t j = 0; j < MATRIX_WIDTH; j++)
          _leds[GetXY(j, i)] = _leds[GetXY(j, i + 1)];
      }
      for (uint8_t i = 0; i < MATRIX_WIDTH; i++)
        _leds[GetXY(MATRIX_HEIGHT - 1, 0)] = CRGB::Black;
    }
    void HorizontalMirror() {
      for (uint8_t i = 0; i < MATRIX_WIDTH / 2; i++) {
        for (uint8_t j =  0; j < MATRIX_HEIGHT; j++) {
          _leds[GetXY(MATRIX_WIDTH - i - 1, j)] = _leds[GetXY(i, j)];
        }
      }
    }
    void VerticalMirror() {
      for (uint8_t i = 0; i < MATRIX_HEIGHT / 2; i++) {
        for (uint8_t j =  0; j < MATRIX_WIDTH; j++) {
          _leds[GetXY(j, MATRIX_HEIGHT - i - 1)] = _leds[GetXY(j, i)];
        }
      }
    }
    void QuadrantMirror() {
      HorizontalMirror();
      VerticalMirror();
    }
    void DrawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, CRGB Col) {
      int16_t dx = x1 - x0;
      int16_t dy = y1 - y0;
      if (abs(dx) >= abs(dy)) {
        int32_t y = ((int32_t)y0 << 16) + 32768;
        if (dx == 0) {
          _leds[GetXY(x0, y >> 16)] = Col;
        } else {
          int32_t f = ((int32_t)dy << 16) / (int32_t)abs(dx);
          if (dx >= 0) {
            for (; x0 <= x1; ++x0, y += f)
              _leds[GetXY(x0, y >> 16)] = Col;
          } else {
            for (; x0 >= x1; --x0, y += f)
              _leds[GetXY(x0, y >> 16)] = Col;
          }
        }
      } else {
        int32_t f = ((int32_t)dx << 16) / (int32_t)abs(dy);
        int32_t x = ((int32_t)x0 << 16) + 32768;
        if (dy >= 0) {
          for (; y0 <= y1; ++y0, x += f)
            _leds[GetXY(x >> 16, y0)] = Col;
        } else {
          for (; y0 >= y1; --y0, x += f)
            _leds[GetXY(x >> 16, y0)] = Col;
        }
      }
    }
    void DrawRectangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, CRGB Col) {
      DrawLine(x0, y0, x0, y1, Col);
      DrawLine(x0, y1, x1, y1, Col);
      DrawLine(x1, y1, x1, y0, Col);
      DrawLine(x1, y0, x0, y0, Col);
    }

    void DrawCircle(int16_t xc, int16_t yc, uint16_t r, CRGB Col) {
      int16_t x = -r;
      int16_t y = 0;
      int16_t e = 2 - (2 * r);
      do {
        _leds[GetXY(xc + x, yc - y)] = Col;
        _leds[GetXY(xc - x, yc + y)] = Col;
        _leds[GetXY(xc + y, yc + x)] = Col;
        _leds[GetXY(xc - y, yc - x)] = Col;
        int16_t _e = e;
        if (_e <= y)e += (++y * 2) + 1;
        if ((_e > x) || (e > y))e += (++x * 2) + 1;
      } while (x < 0);
    }
    void DrawFilledRectangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, CRGB Col) {
      int16_t y = min(y0, y1);
      for (int16_t c = abs(y1 - y0); c >= 0; --c, ++y)
        DrawLine(x0, y, x1, y, Col);
    }
    void DrawFilledCircle(int16_t xc, int16_t yc, uint16_t r, CRGB Col) {
      int16_t x = r;
      int16_t y = 0;
      int16_t e = 1 - x;
      while (x >= y) {
        DrawLine(xc + x, yc + y, xc - x, yc + y, Col);
        DrawLine(xc + y, yc + x, xc - y, yc + x, Col);
        DrawLine(xc - x, yc - y, xc + x, yc - y, Col);
        DrawLine(xc - y, yc - x, xc + y, yc - x, Col);
        ++y;
        if (e >= 0) {
          x--;
          e += 2 * ((y - x) + 1);
        }
        else e += (2 * y) + 1;
      }
    }
};

#endif