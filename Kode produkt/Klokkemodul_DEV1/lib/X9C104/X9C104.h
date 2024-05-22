#include <Arduino.h>
// 100 resistance steps, reset sets to 0, INC controls increments, UD controls up/down, pin1 = INC, pin2 = UD, bouth pins uses 5V.
class X9C104{
    int inc;
    int ud;
    int currentPos;
    public:
    //  @panam pin1 = inc  @panam pin2 = ud
    X9C104(int INC, int UD);
    void wipeUp();
    void wipeDown();
    void reset();
    void setPos(int pos);
};

