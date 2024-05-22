#include <Arduino.h>
#include <HAL.h>
#include <DAC.h>

#define pin3HIGH() PORTD |= (1 << PD3)
#define pin3LOW() PORTD &= ~(1 << PD3)


int yesss = 0;
uint8_t pipeAddress;
uint16_t buffer[16] = {0};
void PacketRecieved(){ //! brug __attribute__((always_inline)) for optimering  
  yesss++;
}

void setup() {
  //Serial.begin(115200);
  //printf_begin();
  //Serial.println("start reciever");
  DAC::setup_10bit();
  playbackBuffer.begin();
  SetupRadio(PacketRecieved);
  pinMode(10, OUTPUT);
  pinMode(3, OUTPUT);
}

void HandlePorts(uint16_t* buf){
  uint8_t buttons;
  buttons = bitRead(buf[0], 10);
  buttons |= bitRead(buf[0], 11) << 1;
  buttons |= bitRead(buf[0], 12) << 2;
  PORTD &= ~(1 << PD3);
  PORTB &= ~(1 << PB2);

  switch (buttons)
  {
  case B00000001: 
    PORTD |= (1 << PD3); //MUX Update 1
    break;
  case B00000010:
    PORTB |= (1 << PB2); //MUX UPDATE 2
    break;
  case B00000100:
    PORTD |= (1 << PD3); //MUX Update 1
    PORTB |= (1 << PB2); //MUX UPDATE 2
    break;
  default:
    break;
  }
}

void loop() {
  if(yesss){  
    cli();
    uint16_t* buf = playbackBuffer.buffer.getPayloadPointer();
    sei();
    radio.read(buf, 32);
    HandlePorts(buf);
    cli();
    playbackBuffer.StorePayLoad_Fast();
    yesss--;
    sei();
  }
}

