#ifndef TIMER_TIMER_H_
#define TIMER_TIMER_H_

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "menu/pages.h"
#include "display/lcd.h"

#define DEFAULT_TIMER_VALUE        10  //default timer value
#define TIME_AFTER_MESSAGE_SENT     2  //time in [s] that passes after message is sent before going back to status page

/* config file used to configure timer mode and settings */
extern const Timer_A_ContinuousModeConfig continuousModeConfig;
/* variables used to keep track of timer settings and display countdown on warning page */
extern int8_t currentTimerValue;
extern int8_t tempTimerValue;
extern int8_t countdownValue;
/* variable used to know if message was already sent and if you can still stop the timer */
extern bool canStopTimer;

/* initializes timer */
extern void initTimer();
/* handle timer value in settings */
extern void increaseTimerValue();
extern void decreaseTimerValue();
/* timer interrupt handler on overflow */
extern void TA0_N_IRQHandler(void);

#endif /* TIMER_TIMER_H_ */
