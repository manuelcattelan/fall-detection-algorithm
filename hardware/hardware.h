#ifndef HARDWARE_HARDWARE_H_
#define HARDWARE_HARDWARE_H_

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "classification/classification.h"
#include "display/lcd.h"
#include "menu/pages.h"
#include "menu/pointer.h"

#define DEFAULT_DETECTION_SETTING       ON  //default status for detection setting
#define DEFAULT_NOTIFICATION_SETTING    ON  //default status for notification setting

#define JOYSTICK_MAX_THRESHOLD       15000  //max x/y value to reach to go right/up
#define JOYSTICK_MIN_THRESHOLD        1000  //min x/y value to reach to go left/down

#define JOYSTICK_AXIS                    2  //number of joystick axis for joystick data
#define ACCELEROMETER_AXIS               3  //number of accelerometer axis for accelerometer data

/* variables to keep track of current fall detection and notification settings */
enum settingStatus {OFF, ON};
extern enum settingStatus detectionStatus;
extern enum settingStatus notificationStatus;

/* x/y joystick position array */
extern int joystickData[JOYSTICK_AXIS];
/* x/y/z accelerometer reading array */
extern int accelerometerData[ACCELEROMETER_AXIS];

/* initializes clock signal, disables watchdog timer */
extern void initHardware();
/* initializes analog to digital converter for accelerometer/joystick conversions */
extern void initAdc();
/* groups together every hardware initialization */
extern void initSystem();
/* interrupt handler for accelerometer/joystick conversions and buttons */
extern void ADC14_IRQHandler(void);

#endif /* HARDWARE_HARDWARE_H_ */
