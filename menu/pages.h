#ifndef MENU_PAGES_H_
#define MENU_PAGES_H_

#include <stdio.h>
#include <string.h>
#include "hardware/hardware.h"
#include "timer/timer.h"

#define DEFAULT_PAGE           STATUS   //default value for currentPage at startup

#define MAX_STRING_LENGTH          25   //string length for longer text strings
#define MIN_STRING_LENGTH           5   //string length for shorter text strings

#define ROW_NUMBER                  3   //number of status rows in dashboard page

#define TITLE_X                    64   //x position for titles
#define TITLE_Y                    20   //y position for titles

#define STATUS_DESCRIPTION_X       15   //x position for status page descriptive text
#define STATUS_VALUE_X            100   //x position for status page on/off/timer values
#define STATUS_Y                   45   //y position for status page rows

#define SETTINGS_DESCRIPTION_X     64   //x position for setting name in detection/notification settings
#define SETTINGS_DESCRIPTION_Y     60   //y position for setting name in detection/notification settings

#define TIMER_X                    64   //x position for timer value in timer settings
#define TIMER_Y                    70   //y position for timer value in timer settings

#define WARNING_X                  64   //x position for warning text in warning page
#define WARNING_Y                  20   //y position for warning text in warning page

#define DISTANCE_BETWEEN_ROWS      20   //y offset between rows

#define SELECT_BUTTON_X            85   //x position for select button number S1
#define BACK_BUTTON_X               5   //x position for back button number S2
#define BUTTONS_Y                 115   //y position for back/select buttons
#define BUTTONS_X_OFFSET           20   //x offset to write description of button next to number


/* variable to keep track of currently displayed page */
enum page {STATUS, DETECTION, NOTIFICATION, TIMER, WARNING};
extern enum page currentPage;

/* pages structures */
typedef struct dashboard{
    char title[MAX_STRING_LENGTH];                        //page title
    char rowDescription[ROW_NUMBER][MAX_STRING_LENGTH];   //options description
    char rowStatus[ROW_NUMBER][MIN_STRING_LENGTH];        //options status
    char selectButtonNumber[MIN_STRING_LENGTH];           //number for select button
    char selectButtonText[MIN_STRING_LENGTH];             //text for select button
}dashboard;
typedef struct onOffSettings{
    char title[MAX_STRING_LENGTH];                        //page title
    char setting[MAX_STRING_LENGTH];                      //setting being modified (detection/notification)
    char optionsRow[MAX_STRING_LENGTH];                   //on/off text
    char backButtonNumber[MIN_STRING_LENGTH];             //number for back button
    char backButtonText[MIN_STRING_LENGTH];               //text for back button
    char selectButtonNumber[MIN_STRING_LENGTH];           //number for select button
    char selectButtonText[MIN_STRING_LENGTH];             //text for back button
}onOffSettings;
/* settings page structure for timer changes */
typedef struct timerSettings{
    char title[MAX_STRING_LENGTH];                        //setting being modified (timer)
    char increaseRow[MAX_STRING_LENGTH];                  //increase text
    char decreaseRow[MAX_STRING_LENGTH];                  //decrease text
    char timerValue[MIN_STRING_LENGTH];                   //timer value being modified
    char backButtonNumber[MIN_STRING_LENGTH];             //number for back button
    char backButtonText[MIN_STRING_LENGTH];               //text for back button
    char selectButtonNumber[MIN_STRING_LENGTH];           //number for select button
    char selectButtonText[MIN_STRING_LENGTH];             //text for back button
}timerSettings;
typedef struct warning{
    char warningMessage[MAX_STRING_LENGTH];               //warning message after fall
    char countdownMessage[MAX_STRING_LENGTH];             //message showing timer countdown
    char noNotificationMessage[MAX_STRING_LENGTH];        //text if notification is off
    char dontSendButton[MAX_STRING_LENGTH];               //button for stopping notification timer
    char backButtonNumber[MIN_STRING_LENGTH];             //number for back button
    char backButtonText[MIN_STRING_LENGTH];               //text for back button
    char selectButtonNumber[MIN_STRING_LENGTH];           //number for select button
    char selectButtonText[MIN_STRING_LENGTH];             //text for select button
}warning;

/* menu pages creation */
extern dashboard statusPage;
extern onOffSettings detectionPage;
extern onOffSettings notificationPage;
extern timerSettings timerPage;
extern warning warningPage;

/* getter/setter functions for currently displayed page */
extern void setCurrentPage(enum page);
extern enum page getCurrentPage();

/* ad-hoc functions to display pages on lcd screen */
extern void displayStatusPage();
extern void displayDetectionSettings();
extern void displayNotificationSettings();
extern void displayTimerSettings();
extern void displayWarningPage();

/* updates timer value when moving joystick */
extern void updateTimerValue();
/* updates countdown value every second */
extern void updateCountdownValue();
/* displays a "message sent" text when timer reaches 0 and removes don't send button */
extern void updateAlarmMessage();

#endif /* MENU_PAGES_H_ */
