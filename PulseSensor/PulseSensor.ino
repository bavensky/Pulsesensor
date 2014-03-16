#include <LCD5110_Basic.h>
LCD5110 myGLCD(12,11,10,9,8);
extern uint8_t SmallFont[];
extern uint8_t MediumNumbers[];
extern uint8_t BigNumbers[];
int pulsePin = 0;                 
int blinkPin = 13;               
int fadePin = 5;                  
int fadeRate = 0;               

volatile int BPM;                  
volatile int Signal;               
volatile int IBI = 600;             
volatile boolean Pulse = false;     
volatile boolean QS = false;       

extern uint8_t logo[];
extern uint8_t logo2[];
extern uint8_t logo3[];


void setup(){
  myGLCD.InitLCD();
  pinMode(blinkPin,OUTPUT);         
  pinMode(fadePin,OUTPUT);          
  Serial.begin(115200);             
  interruptSetup();    
  myGLCD.drawBitmap(0, 0, logo, 84, 48);delay(2000);myGLCD.clrScr();
  myGLCD.drawBitmap(0, 0, logo2, 84, 48);delay(1000);myGLCD.clrScr();
  myGLCD.drawBitmap(0, 0, logo3, 84, 48);delay(1000);myGLCD.clrScr();

}



void loop(){
  sendDataToProcessing('S', Signal);     
  if (QS == true){                      
    fadeRate = 255;                  
    sendDataToProcessing('B',BPM);  
    sendDataToProcessing('Q',IBI);   
    QS = false;                       
  }

  myGLCD.clrScr();
  myGLCD.setFont(SmallFont);myGLCD.print(" Pulse Sensor ", CENTER, 0);
  myGLCD.setFont(SmallFont);
  myGLCD.print(" Heart rate ", CENTER, 8);
  myGLCD.setFont(SmallFont);
  myGLCD.print(" BPM :", LEFT, 24);
  myGLCD.setFont(MediumNumbers);
  myGLCD.printNumI(BPM, RIGHT, 24);

  //delay (5000);
  //BPM = min(BPM,200); float man = map(BPM,0,200,555,215);  
  ledFadeToBeat();  
  delay(20);           
}


void ledFadeToBeat(){
  fadeRate -= 15;                         
  fadeRate = constrain(fadeRate,0,255);   
  analogWrite(fadePin,fadeRate);          
}

void sendDataToProcessing(char symbol, int data ){
  Serial.print(symbol);                
  Serial.println(data);                
}








