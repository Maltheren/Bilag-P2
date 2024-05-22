/**
 * @file HAL.h
 * @author ESD210
 * @brief De froskellige hardwareperiferier
 * @version 0.1
 * @date 2024-04-09
 * 
 */

/*
 * Biblioteker der skal bruges uanset hvad
*/
#include<TurboAnalogRead.h>
#include<JobQueuer.h>
#include<GainController.h>
#include <RF24.h>
#include <SPI.h>
#include <nRF24L01.h>



#define debugPCHIGH(pin) PORTC  |=  (1<<pin) //@brief sætter PORTC pin HIGH
#define debugPCLOW(pin)  PORTC  &= ~(1<<pin) //@brief sætter PORTC pin LOW
#define PC_output DDRC = B11111110


#define UNO_DEV
#ifdef UNO_DEV //Hvis vi kører med de der sender modtager boards
/*
 * Pin definationer
*/
#define ADCChannel 0 //ADC'ens kanal
#define RADIO_CE 9
#define RADIO_CSN 8




/*
 * Specifikke Libraries kun for klokken
*/
#include <DAC.h>




#endif



#ifdef KLOKKE_DEV
#define ADCChannel 0

#endif



#ifdef KLOKKE_PRO
#define ADCChannel 0

#endif


/**
 ** Periferier der bruges uanset. globale variabler
*/

extern RF24 radio; //CE, CSN pins
extern const byte address[6]; //addresse med null termination


/**
 * @brief Sætter radioen op som transmitter ved 1 Mbps
 * @note slår'æ radio til!!
 */
void SetupRadio(); 
