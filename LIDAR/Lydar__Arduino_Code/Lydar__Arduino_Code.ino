//Include Files
#include <Servo.h>
#include <Wire.h>
#include <LIDARLite.h>
#include <SoftI2CMaster.h>

//Class Declarations
Servo servo;
LIDARLite lidar; //Default LidarLite address is 0x62

//Variable Declarations
int Distance[74];
int Degree[37] {45, 47.5, 50, 52.5, 55, 57.5, 60, 62.5, 65, 67.5, 70, 72.5, 75, 77.5, 80, 82.5, 85, 87.5, 90, 92.5, 95, 97.5, 100, 102.5, 105, 107.5, 110, 112.5, 115, 117.5, 120, 122.5, 125, 127.5, 130, 132.5, 135};
int returnLSB[2];
int returnDistance[2];
int x = 0;
int y = 0;
int z = 1;
bool servoRight = false;

void setup()
{
  servo.attach(9);
  servo.write(45);
  /*
      begin(int configuration, bool fasti2c, char lidarliteAddress)

      Starts the sensor and I2C.

      Parameters
      ----------------------------------------------------------------------------
      configuration: Default 0. Selects one of several preset configurations.
      fasti2c: Default 100 kHz. I2C base frequency.
        If true I2C frequency is set to 400kHz.
      lidarliteAddress: Default 0x62. Fill in new address here if changed. See
        operating manual for instructions.
  */
  lidar.begin(0, true); // Set configuration to default and I2C to 400 kHz
  /*
    configure(int configuration, char lidarliteAddress)

    Selects one of several preset configurations.

    Parameters
    ----------------------------------------------------------------------------
    configuration:  Default 0.
    0: Default mode, balanced performance.
    1: Short range, high speed. Uses 0x1d maximum acquisition count.
    2: Default range, higher speed short range. Turns on quick termination
        detection for faster measurements at short range (with decreased
        accuracy)
    3: Maximum range. Uses 0xff maximum acquisition count.
    4: High sensitivity detection. Overrides default valid measurement detection
        algorithm, and uses a threshold value for high sensitivity and noise.
    5: Low sensitivity detection. Overrides default valid measurement detection
        algorithm, and uses a threshold value for low sensitivity and noise.
    lidarliteAddress: Default 0x62. Fill in new address here if changed. See
    operating manual for instructions.
  */
  lidar.configure(0); // Change this number to try out alternate configurations

  Serial.begin(115200);

  //Wire.begin(0x11);
  //Wire.onRequest(requestEvent);
}

void loop()
{
  Serial.println(lidar.distance());
}



void requestEvent()
{
  // Wire.write(Distance, 74);
}

void getDistance() //Function to grab the Data from Lidar Lite V3 and move the Servo
{

  lidar.write(0x00, 0x04, 0x62);
  lidar.read(0x8f, 2, returnDistance[2], true, 0x62);

  int sendDistance = ((returnDistance[0] * 256) + returnDistance[1]);
  Serial.println(sendDistance);
  Serial.println(returnDistance[0]);
  Serial.println(returnDistance[1]);

  if (lidarBusy() == false)
  {
    servo.write(Degree[x]);

    Distance[y] = returnDistance[0];
    Distance[z] = returnDistance[1];
    if (x <= 36 && servoRight == false);
    {
      x++;
      if (x > 36)
      {
       servoRight = true;
      }
    }
    if (x >= 0 && servoRight == true)
    {
      x--;
      if (x < 0)
      {
       servoRight = false;
      }
    }

    y += 2;
    z += 2;

    delay(5);
    
  }
}

bool lidarBusy() //Function to test if the Lidar is done with the reading
{
  bool isBusy = true;

  int busyFlag = 1; //Monitors when the device is done with a measurement

  int busyCounter = 0; //Counts the number of times busy flag is checked, for timeout

  while (busyFlag != 0) //Loop until device is not busy
  {
    Wire.beginTransmission(0x62);
    Wire.write(0x01);

    Wire.requestFrom(0x62, 1);
    busyFlag = bitRead(Wire.read(), 0); //Assign the LSB of the status register to busyFlag

    busyCounter++;

    if (busyCounter > 9999)
    {
      busyCounter = 0;
      Serial.println("Read Failed");
    }
    if (busyFlag == 0)
    {
      isBusy = false;
    }

  }
  return isBusy;
}

void findDistance() //Original Function to move the servo and get data from the Lidar Lite V3
{
  for (int x = 0; x <= 36; x++)
  {
    servo.write(Degree[x]);

    delay(500);

    Distance[x] = lidar.distance();
    /*
        Wire.beginTransmission(0x11);
        Wire.write(i2c_Communication[1]);
        Wire.write(i2c_Communication[2]);
        Wire.endTransmission();
    */
    Serial.println("Position ");
    Serial.println(x);
    Serial.println("Distance ");
    Serial.println(Distance[x]);
  }

  for (int x = 36; x >= 0; x--)
  {
    servo.write(Degree[x]);

    delay(500);

    Distance[x] = lidar.distance();

    // i2c_Communication[1] = x;
    // i2c_Communication[2] = Distance[x];
    /*
        Wire.beginTransmission(0x11);
        Wire.write(i2c_Communication[1]);
        Wire.write(i2c_Communication[2]);
        Wire.endTransmission();
    */
    Serial.println("Position ");
    Serial.println(x);
    Serial.println("Distance ");
    Serial.println(Distance[x]);

  }
}

