

//Include Files
#include <Servo.h>
#include <Wire.h>
#include "SoftI2CMaster.h"
#include "SoftWire.h"
#include "Lidar_Sam.h"
#include "Lidar_Sam.cpp"


void setup()
{
  Lidar.initialize
}

void loop()
{
  Lidar.lidarServo(0x00, 0x8f, readData, true, 0x62);
}

void receiveEvent()
{
  for (int x; x < Wire.available(); x++)
  {
    if (x < MAX_BYTES_RECEIVED)
    {
      commandReceiver[x] = Wire.read();
    }
    else
    {
      Wire.read();
    }
  }
}

void requestEvent()
{
  if (commandReceiver[0] == 0x01)
  {
    sendAllData();
  }
  else if (commandReceiver[0] == 0x02)
  {
    sendAngleData(&commandReceiver[1]);
  }
}





