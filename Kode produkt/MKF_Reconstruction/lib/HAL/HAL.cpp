#include<HAL.h>





const byte address[6] = "32028"; //addresse med null termination
RF24 radio(RADIO_CE, RADIO_CSN);



void SetupRadio(void (*input)()){
    radio.begin();
    //set the address
    radio.setDataRate(RF24_2MBPS);
    radio.openReadingPipe(0, address);
    radio.setPayloadSize(32);
    radio.maskIRQ(true, true, false);
    radio.setAutoAck(1); //står automatiske acks til
    radio.enableAckPayload();
    radio.startListening();
    attachInterrupt(digitalPinToInterrupt(2) ,input ,FALLING );
}

