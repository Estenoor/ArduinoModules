
//#define DEBUG
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_TFTLCD.h> // Hardware-specific library
#include <Wire.h>

// The control pins for the LCD can be assigned to any digital or
// analog pins...but we'll use the analog pins as this allows us to
// double up the pins with the touch screen (see the TFT paint example).
#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0

#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin


// Assign human-readable names to some common 16-bit color values:
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
// If using the shield, all control and data lines are fixed, and
// a simpler declaration can optionally be used:
// Adafruit_TFTLCD tft;

int x = 0;

uint8_t lidarData[2];

void setup()
{
  tft.reset();
  uint16_t identifier = tft.readID();
  identifier = 0x9341;
  tft.begin(identifier);
  tft.setRotation(3);

  Serial.begin(9600);
  tft.fillScreen(BLACK);

  tft.setCursor(0, 0);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.println("Maurader's Tech");
  tft.println("Version 1.1");
  delay(1000);
  tft.fillScreen(BLACK);
  tft.setCursor(0, 0);

  Wire.begin(0x11);
}



void loop()
{
  lidarData[1] = Wire.read();    // receive a byte as character
  Serial.print("P = ");         // print the character
  Serial.println(lidarData[1]);
}

