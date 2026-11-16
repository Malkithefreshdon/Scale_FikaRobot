// Balance FikaRobot : cellule de charge 5 kg + HX711 sur ESP32-C6.
// HX711 : DT -> GPIO18, SCK -> GPIO19, VCC -> 3V3, GND -> GND.
//
// Commandes serie (115200) :
//   t          tare (remise a zero, plateau vide)
//   c<poids>   calibration avec un poids connu en grammes, ex: c200
//   r          affiche la valeur brute
#include <Arduino.h>
#include <HX711.h>
#include <Preferences.h>

constexpr uint8_t PIN_DT = 18;
constexpr uint8_t PIN_SCK = 19;
constexpr uint8_t PIN_LED = 8;  // LED RGB WS2812

HX711 scale;
Preferences prefs;
float scaleFactor = 1.0f;  // unites brutes par gramme

static void led(uint8_t r, uint8_t g, uint8_t b) { neopixelWrite(PIN_LED, r, g, b); }

static void tare() {
  Serial.println("Tare... ne touche pas au plateau");
  scale.tare(20);
  Serial.println("Tare OK");
}

static void calibrate(float knownGrams) {
  if (knownGrams <= 0) {
    Serial.println("Poids invalide");
    return;
  }
  long raw = scale.get_value(20);  // valeur moyenne moins la tare
  if (raw == 0) {
    Serial.println("Lecture nulle : pose le poids sur le plateau");
    return;
  }
  scaleFactor = (float)raw / knownGrams;
  scale.set_scale(scaleFactor);
  prefs.putFloat("factor", scaleFactor);
  Serial.printf("Calibration OK, facteur = %.3f (sauvegarde)\n", scaleFactor);
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("FikaRobot - balance HX711");

  prefs.begin("scale", false);
  scaleFactor = prefs.getFloat("factor", 1.0f);

  scale.begin(PIN_DT, PIN_SCK);
  if (!scale.wait_ready_timeout(2000)) {
    Serial.println("HX711 introuvable : verifie DT=GPIO18, SCK=GPIO19, VCC, GND");
    led(32, 0, 0);
    while (true) delay(1000);
  }
  scale.set_scale(scaleFactor);
  tare();
  led(0, 32, 0);
  Serial.println("Commandes : t = tare, c<g> = calibrer, r = brut");
}

void loop() {
  if (Serial.available()) {
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();
    if (cmd == "t") tare();
    else if (cmd.startsWith("c")) calibrate(cmd.substring(1).toFloat());
    else if (cmd == "r") Serial.printf("brut = %ld\n", scale.read());
  }

  if (scale.is_ready()) {
    Serial.printf("%.1f g\n", scale.get_units(5));
  }
  delay(200);
}
