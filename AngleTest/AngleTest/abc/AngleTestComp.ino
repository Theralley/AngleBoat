#include<Wire.h>
#include <TM1637Display.h>

#define CLK 8
#define DIO 9

TM1637Display display(CLK,DIO);

const int MPU_addr=0x68;
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

int minVal=624; // 589
int maxVal=734; // 734
static int Dnr = 1000;
static float Multiplier = 0.08;

static int PrevY = 0;

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
  
  display.setBrightness(0x0f);
}

void loop(){
  uint8_t data[] = {0x0, 0x0, 0x0, 0x0};
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
  
  y= RAD_TO_DEG * (atan2(-xAng, -zAng)+PI);

  if(y <= 100){  

    y = (((Multiplier*y)) + ((1 - Multiplier)*PrevY));
  
    PrevY = y;
  
     Serial.print("AngleY= ");
     Serial.println(y);
  
    display.setSegments(data);
    display.showNumberDec(y, false, 4, 0);
  }

   
   Serial.println("-----------------------------------------");

   delay(Dnr);
}
