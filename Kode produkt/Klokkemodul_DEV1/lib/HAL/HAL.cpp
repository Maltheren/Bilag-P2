#include<HAL.h>


RF24 radio(RADIO_CE, RADIO_CSN);
const byte address[6] = "32028";
void SetupRadio(){

    radio.begin();
    SPI.setClockDivider(SPI_CLOCK_DIV2);
    radio.setDataRate(RF24_2MBPS);
    radio.setPayloadSize(32); ///fixed payload
    radio.setAutoAck(1); //står automatiske acks til
    radio.enableAckPayload();
    radio.openWritingPipe(address); //ting der lidt bare er nødvendige
    radio.stopListening();
}
