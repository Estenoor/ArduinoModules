#include <Wire.h> //Include the I2C library to the IDE
#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, 7, NEO_GRB + NEO_KHZ800); //Declare a LED strip/ring with 16 pixels on pin 7

byte num = 0; //This is the variable set to the actual data value sent.
byte temp = 0; //This is the variable set to the extra address value sent. It will not be used.

void setup() {
  Wire.begin(1); //Open an I2C channel on address 
  Serial.begin(9600);
  Wire.onReceive(receiveEvent);
  strip.begin();
  strip.show();
}

void loop() {
  if (num == 2) {
    solidColor(strip.Color(0, 50, 0));
  }
  if (num == 3) {
    solidColor(strip.Color(50, 0, 0));
  }
}

void receiveEvent(int numBytes) {
  if (Wire.available()) {
    temp = Wire.read();
    num = Wire.read();
    Serial.println(num);
  }
}

void solidColor(uint32_t c) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
  }
}
