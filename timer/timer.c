#include "timer.h"

const Timer_A_ContinuousModeConfig continuousModeConfig =
{
    TIMER_A_CLOCKSOURCE_ACLK,           // ACLK Clock Source
    TIMER_A_CLOCKSOURCE_DIVIDER_1,      // ACLK/1 = 65.536khz
    TIMER_A_TAIE_INTERRUPT_ENABLE,      // Enable Overflow ISR
    TIMER_A_DO_CLEAR                    // Clear Counter
};

int8_t currentTimerValue = DEFAULT_TIMER_VALUE;
int8_t tempTimerValue = DEFAULT_TIMER_VALUE;
int8_t countdownValue = DEFAULT_TIMER_VALUE;

bool canStopTimer = true;

void initTimer(){
    /* starting and enabling ACLK (128KHz) */
    CS_setReferenceOscillatorFrequency(CS_REFO_128KHZ);
    /* using divider_2 to get a clock frequency of 64KHz */
    CS_initClockSignal(CS_ACLK, CS_REFOCLK_SELECT, CS_CLOCK_DIVIDER_2);
    /* configuring timer continuous mode with config file */
    Timer_A_configureContinuousMode(TIMER_A0_BASE, &continuousModeConfig);
    /* enabling interrupts and going to sleep */
    Interrupt_enableInterrupt(INT_TA0_N);
    /* enabling master interrupts */
    Interrupt_enableMaster();
}
void increaseTimerValue(){
    /* increasing timer of temporary timer value for every joystick interrupt on y axis while on timer settings page */
    if (tempTimerValue < 100)
        tempTimerValue ++;
}
void decreaseTimerValue(){
    /* decreasing timer of temporary timer value for every joystick interrupt on y axis while on timer settings page */
    if (tempTimerValue > 1)
        tempTimerValue --;
}
void TA0_N_IRQHandler(void)
{
    Timer_A_clearInterruptFlag(TIMER_A0_BASE);
    /* decrease the countdown value for every timer interrupt (every ~1s) */
    countdownValue --;
    /* while timervalue is greater than 0 just update the display text */
    if (countdownValue > 0){
        updateCountdownValue();
    } else if (countdownValue == 0){
        /* send message in telegram */
        updateAlarmMessage();
        canStopTimer = false;
    } else if (countdownValue == -(TIME_AFTER_MESSAGE_SENT)){
        /* stop and reset timer and countdown value after TIME_AFTER_MESSAGE_SENT has passed from alert sent */
        /* set canClassify and canStopTimer to true  for next classifications */
        Timer_A_stopTimer(TIMER_A0_BASE);
        Timer_A_clearTimer(TIMER_A0_BASE);
        countdownValue = currentTimerValue;
        clearDisplay();
        displayStatusPage();
        canClassify = true;
        canStopTimer = true;
    }
}

