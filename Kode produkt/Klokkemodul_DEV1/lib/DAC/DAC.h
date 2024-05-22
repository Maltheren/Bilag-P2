#include<Arduino.h>
namespace DAC{
    void setup_10bit();
    void setup_8bit();
    void write_8bit(uint8_t input);
    void write_10bit(uint16_t input);
}