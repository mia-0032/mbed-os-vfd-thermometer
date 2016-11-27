#include "mbed.h"

const uint8_t VFD_LIGHT_MAP[] = {
    0b11111100, // 0
    0b01100000, // 1
    0b11011010, // 2
    0b11110010, // 3
    0b01100110, // 4
    0b10110110, // 5
    0b10111110, // 6
    0b11100000, // 7
    0b11111110, // 8
    0b11110110, // 9
    0b11101110, // A
    0b00111110, // B
    0b10011100, // C
    0b01111010, // D
    0b10011110, // E
    0b10001110, // F
    0b11001110, // P
    0b00101110  // h
};

struct DisplayNumber {
    uint8_t number;
    bool add_dot;
};

class Vfd {
public:
    Vfd(PinName _cathode_pin, PinName a, PinName b, PinName c, PinName d, PinName e, PinName f, PinName g, PinName h, PinName dp);
    void display(const DisplayNumber* pdn);
    void clear();

private:
    //Vfd(const Vfd&);
    //Vfd& operator=(const Vfd&);
    static const uint8_t ANODE_PINS_NUM = 9;
    static const uint8_t DOT_PIN_POS = 8;
    const DigitalOut cathode_pin;
    const BusOut anode_pins;
};
