#include<Wire.h>

const int MPU_addr=0x68;
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

int minVal=624; // 589
int maxVal=734; // 734
static int Dnr = 1000;

int xAngRes = 0;
int yAngRes = 0;
int zAngRes = 0;

double y;

void setup(){
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  Serial.begin(9600);

  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);
  AcXRes=Wire.read()<<8|Wire.read();
  AcYRes=Wire.read()<<8|Wire.read();
  AcZRes=Wire.read()<<8|Wire.read();

  xAngRes = map(AcX,minVal,maxVal,-90,90);
  yAngRes = map(AcY,minVal,maxVal,-90,90);
  zAngRes = map(AcZ,minVal,maxVal,-90,90);
}

void loop(){
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);
  AcX=Wire.read()<<8|Wire.read();
  AcY=Wire.read()<<8|Wire.read();
  AcZ=Wire.read()<<8|Wire.read();
  int xAng = map(AcX,minVal,maxVal,-90,90);
  int yAng = map(AcY,minVal,maxVal,-90,90);
  int zAng = map(AcZ,minVal,maxVal,-90,90);

  xAng = xAng - xAngRes;
  yAng = yAng - yAngRes;
  zAng = zAng - zAngRes;
  
   y= RAD_TO_DEG * (atan2(-xAng, -zAng)+PI);
   
   Serial.print("AngleY= ");
   Serial.println(y);
   
   Serial.println("-----------------------------------------");

   delay(Dnr);
}
