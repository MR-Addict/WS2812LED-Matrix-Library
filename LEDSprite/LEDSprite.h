#ifndef _LEDSPRITE_H_
#define _LEDSPRITE_H_

#include <FastLED.h>
#include <LEDMatrix.h>
#include <LEDText.h>

class cLEDSprite {
  public:
    CRGB *_leds;
    cLEDMatrix *_LEDMatrix;
    cLEDSprite(CRGB *_leds, cLEDMatrix *_LEDMatrix) {
      this ->_leds = _leds;
      this ->_LEDMatrix = _LEDMatrix;
    }
    void Show(uint8_t *Sprite, uint8_t SpriteWidth, uint8_t SpriteHeight, int8_t x, int8_t y, CRGB ColA, CRGB ColB) {
      for (uint8_t i = 0; i < SpriteHeight; i++) {
        for (uint8_t j = 0; j < SpriteWidth; j++) {
          boolean Value = bitRead(Sprite[i * ((SpriteWidth - 1) / 8 + 1) + j / 8], 7 - j % 8);
          if (Value)_leds[(*_LEDMatrix).GetXY(j + x, i + y)] = ColA;
          else _leds[(*_LEDMatrix).GetXY(j + x, i + y)] = ColB;
        }
      }
    }
    void Show(uint32_t *Sprite, uint8_t SpriteWidth, uint8_t SpriteHeight, int8_t x, int8_t y) {
      for (uint8_t i = 0; i < SpriteHeight; i++) {
        for (uint8_t j = 0; j < SpriteWidth; j++) {
          _leds[(*_LEDMatrix).GetXY(j + x, i + y)] = Sprite[i * SpriteWidth + j];
        }
      }
    }
};

#endif