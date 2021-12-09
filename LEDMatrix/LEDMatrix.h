#ifndef _LEDMATRIX_H_
#define _LEDMATRIX_H_

enum MatrixType {
  HORIZONTAL_MATRIX,
  VERTICAL_MATRIX,
  HORIZONTAL_ZIGZAG_MATRIX,
  VERTICAL_ZIGZAG_MATRIX,
  CUSTOM_MATRIX,
};

class cLEDMatrix {
  private:
    uint16_t NUM_LEDS;
    uint8_t MATRIX_WIDTH, MATRIX_HEIGHT;
    MatrixType myType;
    CRGB *_leds;
  public:
    cLEDMatrix(CRGB *_leds, MatrixType myType, uint8_t MATRIX_WIDTH, uint8_t MATRIX_HEIGHT) {
      this ->_leds = _leds;
      this ->myType = myType;
      this ->MATRIX_WIDTH = MATRIX_WIDTH, this ->MATRIX_HEIGHT = MATRIX_HEIGHT;
      NUM_LEDS = MATRIX_WIDTH * MATRIX_HEIGHT;
    }
    uint16_t Size();
    uint8_t Width();
    uint8_t Height();
    uint16_t GetXY(int8_t x, int8_t y);
    void ShiftLeft();
    void ShiftRight();
    void ShiftDown();
    void ShiftUp();
    void HorizontalMirror();
    void VerticalMirror();
    void QuadrantMirror();
    void DrawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, CRGB Col);
    void DrawRectangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, CRGB Col);
    void DrawCircle(int16_t xc, int16_t yc, uint16_t r, CRGB Col);
    void DrawFilledRectangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, CRGB Col);
    void DrawFilledCircle(int16_t xc, int16_t yc, uint16_t r, CRGB Col);
};

#endif