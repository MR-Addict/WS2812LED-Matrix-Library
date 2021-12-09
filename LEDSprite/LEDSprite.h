#ifndef _LEDSPRITE_H_
#define _LEDSPRITE_H_

class cLEDSprite {
  private:
    CRGB *_leds;
    cLEDMatrix *_LEDMatrix;
  public:
    cLEDSprite(CRGB *_leds, cLEDMatrix *_LEDMatrix) {
      this ->_leds = _leds;
      this ->_LEDMatrix = _LEDMatrix;
    }
    void Show(const uint8_t *Sprite, uint8_t SpriteWidth, uint8_t SpriteHeight, int8_t x, int8_t y, CRGB ColA, CRGB ColB);
    void Show(const uint32_t *Sprite, uint8_t SpriteWidth, uint8_t SpriteHeight, int8_t x, int8_t y);
};

#endif