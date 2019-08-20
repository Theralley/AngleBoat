#include<Wire.h>

const int MPU_addr=0x68;
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

int minVal=624; // 589
int maxVal=734; // 734
int TestCases=50;
int xAngTop, xAngBot, zAngTop, zAngBot;

double y, AngTop;
double AngBot = 10.0;
double ErrorRate, ErrorOccur;
double AppZAng, AppXAng, AppY;
bool hasRun;

double AngleArray[49];
int xAngArray[49];
int zAngArray[50];

void setup(){
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  Serial.begin(9600);
  hasRun = false;
  ErrorOccur = 0;
  
}
void loop(){
  if(hasRun == false){
    for(int counter = 0; counter <= TestCases-1; counter++){
      
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
       
       Serial.print("Nr: ");
       Serial.println(counter + 1);
       Serial.print("AngleY= ");
       Serial.println(y);
       Serial.print("-xAng= ");
       Serial.println(-xAng);
       Serial.print("-zAng= ");
       Serial.println(-zAng);
       
       Serial.println("-----------------------------------------");
       AngleArray[counter] = y;
       xAngArray[counter] = -xAng;
       zAngArray[counter] = -zAng;
  
       if(counter == 0){
        xAngTop = -xAng;
        zAngTop = -zAng;
       }
  
       //delay(200);
    }
    
    for(int i = 0; i < TestCases; i++){
      
      if(AngleArray[i] < 90){
        AppY = AppY + AngleArray[i];
      }
      
      if(AngleArray[i] > 90){
        ErrorOccur = ErrorOccur + 1;
      }
      
      if(AngleArray[i] < 90 && AngleArray[i] > AngTop){
        AngTop = AngleArray[i];
      }
      
      if(AngleArray[i] < AngBot){
        AngBot = AngleArray[i];
      }
    }
    
    for(int i = 0; i < TestCases; i++){
      if(xAngArray[i] < 0){
        AppXAng = AppXAng + xAngArray[i];
        
        if(xAngArray[i] > xAngTop){
          xAngTop = xAngArray[i];
        }
        
        if(xAngArray[i] < xAngBot){
          xAngBot = xAngArray[i];
        }
      }
    }
    
    for(int i = 0; i < TestCases; i++){
      AppZAng = AppZAng + zAngArray[i];
     
      if(zAngArray[i] > zAngTop){
        zAngTop = zAngArray[i];
      }
      
      if(zAngArray[i] < zAngBot){
        zAngBot = zAngArray[i];
      }
    }

    if(ErrorOccur > 0){
      ErrorRate = ErrorOccur/TestCases;
      ErrorRate *= 100;
    }

    Serial.print("Approx. AngY: ");
    Serial.println(AppY/TestCases);
    Serial.print("Approx. -zAng: ");
    Serial.println(AppZAng/TestCases);
    Serial.print("Approx. -xAng: ");
    Serial.println(AppXAng/TestCases);
    Serial.print("Top AngY: ");
    Serial.println(AngTop);
    Serial.print("Bot AngY: ");
    Serial.println(AngBot);
    Serial.print("Top -zAng: ");
    Serial.println(zAngTop);
    Serial.print("Bot -zAng: ");
    Serial.println(zAngBot);
    Serial.print("Top -xAng: ");
    Serial.println(xAngTop);
    Serial.print("Bot -xAng: ");
    Serial.println(xAngBot);
    Serial.print("minVal: ");
    Serial.println(minVal);
    Serial.print("maxVal: ");
    Serial.println(maxVal);
    Serial.print("Val Difference: ");
    Serial.println(maxVal-minVal);
    Serial.print("Error Rate: ");
    Serial.print(ErrorRate);
    Serial.println("%");

    Serial.println("-----------------------------------------");
  }
  hasRun = true;
}
