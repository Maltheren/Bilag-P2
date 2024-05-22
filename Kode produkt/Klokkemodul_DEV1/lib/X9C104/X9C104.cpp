#include <X9C104.h>

void X9C104::wipeUp(){
  if (currentPos < 99)
  {
    digitalWrite(ud,LOW);
    digitalWrite(inc,LOW);
    digitalWrite(inc,HIGH);
    currentPos++;
  }
}

void X9C104::wipeDown(){
  if (currentPos > 0)
  {
    digitalWrite(ud,HIGH);
    digitalWrite(inc,LOW);
    digitalWrite(inc,HIGH);
    currentPos--;
  }
  
  
}

X9C104::X9C104(int pin1, int pin2){
  inc=pin1;
  ud=pin2; 
  pinMode(inc, OUTPUT);
  pinMode(ud, OUTPUT);
    
  digitalWrite(inc,HIGH);

  reset();
}

void X9C104::reset(){
  for (int i = 0; i < 100; i++){
    digitalWrite(ud,HIGH);
    digitalWrite(inc,LOW);
    digitalWrite(inc,HIGH);
  }
  currentPos = 0;
}

void X9C104::setPos(int pos){
  if (pos > 99 || pos < 0)
  {
    return;
  }
  
  while (currentPos > pos)
  {
    wipeDown();
  }
  while (currentPos < pos)
  {
    wipeUp();
  }
  
  
}

