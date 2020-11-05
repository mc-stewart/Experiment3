/* 

Inconvenient Interface
By Mairead Stewart
For DIGF 6037 - Creation & Computation
November 6, 2020

Sending pitch and roll code from https://github.com/DigitalFuturesOCADU/CC2020
*/

int ledPin1 = 13;
int ledPin2 = 12;
int ledPin3 = 11;
int ledPin4 = 10;
int ledPin5 = 9;
int ledPin6 = 8;
int ledPin7 = 7;
int ledPin8 = 6;
int ledPin9 = 5;
int ledPin10 = 4;
int ledPin11 = 3;
int ledPin12 = 2;

float lightUp();


#include "SparkFunLSM6DS3.h"
#include "Wire.h"
#include "six_axis_comp_filter.h"


LSM6DS3 nano33IMU(I2C_MODE, 0x6A); //define the IMU object
CompSixAxis CompFilter(0.1, 2); //define the filter object


float pitch;
float roll;


void setup() 
{
  Serial.begin(9600);
  
  //Call .begin() to configure the IMU (Inertial Measurement Unit)
  nano33IMU.begin();

  pinMode (ledPin1,OUTPUT);
  pinMode (ledPin2,OUTPUT);
  pinMode (ledPin3,OUTPUT);
  pinMode (ledPin3,OUTPUT);
  pinMode (ledPin4,OUTPUT);
  pinMode (ledPin5,OUTPUT);
  pinMode (ledPin6,OUTPUT);
  pinMode (ledPin7,OUTPUT);
  pinMode (ledPin8,OUTPUT);
  pinMode (ledPin9,OUTPUT);
  pinMode (ledPin10,OUTPUT);
  pinMode (ledPin11,OUTPUT);
  pinMode (ledPin12,OUTPUT);
}


void loop() 
{
  if (pitch>= 20) {


  digitalWrite(ledPin1,true);
  digitalWrite(ledPin2,true);
  digitalWrite(ledPin3,true);
  digitalWrite(ledPin4,true);
  digitalWrite(ledPin5,true);
  digitalWrite(ledPin6,true);
  digitalWrite(ledPin7,true);
  digitalWrite(ledPin8,true);
  digitalWrite(ledPin9,true);
  digitalWrite(ledPin10,true);
  digitalWrite(ledPin11,true);
  digitalWrite(ledPin12,true);

  } else {
  digitalWrite(ledPin1,false);
  digitalWrite(ledPin2,false);
  digitalWrite(ledPin3,false);
  digitalWrite(ledPin4,false);
  digitalWrite(ledPin5,false);
  digitalWrite(ledPin6,false);
  digitalWrite(ledPin7,false);
  digitalWrite(ledPin8,false);
  digitalWrite(ledPin9,false);
  digitalWrite(ledPin10,false);
  digitalWrite(ledPin11,false);
  digitalWrite(ledPin12,false);
  
  }
  
calculatePitchAndRoll();
}


void calculatePitchAndRoll()
{
  float accelX, accelY, accelZ, // variables to store sensor values
      gyroX, gyroY, gyroZ,
      xAngle, yAngle;       

  //  Get all motion sensor (in this case LSM6DS3) parameters,
  //  If you're using a different sensor you'll have to replace the values
  accelX = nano33IMU.readFloatAccelX();
  accelY = nano33IMU.readFloatAccelY();
  accelZ = nano33IMU.readFloatAccelZ();

  gyroX = nano33IMU.readFloatGyroX();
  gyroY = nano33IMU.readFloatGyroY();
  gyroZ = nano33IMU.readFloatGyroZ();

  // Convert these values into angles using the Complementary Filter
  CompFilter.CompAccelUpdate(accelX, accelY, accelZ); // takes arguments in m/s^2
  CompFilter.CompGyroUpdate(gyroX, gyroY, gyroZ); // takes arguments un rad/s 
  CompFilter.CompUpdate();
  CompFilter.CompStart();

  // Get angle relative to X and Y axes and write them to the variables in the arguments
  //in radians
  CompFilter.CompAnglesGet(&xAngle, &yAngle);

  //convert from radians to angles
  pitch = xAngle*RAD_TO_DEG;
  roll = yAngle*RAD_TO_DEG;

  
  Serial.print(pitch);
  Serial.print(",");
  Serial.println(roll);

  //this is need for stability of the connection
  delay(100);
}
