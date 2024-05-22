#include <Arduino.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <TurboAnalogRead.h>

#include "Wire.h"

int S1 = 6; //S1S2
int S2 = 7; //Lunge
int S3 = 8; //Generel

float output1;
float output2;
float output3;

#define btn1 3 
#define btn2 4 
#define btn3 5 

int knapValg(){
  bool knap1 = digitalRead(btn1);
  bool knap2 = digitalRead(btn2);

  if(knap1 && !knap2){
    return 1;  
  }
  else if(knap2 && !knap1){
    return 2;
  }
  else if (knap1 && knap2){
    return 3;
  }
  else{
    return 0;
  }
}

void filterS1S2(){
  digitalWrite(S1, HIGH);
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
}

void filterLunge(){
  digitalWrite(S1, LOW);
  digitalWrite(S2, HIGH);
  digitalWrite(S3, LOW);
}

void filterGenerel(){
  digitalWrite(S1, LOW);
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
}

void setup(){
  pinMode(btn1, INPUT);
  pinMode(btn2, INPUT);
  pinMode(btn3, INPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(A0,INPUT);
  Serial.begin(921600);

TurboAnalogRead::Setup_timer(0,NULL);

TurboAnalogRead::Measure();


}

void loop(){
  int knapTryk = knapValg();

if(TurboAnalogRead::flag){
Serial.println(TurboAnalogRead::lastMeasurement);
TurboAnalogRead::flag = 0;
}

  if (knapTryk == 1){
    filterS1S2();
    }
  else if (knapTryk == 2){
    filterLunge();
  }
  else if (knapTryk == 3){
    filterGenerel();
  }
  
}
  