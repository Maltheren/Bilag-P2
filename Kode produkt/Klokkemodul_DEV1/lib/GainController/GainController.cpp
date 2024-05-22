#include<GainController.h>
GainController gainController;





void GainController::begin(){
    gainPot.reset();
    gainPot.setPos(1);
}

//Styrer opdateringen af Gain potmeteret
void GainController::Update(uint16_t Sample){
    ticksSince++;
    if(ticksSinceChange <= ChangePeriod){
        ticksSinceChange++;
    }

    if(Sample < GreenLine){
        ticksSince = 0;
    }
    if(Sample < RedLine){
        if(ticksSinceChange > ChangePeriod){
            gainPot.wipeDown();
            ticksSinceChange = 0;
        }
    }
    if(ticksSince > TickThreshold){
        if(ticksSinceChange > ChangePeriod){
            gainPot.wipeUp();
            ticksSinceChange = 0;
        }
    }
}

