#include <Arduino.h>
#include <HAL.h>
#include <Ringbuffer.h>
#include <RF24.h>


/**
 * @brief Den endelige kode til DEV1 boardet, med udgangspunkt i arduino UNO'en og Det sample 
 **/



/*************************************
 ** Delte funktioner og deres jobs
*/


/**********************************
 ** Delte semaforer og buffere
 */
SampleBuffer sampleBuffer; //buffer til vores... samples



void NewMeasurement(){ //Kode der bliver kørt hver gang der er taget en ny måling
  gainController.Update(TurboAnalogRead::lastMeasurement);
  if(sampleBuffer.Store(TurboAnalogRead::lastMeasurement)){
    //Queuer::Queue_INT(&SerializeJob, 30);
  }
}

void Readbuttons(uint16_t* buf){
  bool buttons[3] = {0};

  buttons[0] = digitalRead(4); //((PIND >> PD4) & 0x01);
  buttons[1] = digitalRead(5); //((PIND >> PD5) & 0x01);
  buttons[2] = digitalRead(6); //((PIND >> PD6) & 0x01);

  buf[0] |= ((uint16_t)buttons[0] << 10);
  buf[0] |= ((uint16_t)buttons[1] << 11);
  buf[0] |= ((uint16_t)buttons[2] << 12);
}

void setup() {

  gainController.begin();
  
  TurboAnalogRead::Setup_timer(ADCChannel, NewMeasurement); //sætter den funktion der skal kaldes ved nye måling op

  SetupRadio();

  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  
  TurboAnalogRead::Measure(); //starter timer
}
int inttt = 0;
uint16_t* outputBuffer;
void loop() {
  if(sampleBuffer.bufferReady()){
    cli();
    outputBuffer = sampleBuffer.Read();
    sei();
    Readbuttons(outputBuffer);
    bool result = radio.writeBlocking(outputBuffer, 32, 1); //!Evt brug writefast
  }
}

