#include<Arduino.h>
#include<RF24.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <PlaybackHandler.h>



#define RADIO_CE 9
#define RADIO_CSN 8

extern const byte address[6]; //addresse med null termination
extern RF24 radio;




/**
 * @brief Nigger
 * 
 */
void SetupRadio(void (*input)()); 
