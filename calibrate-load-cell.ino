#include <HX711.h>

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 3;
const int LOADCELL_SCK_PIN = 2;

HX711 scale;

void setup() {
  Serial.begin(9600);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.tare();
}

const float calibration_factor = -34.94897959; // Your calculated value here;

void loop() {
  Serial.print("Weight: ");
  Serial.print(scale.get_units(10) * calibration_factor);
  Serial.println(" grams");
}
