#include<PlaybackHandler.h>

#define pin3HIGH() PORTD |= (1 << PD3)
#define pin3LOW() PORTD &= ~(1 << PD3)

PlaybackBuffer playbackBuffer;

AVG_calculator::AVG_calculator(uint8_t Size){
    Nums = Size;
    Avg = UINT16_MAX;
}

uint16_t AVG_calculator::Update(uint16_t sample){
    Avg -= Avg / Nums;
    Avg += sample / Nums;
    return Avg;
}

RingBuffer::RingBuffer(){
    writeindex = 0;//sætter 
    readindex = 0;
}
void RingBuffer::begin(){
    Serial.begin(115200);
    Serial.print("Laver buffer pointers: ");
    for(int i = 0; i < numOfBuffers; i++){
        bufferPointers[i] = &completeBuffer[i * 16]; //finder alle indexes til de nødvendige buffers
        Serial.print(" \t ");
        Serial.print(i);
        Serial.print(": ");
        Serial.print((uint16_t)bufferPointers[i]);
    }
    Serial.println(" [OK!]");
    int x = 0;
    for (uint32_t i = 0; i < INT32_MAX; i++)
    {
        x += i;
    }
    writeindex = 0;//sætter 
    readindex = 0;
}

//Laver dem atomiske
void RingBuffer::writeSample(uint16_t Sample){
    completeBuffer[writeindex] = Sample;
    writeindex = (writeindex + 1) % (numOfBuffers*16);
    buffersBehind++;
}
uint16_t RingBuffer::readSample(){
    uint16_t sample = completeBuffer[readindex];
    readindex = (readindex + 1) % (numOfBuffers*16);
    buffersBehind--;
    return sample;
}
uint16_t* RingBuffer::getPayloadPointer(){
    return bufferPointers[payloadIndex];
}
void RingBuffer::increment(){
    payloadIndex = (payloadIndex + 1) % numOfBuffers;
    buffersBehind += 16;
}


void RingBuffer::writePayload(uint16_t* Sample){
    
}
void RingBuffer::readPayload(uint16_t* Sample){

}

PlaybackBuffer::PlaybackBuffer(){
    payloadPeriodAvg = AVG_calculator(50); //Constructor for avgudregneren

}




void PlaybackBuffer::StorePayLoad_Fast(){
    buffer.increment();
    uint16_t counts = TCNT1; 
    uint16_t ticks_Since = counts + SamplesPlayed*OCR1A;
    payloadPeriodAvg.Update(ticks_Since);
    uint16_t playbackPeriod = payloadPeriodAvg.Avg / 16;
    playbackPeriod -= (buffer.buffersBehind - bufferAim) * Delta;
    SamplesPlayed = 0;
    ChangePeriod = playbackPeriod;
    ChangePeriodFlag = 1;
}


/**
 * Gemmer en 16 bits payload i bufferen
*/
void PlaybackBuffer::StorePayLoad(uint16_t* input){ 
    //digitalWrite(3, HIGH);

    for (int i = 0; i < 16; i++) //langsom kopiering
    {
        buffer.writeSample(input[i]);
    }    

    cli();
    uint16_t counts = TCNT1; 
    uint16_t ticks_Since = counts + SamplesPlayed*OCR1A;
    uint16_t playbackPeriod = payloadPeriodAvg.Avg / 16;
    playbackPeriod -= (buffer.buffersBehind - bufferAim) * Delta;
    if(buffer.buffersBehind < 0){ //hvis bufferen er foran
        playbackPeriod = playbackPeriod;
    }
    SamplesPlayed = 0;
    OCR1A = playbackPeriod;
    TCNT1 = 0;
    sei();

    payloadPeriodAvg.Update(ticks_Since);
    /*
    sei();
    Serial.print("OCR1A: ");
    Serial.print(playbackPeriod);
    Serial.print("   Samples played: ");
    Serial.print(SamplesPlayed);
    Serial.print("   Total: ");
    Serial.print(ticks_Since);
    Serial.print("   Bufferbehind: ");
    Serial.print(buffer.buffersBehind);
    Serial.print("   AVG: ");
    Serial.println(payloadPeriodAvg.Avg);
    cli();
    */




    /*
    if(buffer.buffersBehind < bufferedMin){ //hvis vi er få buffers efter
        playbackPeriod = payloadPeriodAvg.Avg /15;
    }
    if(buffer.buffersBehind > bufferedMax){ //hvis vi er for mange buffers efter
        playbackPeriod = payloadPeriodAvg.Avg / 17; //kører hurtigere
    }
    if(buffer.buffersBehind < 0 ){ //Hvis bufferen er foran
        playbackPeriod = UINT16_MAX;
    }
    */
  

    




    //digitalWrite(3, LOW);
}

uint16_t PlaybackBuffer::GetSample(){
    SamplesPlayed++;
    return buffer.readSample();

}



/**
 * Sætter timeren op osv.
*/
void PlaybackBuffer::begin(){
    buffer.begin();
    cli();
    TCCR1A = B00000000; //kobler så TCCR1 ikke er forbundet til nogle pins
    TCCR1B = B00001001; //setter prescaler til 1 og CTC
    OCR1A = INT16_MAX; //sætter periodetiden til det maksiamlt tilladte
    TIMSK1 = B00000010;  //slår mask til for OCIE1A
    sei();
}


uint16_t tak = 0;
/**
 * @brief ISR routine for at gengive et sample med den estimerede periodetid i COMP1A
 * 
 */
ISR(TIMER1_COMPA_vect){ //playbackhandleren. Hvor tit timeren skal køres er styret af compA
    TIMSK1 &= ~(B00000010);
    if(playbackBuffer.ChangePeriodFlag){
        OCR1A = playbackBuffer.ChangePeriod;
    }
    TIMSK1 |= (B00000010);
    TIFR1 &= ~(B00000010); //just in case flaget er mækreligt
    uint16_t sample = playbackBuffer.GetSample();
    sample &= 0x03FF;
    DAC::write_10bit(sample);
} 