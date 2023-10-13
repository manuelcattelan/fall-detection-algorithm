#include "hardware.h"

enum settingStatus detectionStatus = DEFAULT_DETECTION_SETTING;
enum settingStatus notificationStatus = DEFAULT_NOTIFICATION_SETTING;

int joystickData[JOYSTICK_AXIS] = {};
int accelerometerData[ACCELEROMETER_AXIS] = {};

void initHardware(){
    /* halting wtd and disabling master interrupts */
    WDT_A_holdTimer();
    Interrupt_disableMaster();
    /* sets the core voltage level to VCORE1 */
    PCM_setCoreVoltageLevel(PCM_VCORE1);
    /* sets 2 flash wait states for Flash bank 0 and 1 */
    FlashCtl_setWaitState(FLASH_BANK0, 2);
    FlashCtl_setWaitState(FLASH_BANK1, 2);
    /* initializes clock signal */
    CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_48);
    CS_initClockSignal(CS_MCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);
    CS_initClockSignal(CS_HSMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);
    CS_initClockSignal(CS_SMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);
    CS_initClockSignal(CS_ACLK, CS_REFOCLK_SELECT, CS_CLOCK_DIVIDER_1);
}
void initAdc(){
    /* configures accelerometer Pin 4.0 (x-axis), Pin 4.2 (y-axis) and Pin 6.1 (z-axis) as adc input */
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P4, GPIO_PIN0, GPIO_TERTIARY_MODULE_FUNCTION);
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P4, GPIO_PIN2, GPIO_TERTIARY_MODULE_FUNCTION);
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P6, GPIO_PIN1, GPIO_TERTIARY_MODULE_FUNCTION);
    /* configures joystick Pin 6.0 (x-axis) and Pin 4.4 (y-axis) as adc input */
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P6, GPIO_PIN0, GPIO_TERTIARY_MODULE_FUNCTION);
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P4, GPIO_PIN4, GPIO_TERTIARY_MODULE_FUNCTION);
    /* enabling and configuring adc */
    ADC14_enableModule();
    ADC14_initModule(ADC_CLOCKSOURCE_ADCOSC, ADC_PREDIVIDER_64, ADC_DIVIDER_8, 0);
    /* adc memory configuration for pheripherals with repeat */
    ADC14_configureMultiSequenceMode(ADC_MEM0, ADC_MEM4, true);
    /* accelerometer configuration with x-axis (A14) on MEM0, y-axis (A13) on MEM1 and z-axis (A11) on MEM2 */
    ADC14_configureConversionMemory(ADC_MEM0, ADC_VREFPOS_AVCC_VREFNEG_VSS, ADC_INPUT_A14, ADC_NONDIFFERENTIAL_INPUTS);
    ADC14_configureConversionMemory(ADC_MEM1, ADC_VREFPOS_AVCC_VREFNEG_VSS, ADC_INPUT_A13, ADC_NONDIFFERENTIAL_INPUTS);
    ADC14_configureConversionMemory(ADC_MEM2, ADC_VREFPOS_AVCC_VREFNEG_VSS, ADC_INPUT_A11, ADC_NONDIFFERENTIAL_INPUTS);
    /* joystick configuration with x-axis (A15) on MEM1 and y-axix (A9) on MEM2 */
    ADC14_configureConversionMemory(ADC_MEM3, ADC_VREFPOS_AVCC_VREFNEG_VSS, ADC_INPUT_A15, ADC_NONDIFFERENTIAL_INPUTS);
    ADC14_configureConversionMemory(ADC_MEM4, ADC_VREFPOS_AVCC_VREFNEG_VSS, ADC_INPUT_A9, ADC_NONDIFFERENTIAL_INPUTS);
    /* enable interrupts when a conversion on channel 4 (ADC_MEM4 for joystick) or channel 2 (ADC_MEM2 for accelerometer) is complete */
    ADC14_enableInterrupt(ADC_INT2);
    ADC14_enableInterrupt(ADC_INT4);
    /* enable adc interrupts */
    Interrupt_enableInterrupt(INT_ADC14);
    Interrupt_enableMaster();
    /* enable sample timer to make automatic interations */
    ADC14_enableSampleTimer(ADC_AUTOMATIC_ITERATION);
    /* enable and trigger conversion */
    ADC14_enableConversion();
    ADC14_toggleConversionTrigger();
}
void initSystem(){
    /* initializes hardware, display, timer and analog to digital converter */
    initHardware();
    initDisplay();
    initTimer();
    initAdc();
}
void ADC14_IRQHandler(void){
    uint64_t status = ADC14_getEnabledInterruptStatus();
    ADC14_clearInterruptFlag(status);
    /* check which pin generated the interrupt */
    if (status & ADC_INT2){
        /*
         * accelerometer conversion finished
         */
        if (detectionStatus == ON && canClassify == true)
            doProgramState();
    }
    if (status & ADC_INT4){
        /*
         * joystick conversion finished
         */
        int i;
        /* store joystick x and y conversion */
        joystickData[0] = ADC14_getResult(ADC_MEM3);
        joystickData[1] = ADC14_getResult(ADC_MEM4);
        switch(getCurrentPage()){
            /* if current page is status page */
            case STATUS:
                /* check for vertical movements only and move pointer accordingly */
                if (joystickData[1] > JOYSTICK_MAX_THRESHOLD){
                    movePointerUp();
                    for (i = 0; i < 400000; i++);
                } else if (joystickData[1] < JOYSTICK_MIN_THRESHOLD){
                    movePointerDown();
                    for (i = 0; i < 400000; i++);
                }
                break;
            /* if current page is detection settings */
            case DETECTION:
                /* check for horizontal movements only and move accordingly */
                if (joystickData[0] > JOYSTICK_MAX_THRESHOLD){
                    movePointerRight();
                    for (i = 0; i < 400000; i++);
                } else if (joystickData[0] < JOYSTICK_MIN_THRESHOLD){
                    movePointerLeft();
                    for (i = 0; i < 400000; i++);
                }
                break;
            /* if current page is notification settings */
            case NOTIFICATION:
                if (detectionStatus == ON){
                    /* if fall detection is on check for horizontal movements only and move accordingly (can't turn on notifications when fall detection is off) */
                    if (joystickData[0] > JOYSTICK_MAX_THRESHOLD){
                        movePointerRight();
                        for (i = 0; i < 400000; i++);
                    } else if (joystickData[0] < JOYSTICK_MIN_THRESHOLD){
                        movePointerLeft();
                        for (i = 0; i < 400000; i++);
                    }
                }
                break;
            /* if current page is timer settings */
            case TIMER:
                /* checks for vertical movements only and increase/decrease timer value accordingly, then displays it on screen */
                if (joystickData[1] > JOYSTICK_MAX_THRESHOLD){
                    increaseTimerValue();
                    updateTimerValue();
                    for (i = 0; i < 400000; i++);
                }
                else if (joystickData[1] < JOYSTICK_MIN_THRESHOLD){
                    decreaseTimerValue();
                    updateTimerValue();
                    for (i = 0; i < 400000; i++);
                }
                break;
            default:
                break;
        }
    }
    if (!(P5IN & GPIO_PIN1)){
        /*
         * upper button pressed (back)
         */
        int i;
        /* if page is detection/notification settings or page is warning page with notifications off the back button displays the status page */
        if (getCurrentPage() == DETECTION || getCurrentPage() == NOTIFICATION || (getCurrentPage() == WARNING && notificationStatus == OFF)){
            /* re-enables classification after a possible fall */
            canClassify = true;
            clearDisplay();
            displayStatusPage();
            for (i = 0; i < 400000; i++);
        }
        /* if page is timer settings the back button restores the timer value before the modifications and displays the status page */
        else if (getCurrentPage() == TIMER){
            tempTimerValue = currentTimerValue;
            clearDisplay();
            displayStatusPage();
            for (i = 0; i < 400000; i++);
        }
    }
    if (!(P3IN & GPIO_PIN5)){
        /*
         * lower button pressed (select)
         */
        int i;
        switch(getCurrentPage()){
            /* if current page is status page */
            case STATUS:
                /* checks pointer vertical position to display the right settings page */
                switch(getPointerY()){
                    case DETECTION_ROW:
                        clearDisplay();
                        displayDetectionSettings();
                        for (i = 0; i < 400000; i++);
                        break;
                    case NOTIFICATION_ROW:
                        clearDisplay();
                        displayNotificationSettings();
                        for (i = 0; i < 400000; i++);
                        break;
                    case TIMER_ROW:
                        clearDisplay();
                        displayTimerSettings();
                        for (i = 0; i < 400000; i++);
                        break;
                    default:
                        break;
                }
                break;
            /* if current page is notification settings */
            case NOTIFICATION:
                /* checks pointer horizontal position to either turn ON or OFF the currently displayed setting */
                switch(getPointerX()){
                    case ON_X:
                        notificationStatus = ON;
                        clearDisplay();
                        displayStatusPage();
                        for (i = 0; i < 400000; i++);
                        break;
                    case OFF_X:
                        notificationStatus = OFF;
                        clearDisplay();
                        displayStatusPage();
                        for (i = 0; i < 400000; i++);
                        break;
                    default:
                        break;
                }
                break;
            /* if current page is detection settings */
            case DETECTION:
                /* checks pointer horizontal position to either turn ON or OFF the currently displayed setting */
                switch(getPointerX()){
                    case ON_X:
                        detectionStatus = ON;
                        clearDisplay();
                        displayStatusPage();
                        for (i = 0; i < 400000; i++);
                        break;
                    case OFF_X:
                        detectionStatus = OFF;
                        notificationStatus = OFF;
                        clearDisplay();
                        displayStatusPage();
                        for (i = 0; i < 400000; i++);
                        break;
                    default:
                        break;
                }
                break;
            /* if current page is timer settings */
            case TIMER:
                /* updates the timer value and the countdown value to the temporary timer value(being modified in the timer settings page) */
                currentTimerValue = tempTimerValue;
                countdownValue = tempTimerValue;
                clearDisplay();
                displayStatusPage();
                for (i = 0; i < 400000; i++);
                break;
            /* if current page is warning page */
            case WARNING:
                /* if the fall notification is ON and you can still stop the timer, stop it and reset the timer count and countdown value, then display the status page without sending a notification */
                if (notificationStatus == ON && canStopTimer == true){
                    Timer_A_stopTimer(TIMER_A0_BASE);
                    Timer_A_clearTimer(TIMER_A0_BASE);
                    countdownValue = currentTimerValue;
                    canClassify = true;
                    clearDisplay();
                    displayStatusPage();
                    for (i = 0; i < 400000; i++);
                }
            default:
                break;
        }
    }
}
