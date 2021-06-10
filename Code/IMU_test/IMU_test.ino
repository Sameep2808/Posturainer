#include <Wire.h>
const int MPU = 0x68; 
float AccX, AccY, AccZ;
float GyroX, GyroY, GyroZ,ogz=0,ogx=0,ogy=0;
float accAngleX, accAngleY, gyroAngleX, gyroAngleY, gyroAngleZ;
float roll, pitch, yaw;
float AccErrorX, AccErrorY, GyroErrorX, GyroErrorY, GyroErrorZ;
float elapsedTime, currentTime, previousTime;
int c = 0;
void setup() {
  Serial.begin(9600);
  Wire.begin();                      // Initialize comunication
  Wire.beginTransmission(MPU);       // Start communication with MPU6050 // MPU=0x68
  Wire.write(0x6B);                  // Talk to the register 6B
  Wire.write(0x00);                  // Make reset - place a 0 into the 6B register
  Wire.endTransmission(true);  
  
  // Configure Accelerometer Sensitivity - Full Scale Range (default +/- 2g)
  //Wire.beginTransmission(MPU);
  //Wire.write(0x1C);                  //Talk to the ACCEL_CONFIG register (1C hex)
  //Wire.write(0x10);                  //Set the register bits as 00010000 (+/- 8g full scale range)
  //Wire.endTransmission(true);
  // Configure Gyro Sensitivity - Full Scale Range (default +/- 250deg/s)
  Wire.beginTransmission(MPU);
  Wire.write(0x1B);                   // Talk to the GYRO_CONFIG register (1B hex)
  Wire.write(0x18);                   // Set the register bits as 00010000 (1000deg/s full scale)
  Wire.endTransmission(true);
  delay(20);
  
  
  delay(20);
  
}
void loop() {
  // === Read acceleromter data === //
  Wire.beginTransmission(MPU);
  Wire.write(0x3B); // Start with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 6, true);
  AccX = (Wire.read() << 8 | Wire.read()) / 16384.0; // X-axis value
  AccY = (Wire.read() << 8 | Wire.read()) / 16384.0; // Y-axis value
  AccZ = (Wire.read() << 8 | Wire.read()) / 16384.0; // Z-axis value
  accAngleX = (atan(AccY / sqrt(pow(AccX, 2) + pow(AccZ, 2))) * 180 / PI) - 0.58; // AccErrorX ~(0.58) See the calculate_IMU_error()custom function for more details
  accAngleY = (atan(-1 * AccX / sqrt(pow(AccY, 2) + pow(AccZ, 2))) * 180 / PI) + 1.58; // AccErrorY ~(-1.58)
  
  accAngleX+=10;
  accAngleY+=12.6;
  
  // === Read gyroscope data === //
  previousTime = currentTime;        // Previous time is stored before the actual time read
  currentTime = millis();            // Current time actual time read
  elapsedTime = (currentTime - previousTime) / 1000; // Divide by 1000 to get seconds
  Wire.beginTransmission(MPU);
  Wire.write(0x43); // Gyro data first register address 0x43
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 6, true); // Read 4 registers total, each axis value is stored in 2 registers
  GyroX = (Wire.read() << 8 | Wire.read()) / 16.4; // For a 250deg/s range we have to divide first the raw value by 131.0, according to the datasheet
  GyroY = (Wire.read() << 8 | Wire.read()) / 16.4;
  GyroZ = (Wire.read() << 8 | Wire.read()) / 16.4;
  GyroX+=4;
  GyroY-=1.95;
  GyroZ-=1.8;
  if(abs(GyroX-ogx)>1.5){
  gyroAngleX = gyroAngleX + GyroX * elapsedTime; // deg/s * s = deg
  ogx=GyroX;
  }
     
  if(abs(GyroY-ogy)>3){
  gyroAngleY = gyroAngleY + GyroY * elapsedTime;
  ogy=GyroY;
  }
    
  if(abs(GyroZ-ogz)>1.5){
  yaw =  yaw + GyroZ * elapsedTime;
  ogz=GyroZ;
  }
  //Serial.println(accAngleY);
  
  roll = 0.96 * gyroAngleX + 0.04 * accAngleX;
  pitch = 0.96 * gyroAngleY + 0.04 * accAngleY;
  
  // Print the values on the serial monitor
  Serial.print(roll);
  Serial.print("/");
  Serial.print(pitch);
  Serial.print("/");
  Serial.println(yaw);
}

