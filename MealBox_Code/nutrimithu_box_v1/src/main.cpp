#include <HX711.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define DOUT 13
#define CLK 12
HX711 scale;

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// float calibration_factor = -7050; // Adjust after calibration

void setup() {
  Serial.begin(115200);
  scale.begin(DOUT, CLK);
  // scale.set_scale(calibration_factor);
  scale.tare();

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED init failed");
    while (true);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Scale Init");
  display.display();
  delay(1000);
}

void loop() {
  float weight = scale.get_units(10);
  display.clearDisplay();
  display.setCursor(0, 10);
  display.print("Weight: ");
  display.print(weight, 1);
  display.println(" g");
  display.display();
  delay(500);
}
