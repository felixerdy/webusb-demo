#include <Adafruit_NeoPixel.h>
#include <WebUSB.h>


Adafruit_NeoPixel rgb_led = Adafruit_NeoPixel(1,1,NEO_RGB + NEO_KHZ800);
WebUSB WebUSBSerial(1 /* https:// */, "webusb.netlify.com/rgb/");

#define Serial WebUSBSerial

int color[3];
int colorIndex;

void setup() {
  while (!Serial) {
    ;
  }
  Serial.begin(9600);
  Serial.write("Sketch begins.\r\n");
  Serial.flush();
  colorIndex = 0;

  rgb_led.begin();

}

void loop() {
  if (Serial && Serial.available()) {
    color[colorIndex++] = Serial.read();
    if (colorIndex == 3) {
      rgb_led.setPixelColor(0,rgb_led.Color(color[0],color[1],color[2]));
      rgb_led.show();
      
      colorIndex = 0;
    }
  }
}
