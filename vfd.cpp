#include "vfd.h"
#include "mbed.h"

Vfd::Vfd(PinName _cathode_pin, PinName a, PinName b, PinName c, PinName d, PinName e, PinName f, PinName g, PinName h, PinName dp):
    cathode_pin(_cathode_pin), anode_pins(a, b, c, d, e, f, g, h, dp) {}

void Vfd::display(const DisplayNumber* pdn) {
    cathode_pin = 1;
    anode_pins.write((int)VFD_LIGHT_MAP[pdn->number]);
}

void Vfd::clear() {
    anode_pins.write(0);
    cathode_pin = 0;
}
