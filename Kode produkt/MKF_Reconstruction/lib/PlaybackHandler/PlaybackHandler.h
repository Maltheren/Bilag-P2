#include<Arduino.h>
#include<DAC.h>
#define numOfBuffers 16


#define bufferAim 64
#define Delta 10



class AVG_calculator{

    uint8_t Nums;
    public: 
    AVG_calculator(uint8_t Size);
    uint16_t Avg;
    uint16_t Update(uint16_t Sample);
};



/**
 * Vi får brug for en måde at køre en timer på for at tjekke tiden for hver gang en buffer loadet
*/
class RingBuffer{
    uint16_t completeBuffer[numOfBuffers * 16]; //laver en buffer på der kan holde det hele.
    uint16_t* bufferPointers[numOfBuffers];   //de forskellige startpunker
    uint16_t readindex;
    uint16_t writeindex;
    uint16_t payloadIndex;
    

    public:

    /**
     * @brief Laver en ny ringbuffer med de forskellige elementer
     * 
     */
    RingBuffer();
    int buffersBehind;
    void begin();
    void writeSample(uint16_t input);
    uint16_t readSample();
    uint16_t* getPayloadPointer();
    void increment();

    void writePayload(uint16_t* input);
    void readPayload(uint16_t* input);
};






class PlaybackBuffer{

    uint8_t storeIndex = 0;
    uint8_t playIndex = 0;  

    public:
    /***For at timeren kan fungere***/
    uint16_t SamplesPlayed = 0;
    uint16_t ChangePeriod;
    bool ChangePeriodFlag;
    AVG_calculator payloadPeriodAvg = NULL;//Hehee
    RingBuffer buffer;
    PlaybackBuffer();
    void begin();
    void StorePayLoad(uint16_t* input);
    void StorePayLoad_Fast();
    uint16_t GetSample();

    uint16_t flag = 0;

};

extern PlaybackBuffer playbackBuffer;


