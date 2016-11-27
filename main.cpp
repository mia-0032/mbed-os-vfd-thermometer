#include "mbed.h"
#include "vfd.h"

//for debug
DigitalOut led1(LED1, 0);
DigitalOut led2(LED2, 0);
DigitalOut led3(LED3, 0);
DigitalOut led4(LED4, 0);
Serial pc(USBTX, USBRX);

// for VFD
const uint32_t VFD_REFRESH_WAIT_MS = 2;
const uint8_t VFD_NUM = 4;
Vfd vfds[VFD_NUM] = {
    Vfd(p14, p18, p19, p20, p21, p22, p23, p24, p25, p26),
    Vfd(p15, p18, p19, p20, p21, p22, p23, p24, p25, p26),
    Vfd(p16, p18, p19, p20, p21, p22, p23, p24, p25, p26),
    Vfd(p17, p18, p19, p20, p21, p22, p23, p24, p25, p26)
};
int display_number = 1234;

void vfd_display_numbers(void const *args)
{
    uint8_t ones_place, tens_place, hundreds_place, thousands_place;
    led4 = !led4;

    ones_place = 17;
    tens_place = (uint8_t)(display_number % 10);
    thousands_place = (uint8_t)(display_number / 100);
    hundreds_place = (uint8_t)((display_number - thousands_place * 100 - tens_place) / 10);

    DisplayNumber displayNumbers[] = {
        {ones_place, false},
        {tens_place, false},
        {hundreds_place, true},
        {thousands_place, false}
    };

    for(int i=0; i < VFD_NUM; i++) {
        vfds[i].display(&displayNumbers[i]);
        Thread::wait(VFD_REFRESH_WAIT_MS);
        vfds[i].clear();
    }
}

// main() runs in its own thread in the OS
// (note the calls to Thread::wait below for delays)
int main() {
    // start vfd
    RtosTimer vfd_timer(vfd_display_numbers, osTimerPeriodic, NULL);
    vfd_timer.start(16); //60fps

    while (true) {
        led1 = !led1;
        Thread::wait(500);
        display_number++;
    }
}
