// Test de la LED RGB (WS2812) integree a l'ESP32-C6-DevKitC-1 (GPIO8).
#include <Arduino.h>

#ifndef RGB_BUILTIN
#define RGB_BUILTIN 8
#endif

static void setColor(uint8_t r, uint8_t g, uint8_t b, const char *name) {
  Serial.println(name);
  neopixelWrite(RGB_BUILTIN, r, g, b);
  delay(700);
}

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println("FikaRobot - test LED RGB");
}

void loop() {
  setColor(32, 0, 0, "rouge");
  setColor(0, 32, 0, "vert");
  setColor(0, 0, 32, "bleu");
  setColor(32, 32, 32, "blanc");
  setColor(0, 0, 0, "eteint");
}
