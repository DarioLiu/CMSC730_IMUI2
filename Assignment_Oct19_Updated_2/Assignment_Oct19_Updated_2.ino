#include <Wire.h>
const int sda = 21;
const int scl = 22;
byte ACCEL_XOUT_H = 0;
byte ACCEL_XOUT_L = 0;
byte ACCEL_YOUT_H = 0;
byte ACCEL_YOUT_L = 0;
byte ACCEL_ZOUT_H = 0;
byte ACCEL_ZOUT_L = 0;
byte GYRO_XOUT_H = 0;
byte GYRO_XOUT_L = 0;
byte GYRO_YOUT_H = 0;
byte GYRO_YOUT_L = 0;
byte GYRO_ZOUT_H = 0;
byte GYRO_ZOUT_L = 0;
int selector = 0;
//int selector = 1;

int address = 0x68;


int16_t ACCEL_X_RAW = 0;
int16_t ACCEL_Y_RAW = 0;
int16_t ACCEL_Z_RAW = 0;

int16_t GYRO_X_RAW = 0;
int16_t GYRO_Y_RAW = 0;
int16_t GYRO_Z_RAW = 0;


float gX, gY, gZ; 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin(sda, scl);
 

}

void loop() {
  // Requesting high byte of ACCEL_X
  Wire.beginTransmission(address);
  Wire.write(0x3B); // Starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false); // Restart, not stop. This is important for multiple reads.
  Wire.requestFrom(address, 6, true); // Read 6 registers in a row

  ACCEL_X_RAW = Wire.read() << 8 | Wire.read();
  ACCEL_Y_RAW = Wire.read() << 8 | Wire.read();
  ACCEL_Z_RAW = Wire.read() << 8 | Wire.read();

  gX = ACCEL_X_RAW / 16384.0;
  gY = ACCEL_Y_RAW / 16384.0; 
  gZ = ACCEL_Z_RAW / 16384.0;   // Floating point division
  
  // Serial.print("gX: ");
  // Serial.print(gX);
  // Serial.print(",");
  // Serial.print(gY);
  // Serial.print(",");
  // Serial.println(gZ); 

  // Read Gyro Data
  Wire.beginTransmission(address);
  Wire.write(0x43); // Starting with register 0x43 (GYRO_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(address, 6, true); // Read 6 registers for XYZ gyro

  GYRO_X_RAW = Wire.read() << 8 | Wire.read();
  GYRO_Y_RAW = Wire.read() << 8 | Wire.read();
  GYRO_Z_RAW = Wire.read() << 8 | Wire.read();
 
  
  // Serial.print(" GYRORAW_X: ");
  // Serial.print(GYRO_X_RAW);
  // Serial.print(", GYRORAW_Y: ");
  // Serial.print(GYRO_Y_RAW);
  // Serial.print(", GYRORAW_Z: ");
  // Serial.println(GYRO_Z_RAW);

  //Serial.print(" GYRORAW_X: ");
  // Serial.print(GYRO_X_RAW);
  // Serial.print(",");
  // Serial.print(GYRO_Y_RAW);
  // Serial.print(",");
  // Serial.println(GYRO_Z_RAW);
  
  if (Serial.available()>0){
    char c = Serial.read();
    if (c == 'x') selector =0; //as default value
    else if (c=='y') selector =1; // condition 1 
    else if (c=='z') selector = 2;
    else selector = selector;

  }

  if (selector == 0 ){
      Serial.print(gX);
      Serial.print(",");
      Serial.println(GYRO_X_RAW);
      
      }
  else if(selector ==1){
      Serial.print(gY);
      Serial.print(",");
      Serial.println(GYRO_Y_RAW);
  }
  else {
      Serial.print(gZ);
      Serial.print(",");
      Serial.println(GYRO_Z_RAW);

      }
      
    
  delay(200);

}


