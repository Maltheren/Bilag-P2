#include <Arduino.h>
#define bufferSize 4 //


class SampleBuffer{
    uint16_t CompleteBuffer[16*bufferSize]; //indehoder et langt array med alle subbufferene 
    uint16_t* bufferPointers[bufferSize];
    uint16_t bufferindex = 0;
    uint16_t outputIndex = 0;
    
    uint16_t bufferpointerIndex = 0;
    public:
    uint16_t buffersBehind = 0;
    SampleBuffer(); 
    bool Store(uint16_t input);
    uint16_t* ReadMostRecent(); //! Bliver ikke brugt
    uint16_t* Read();
    bool bufferReady();
};