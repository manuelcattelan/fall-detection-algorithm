#include "hardware/hardware.h"
#include "menu/pages.h"
/*
 * main function
 */
void main(void)
{
    initSystem();
    displayStatusPage();
    while(1){
        PCM_gotoLPM0();
    }
}
