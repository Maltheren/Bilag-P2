#include <Ringbuffer.h>

SampleBuffer::SampleBuffer(){
    bufferindex = 0;
    for (uint8_t i = 0; i < bufferSize; i++)
    {
        bufferPointers[i] = &CompleteBuffer[i*16];
    }
}
/**
 * @brief Funktion til ligge i sample i bufferen.
 * @param input 16 bit sample
 * @return true Hvis en payload er klar (dvs 16 samples)
 * @return false Hvis en payload ikke er klar
 */
bool SampleBuffer::Store(uint16_t input){
    bool payloadReady = 0;
    buffersBehind++;
    CompleteBuffer[bufferindex] = input;
    bufferindex = (bufferindex + 1) % (bufferSize*16);
    if((bufferindex % 16) == 0) { //hver gang en ny buffer er klar
        payloadReady = true;
        outputIndex = (outputIndex + 1) % 4; //sætter pointeren til næste buffer
    }
    return payloadReady;
}

/**
 * @brief Henter den nyeste payload i bufferen
 * 
 * @return uint16_t* pointer til et array på 16 samples 
 */
uint16_t* SampleBuffer::ReadMostRecent(){
    buffersBehind -= 16;
    return bufferPointers[outputIndex]; //Henter addressen på den nyeste buffer
}
uint16_t* SampleBuffer::Read(){
    buffersBehind -= 16;
    uint16_t* result = bufferPointers[bufferpointerIndex];
    bufferpointerIndex = (bufferpointerIndex + 1) % bufferSize;
    return result;
}

bool SampleBuffer::bufferReady(){
    bool temp = false;
    cli();
    if(buffersBehind > 16){
        temp = true;
    }
    sei();
    return temp;
}