#include <Wire.h>
#include <VL53L0X.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

VL53L0X sensor;
int cm;

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup()
{
  Serial.begin(9600);
  Wire.begin();

  sensor.setTimeout(500);
  if (!sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor!");
    while (1) {}
  }

  // Start continuous back-to-back mode (take readings as
  // fast as possible).  To use continuous timed mode
  // instead, provide a desired inter-measurement period in
  // ms (e.g. sensor.startContinuous(100)).
  sensor.startContinuous();

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  delay(2000);
  display.clearDisplay();
  display.setTextColor(WHITE);
  delay(10);
}

void loop()
{
  //Serial.print(sensor.readRangeContinuousMillimeters());
  cm=(sensor.readRangeContinuousMillimeters())/10;
  Serial.println(cm);
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 10);
  display.print("Distance");
  display.setTextSize(3);
  display.setCursor(0, 35);
  display.print(cm);
  display.print(" cm");
  display.display();
  delay(500);
  if (sensor.timeoutOccurred()) { Serial.print(" TIMEOUT"); }

}
