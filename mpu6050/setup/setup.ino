
#include <Wire.h>
float RateRoll, RatePitch, RateYaw;
float RateCalibrationRoll, RateCalibrationPitch, RateCalibrationYaw;
float RateCalibrationAccX, RateCalibrationAccY, RateCalibrationAccZ;
int RateCalibrationNumber;
float AccX, AccY, AccZ;
float AngleRoll, AnglePitch;

float LoopTimer;

float KalmanAngleRoll=0, KalmanUncertaintyAngleRoll=2*2;
float KalmanAnglePitch=0, KalmanUncertaintyAnglePitch=2*2;
float Kalman1DOutput[]={0,0};
void kalman_1d(float KalmanState, float KalmanUncertainty, float KalmanInput, float KalmanMeasurement) {
  KalmanState=KalmanState+0.004*KalmanInput;
  KalmanUncertainty=KalmanUncertainty + 0.004 * 0.004 * 4 * 4;
  float KalmanGain=KalmanUncertainty * 1/(1*KalmanUncertainty + 3 * 3);
  KalmanState=KalmanState+KalmanGain * (KalmanMeasurement-KalmanState);
  KalmanUncertainty=(1-KalmanGain) * KalmanUncertainty;
  Kalman1DOutput[0]=KalmanState; 
  Kalman1DOutput[1]=KalmanUncertainty;
}

void gyro_signals(void) {
  Wire.beginTransmission(0x68);//start i2c connection
  Wire.write(0x1A); //switch on lowpass filter to  avoid fibration
  Wire.write(0x05);
  Wire.endTransmission(); 

  Wire.beginTransmission(0x68);
  Wire.write(0x1C);//configure acclelerometre +-8g
  Wire.write(0x10);
  Wire.endTransmission();
  Wire.beginTransmission(0x68);
  Wire.write(0x3B);  //acces au registre accelerometre
  Wire.endTransmission(); 
  Wire.requestFrom(0x68,6);
  int16_t AccXLSB = Wire.read() << 8 | Wire.read();
  int16_t AccYLSB = Wire.read() << 8 | Wire.read();
  int16_t AccZLSB = Wire.read() << 8 | Wire.read();


  Wire.beginTransmission(0x68);// change sensitivity scale  in LSB /deg/s 
  Wire.write(0x1B); // we take 65.5 LSB/°/s
  Wire.write(0x8); 
  Wire.endTransmission(); 
  Wire.beginTransmission(0x68);
  Wire.write(0x43); //demander l'acces au registre 
  Wire.endTransmission();
  Wire.requestFrom(0x68,6);//prendre les 6 bit : X[15:8] X[7:0] YY ZZ
  int16_t GyroX=Wire.read()<<8 | Wire.read();
  int16_t GyroY=Wire.read()<<8 | Wire.read();
  int16_t GyroZ=Wire.read()<<8 | Wire.read();
  RateRoll=(float)GyroX/65.5; //supr LSB pour avoir deg/s
  RatePitch=(float)GyroY/65.5;
  RateYaw=(float)GyroZ/65.5;
  AccX=(float)AccXLSB/4096;  //+-8g -> 4096 LBS
  AccY=(float)AccYLSB/4096;
  AccZ=(float)AccZLSB/4096;
 
}
void setup() {
  Serial.begin(57600);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  Wire.setClock(400000);// setup clock speed
  Wire.begin();
  delay(250);
  Wire.beginTransmission(0x68); //start le gyro on power mode
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission();

  for (RateCalibrationNumber=0; //setup la calibration
         RateCalibrationNumber<2000; 
         RateCalibrationNumber ++) {
    gyro_signals();
    RateCalibrationRoll+=RateRoll;
    RateCalibrationPitch+=RatePitch;
    RateCalibrationYaw+=RateYaw;
      RateCalibrationAccX+=AccX;
    RateCalibrationAccY+=AccY;
    RateCalibrationAccZ+=AccZ;
    delay(1);
  }
  RateCalibrationRoll/=2000;
  RateCalibrationPitch/=2000;
  RateCalibrationYaw/=2000; 
  RateCalibrationAccX/=2000;
  RateCalibrationAccY/=2000;
  RateCalibrationAccZ/=2000;   
}
void loop() {
  gyro_signals();
  RateRoll-=RateCalibrationRoll;
  RatePitch-=RateCalibrationPitch;
  RateYaw-=RateCalibrationYaw;
  AccX-=RateCalibrationAccX;
  AccY-=RateCalibrationAccY;
  AccZ-=RateCalibrationAccZ;
   AngleRoll=atan(AccY/sqrt(AccX*AccX+AccZ*AccZ))*1/(3.142/180);
  AnglePitch=-atan(AccX/sqrt(AccY*AccY+AccZ*AccZ))*1/(3.142/180);
//  Serial.print("Roll rate [°/s]= ");
//  Serial.print(RateRoll);
//  Serial.print(" Pitch Rate [°/s]= ");
//  Serial.print(RatePitch);
//  Serial.print(" Yaw Rate [°/s]= ");
//  Serial.println(RateYaw);
//  Serial.print("Acceleration X [g]= ");
//  Serial.print(AccX);
//  Serial.print(" Acceleration Y [g]= ");
//  Serial.print(AccY);
//  Serial.print(" Acceleration Z [g]= ");
//  Serial.println(AccZ);
    Serial.print("angleRoll = ");
  Serial.print(AngleRoll);
  Serial.print(" angle Pitch= ");
  Serial.println(AnglePitch);
  kalman_1d(KalmanAngleRoll, KalmanUncertaintyAngleRoll, RateRoll, AngleRoll);
  KalmanAngleRoll=Kalman1DOutput[0]; 
  KalmanUncertaintyAngleRoll=Kalman1DOutput[1];
  kalman_1d(KalmanAnglePitch, KalmanUncertaintyAnglePitch, RatePitch, AnglePitch);
  KalmanAnglePitch=Kalman1DOutput[0]; 
  KalmanUncertaintyAnglePitch=Kalman1DOutput[1];
  Serial.print("Roll Angle [°] ");
  Serial.print(KalmanAngleRoll);
  Serial.print(" Pitch Angle [°] ");
  Serial.println(KalmanAnglePitch);
  while (micros() - LoopTimer < 4000);
  LoopTimer=micros();
 
}
