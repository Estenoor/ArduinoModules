//Include Files
#include <Adafruit_GFX.h>       // Core graphics library
#include <Adafruit_TFTLCD.h>    // Hardware-specific library

//Control Pins
#define LCD_CS A3               // Chip Select goes to Analog 3
#define LCD_CD A2               // Command/Data goes to Analog 2
#define LCD_WR A1               // LCD Write goes to Analog 1
#define LCD_RD A0               // LCD Read goes to Analog 0
#define LCD_RESET A4            // Can alternately just connect to Arduino's reset pin

//Defining Human-readable names to the Colors
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

//Variable Declarations
String companyName = "Maurader's Tech";
String Moniter;
String Input;
String serialInput;
uint16_t identifier;
int x = 0;

//Declare the Display Class and Define which pins are used
Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);


void setup()
{
  
  tft.reset();                  //Reset Display
  identifier = 0x9341;          //Set Identifier as 0x9341
  tft.begin(identifier);        //Start the Display with the correct Identifier
  tft.setRotation(3);           //Set Display Rotation as 3 (Horizontal)

  Serial.begin(9600);           //Initialize Serial Communications

  tft.fillScreen(BLACK);        //Set Background of Display Black
  tft.setCursor(0, 0);          //Set Cursor Location to upper left of Display
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.println(companyName);     //Print Company Name (Maurader's Tech) on Diplay
  tft.println("Version 1.1");   //Print Version Name on Display
  delay(1000);                  //Keep Display the Same for 1000 miliseconds
  tft.fillScreen(BLACK);        //Clear Text on Display by Setting the whole Screen Black
  tft.setCursor(0, 0);          //Set Cursor back to upper left of Display
}



void loop() 
{
  
  printSerialInput(getSerialInput());
}


//This Function will get the input from the Serial Moniter and set it equal to the 
//variable serialInput then returns serialInput
String getSerialInput()
{
  serialInput = Serial.readString();
  return serialInput;
}

//This Function Clears the Display by setting the whole screen the color Black
void clearScreen()
{
  tft.fillScreen(BLACK);
}

//This function takes the input from the Serial Moniter and decides what to do with it
void serialInputProccessor()
{
  
}

//This Method Prints the input from the Serial Moniter to the Display then moves the curser 
//down 15 pixels so the text doesn't overlap
void printSerialInput(String Output) 
{
  if (Serial.available())
  {
  tft.setCursor(0, x);
  tft.setTextColor(GREEN);
  tft.setTextSize(2);
  tft.println(">> " + Output);  
  x = x + 15;
  }
}

