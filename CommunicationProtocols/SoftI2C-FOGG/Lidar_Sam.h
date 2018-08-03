#ifndef Lidar_Sam_h
#define Lidar_Sam_h

//Defining Pins for SoftI2C to work
#define SCL_PIN 3      //Define I2C Clock Pin as 11
#define SCL_PORT PORTB
#define SDA_PIN 2      //Define I2C Data Pin as 10
#define SDA_PORT PORTB
#define I2C_TIMEOUT 1000 //Set the timeout  
#define I2C_FASTMODE 1

#include <SoftI2CMaster.h>
#include <SoftWire.h>
#include <Wire.h>
#include <Servo.h>
#include <Arduino.h>

#define highArray 0
#define lowArray 1
#define MAX_BYTES_RECEIVED 4

class Lidar
{
 private:
     byte readData[2];
     int arrayPointer = 0;
     
     
 public:
    Lidar();
    Servo servo = Servo();
    SoftWire lidar = SoftWire(); 

    int lidarSerial[37];
    int commandReceiver[4];
    byte dataToSend[74];
    double degree = 45;
    
    void initialize(int ARDUINO_ADDR, long int SERIAL_BAUD);
    void sendAngleData(int anglePointer);
    void sendAllData();
    void lidarServo(char writeAdress, char readAddress, byte dataArray[2], bool moniterBusy, char lidarliteAddress);
    int  Busy(char lidarliteAddress);
    void Write(char myAddress, char myValue, char lidarliteAddress);
    void Read(char myAddress, int numOfBytes, byte arrayToSave[2], bool monitorBusyFlag, char lidarliteAddress);

    
};

#endif
