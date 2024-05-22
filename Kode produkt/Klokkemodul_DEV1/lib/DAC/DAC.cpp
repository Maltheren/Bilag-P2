#include <DAC.h>

void DAC::setup_10bit(){
  for (int i = 4; i < 8; i++)
  {
    pinMode(i, OUTPUT);
  }
  for (int i = 14; i < 20; i++){
    pinMode(i, OUTPUT);
  }
}

void DAC::setup_8bit(){
  for (int i = 4; i < 8; i++)
  {
    pinMode(i, OUTPUT);
  }
  for (int i = 14; i < 18; i++){
    pinMode(i, OUTPUT);
  }
}


void DAC::write_8bit(uint8_t input){
  cli();
  uint8_t temp = PORTD & ~B11110000; //sætter de laveste 4 bit
  temp |= input << 4;

  
  uint8_t temp2 = PORTC & ~B00001111;
  temp2 |= input >> 4;

  PORTD = temp;
  PORTC = temp2;
  sei();
}





void DAC::write_10bit(uint16_t input){
  cli();
  uint8_t temp = PORTD & ~B11110000; //sætter de laveste 4 bit
  temp |= input << 4;

  
  uint8_t temp2 = PORTC & ~B00111111;
  temp2 |= input >> 4;

  PORTD = temp;
  PORTC = temp2;
  sei();
}