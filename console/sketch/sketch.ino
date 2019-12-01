#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "SenseBoxMCU.h"

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#include <WebUSB.h>

/**
   Creating an instance of WebUSBSerial will add an additional USB interface to
   the device that is marked as vendor-specific (rather than USB CDC-ACM) and
   is therefore accessible to the browser.

   The URL here provides a hint to the browser about what page the user should
   navigate to to interact with the device.
*/
WebUSB WebUSBSerial(1 /* https:// */, "webusb.github.io/arduino/demos/console");

#define Serial WebUSBSerial

const int ledPin = 7;

void setup() {
  while (!Serial) {
    ;
  }
  Serial.begin(9600);
  Serial.write("Sketch begins.\r\n> ");
  Serial.flush();
  pinMode(ledPin, OUTPUT);
  senseBoxIO.powerI2C(true);
  delay(2000);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3D);
  display.display();
  delay(100);
  display.clearDisplay();
}

void loop() {
  if (Serial && Serial.available()) {
    String input = Serial.readString();

    byte plain[input.length()];
    input.getBytes(plain, input.length());
    Serial.println(input);
    
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(1);
    display.setTextColor(WHITE, BLACK);
    display.print(String(input));
    display.display();
    
    Serial.write("\r\n> ");
    Serial.flush();
      

  }
}
