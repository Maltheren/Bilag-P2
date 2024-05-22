#include<Arduino.h>
#include <X9C104.h>

#define POT_UD 2 //Hardwaredefineret.
#define POT_INC 3

#define RedLine 10 //En værdi der skal holdes under
#define GreenLine 100 //En værdi som signalet minimum skal være
#define TickThreshold 30000 //Hvor lang signalet må være ude af den grønne zon
#define ChangePeriod 2000 //Hvor ofte systemet på skifte på forstærkningen i Ticks


/**
 * @brief Blok til at bestemme hvor mange gange forstærkning der skal sættes på 
 * 
 */
class GainController{ 
    X9C104 gainPot = X9C104(POT_INC, POT_UD);
    uint16_t ticksSince = 0;
    uint16_t ticksSinceChange = 0;
    public:
    void begin();

    void Update(uint16_t Sample);

};



extern GainController gainController;