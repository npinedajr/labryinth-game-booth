#include <MPU6050_tockn.h> //Include the MPU6050_tockn library by tockn, making it easier to program the accelerometer connected.
#include <Wire.h> //Include the Wire library, which is required for I2C. 
#include <VarSpeedServo.h> //Include the VarSpeedServo library, which changes the speed servos rotate. 

VarSpeedServo servoOut; //Define a VarSpeedServo with the name servoOut, which will represent the servo in the outer ring of the labyrinth.
VarSpeedServo servoIn; //Define a VarSpeedServo with the name servoOut, which will represent the servo in the outer ring of the labyrinth.

MPU6050 mpu6050(Wire); //Create a MPU6050 object, where mpu6050 is the accelerometer connected.

float accelOut = 0;
float accelIn = 0;

void setup() {
  servoOut.write(58); //Set the initial position of servoOut to 58 degrees.
  servoOut.attach(9); //servoOut will be attached to pin 9 of the Arduino.
  servoIn.write(55); //Set the initial position of servoIn to 55 degrees/ 
  servoIn.attach(6); //servoIn will be attached to pin 6 of the Arduino.
  Wire.begin(); //I2C begins.
  mpu6050.begin(); //The accelerometer connected will initialize.
  mpu6050.calcGyroOffsets(true); //The accelerometer will calibrate to imrpove measurements.
}

/*The following program will  read two values from the accelerometer: the angle in the x and y direction. 
 *These two values will control what angle the servos will change to. With the use of the VarSpeedServo library,
 *the servos will move slowly to ensure that the labryinth is safe and will not break due to rapid movements 
 *from the servos.
 */
void loop() {
  mpu6050.update();
  accelOut = mpu6050.getAngleY();
  accelOut = map(accelOut,-90,90,40,76);
  accelIn = mpu6050.getAngleX();
  accelIn = map(accelIn,-50,90,46,76);
  servoOut.write(accelOut,21);
  servoIn.write(accelIn,21);
}
