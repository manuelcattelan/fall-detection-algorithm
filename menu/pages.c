#include "pages.h"

enum page currentPage = DEFAULT_PAGE;

/* menu pages string definition */
dashboard statusPage = {
                           .title = "STATUS PAGE",
                           .rowDescription = {
                                              "Detection_____",
                                              "Notification__",
                                              "Timer [s]_____"
                           },
                           .selectButtonNumber = "S2-",
                           .selectButtonText = "sel."
};
onOffSettings detectionPage = {
                               .title = "SETTINGS",
                               .setting = "fall detection",
                               .optionsRow = "ON      OFF",
                               .backButtonNumber = "S1-",
                               .backButtonText = "back",
                               .selectButtonNumber = "S2-",
                               .selectButtonText = "sel."
};
onOffSettings notificationPage = {
                               .title = "SETTINGS",
                               .setting = "fall notification",
                               .optionsRow = "ON      OFF",
                               .backButtonNumber = "S1-",
                               .backButtonText = "back",
                               .selectButtonNumber = "S2-",
                               .selectButtonText = "sel."
};
timerSettings timerPage = {
                           .title = "SETTINGS",
                           .increaseRow = "increase",
                           .decreaseRow = "decrease",
                           .backButtonNumber = "S1-",
                           .backButtonText = "back",
                           .selectButtonNumber = "S2-",
                           .selectButtonText = "sel."
};
warning warningPage = {
                       .warningMessage = "FALL DETECTED!",
                       .noNotificationMessage = "Notifications OFF!",
                       .dontSendButton = "don't send",
                       .backButtonNumber = "S1-",
                       .backButtonText = "back",
                       .selectButtonNumber = "S2-",
                       .selectButtonText = "sel."
};
void setCurrentPage(enum page displayedPage){
    currentPage = displayedPage;
}
enum page getCurrentPage(){
    return currentPage;
}
void displayStatusPage(){
    int i;
    /* display status page title */
    Graphics_drawStringCentered(&titleContext, (int8_t *) statusPage.title, AUTO_STRING_LENGTH, TITLE_X, TITLE_Y, OPAQUE_TEXT);
    /* display status page settings description */
    for (i = 0; i < ROW_NUMBER; i ++){
        Graphics_drawString(&btContext, (int8_t *) statusPage.rowDescription[i], AUTO_STRING_LENGTH, STATUS_DESCRIPTION_X, STATUS_Y + (i * DISTANCE_BETWEEN_ROWS), OPAQUE_TEXT);
    }
    /* check settings status and update text on status page */
    if (detectionStatus == ON)
        strcpy(statusPage.rowStatus[0], " ON");
    else
        strcpy(statusPage.rowStatus[0], "OFF");
    if (notificationStatus == ON)
        strcpy(statusPage.rowStatus[1], " ON");
    else
        strcpy(statusPage.rowStatus[1], "OFF");
    sprintf(statusPage.rowStatus[2], "%3d", currentTimerValue);
    /* display status page settings status */
    for (i = 0; i < ROW_NUMBER; i ++){
        Graphics_drawString(&rtContext, (int8_t *) statusPage.rowStatus[i], AUTO_STRING_LENGTH, STATUS_VALUE_X, STATUS_Y + (i * DISTANCE_BETWEEN_ROWS), OPAQUE_TEXT);
    }
    /* display select button */
    Graphics_drawString(&btContext, (int8_t *) statusPage.selectButtonNumber, AUTO_STRING_LENGTH, SELECT_BUTTON_X, BUTTONS_Y, OPAQUE_TEXT);
    Graphics_drawString(&rtContext, (int8_t *) statusPage.selectButtonText, AUTO_STRING_LENGTH, (SELECT_BUTTON_X + BUTTONS_X_OFFSET), BUTTONS_Y, OPAQUE_TEXT);
    /* set pointer to first option of status page and display it */
    setPointerPosition(STATUS_PAGE_X, STATUS_PAGE_Y);
    displayPointer();

    setCurrentPage(STATUS);
}
void displayDetectionSettings(){
    /* display detection settings title */
    Graphics_drawStringCentered(&titleContext, (int8_t *) detectionPage.title , AUTO_STRING_LENGTH, TITLE_X, TITLE_Y, OPAQUE_TEXT);
    /* display info about setting being modified */
    Graphics_drawStringCentered(&btContext, (int8_t *) detectionPage.setting , AUTO_STRING_LENGTH, SETTINGS_DESCRIPTION_X, SETTINGS_DESCRIPTION_Y, OPAQUE_TEXT);
    /* display on-off row */
    Graphics_drawStringCentered(&btContext, (int8_t *) detectionPage.optionsRow , AUTO_STRING_LENGTH, SETTINGS_DESCRIPTION_X, SETTINGS_DESCRIPTION_Y + DISTANCE_BETWEEN_ROWS, OPAQUE_TEXT);
    /* display back button */
    Graphics_drawString(&btContext, (int8_t *) detectionPage.backButtonNumber , AUTO_STRING_LENGTH, BACK_BUTTON_X, BUTTONS_Y, OPAQUE_TEXT);
    Graphics_drawString(&rtContext, (int8_t *) detectionPage.backButtonText , AUTO_STRING_LENGTH, BACK_BUTTON_X + BUTTONS_X_OFFSET, BUTTONS_Y, OPAQUE_TEXT);
    /* display select button */
    Graphics_drawString(&btContext, (int8_t *) detectionPage.selectButtonNumber , AUTO_STRING_LENGTH, SELECT_BUTTON_X, BUTTONS_Y, OPAQUE_TEXT);
    Graphics_drawString(&rtContext, (int8_t *) detectionPage.selectButtonText , AUTO_STRING_LENGTH, SELECT_BUTTON_X + BUTTONS_X_OFFSET, BUTTONS_Y, OPAQUE_TEXT);
    /* set pointer on setting status currently selected (on/off) */
    if (detectionStatus == ON)
        setPointerPosition(ON_X, ON_OFF_Y);
    else
        setPointerPosition(OFF_X, ON_OFF_Y);

    displayPointer();

    setCurrentPage(DETECTION);
}
void displayNotificationSettings(){
    /* display notification settings title */
    Graphics_drawStringCentered(&titleContext, (int8_t *) notificationPage.title , AUTO_STRING_LENGTH, TITLE_X, TITLE_Y, OPAQUE_TEXT);
    /* display info about setting being modified */
    Graphics_drawStringCentered(&btContext, (int8_t *) notificationPage.setting , AUTO_STRING_LENGTH, SETTINGS_DESCRIPTION_X, SETTINGS_DESCRIPTION_Y, OPAQUE_TEXT);
    /* display on-off row */
    Graphics_drawStringCentered(&btContext, (int8_t *) notificationPage.optionsRow , AUTO_STRING_LENGTH, SETTINGS_DESCRIPTION_X, SETTINGS_DESCRIPTION_Y + DISTANCE_BETWEEN_ROWS, OPAQUE_TEXT);
    /* display back button */
    Graphics_drawString(&btContext, (int8_t *) notificationPage.backButtonNumber , AUTO_STRING_LENGTH, BACK_BUTTON_X, BUTTONS_Y, OPAQUE_TEXT);
    Graphics_drawString(&rtContext, (int8_t *) notificationPage.backButtonText , AUTO_STRING_LENGTH, BACK_BUTTON_X + BUTTONS_X_OFFSET, BUTTONS_Y, OPAQUE_TEXT);
    /* display select button */
    Graphics_drawString(&btContext, (int8_t *) notificationPage.selectButtonNumber , AUTO_STRING_LENGTH, SELECT_BUTTON_X, BUTTONS_Y, OPAQUE_TEXT);
    Graphics_drawString(&rtContext, (int8_t *) notificationPage.selectButtonText , AUTO_STRING_LENGTH, SELECT_BUTTON_X + BUTTONS_X_OFFSET, BUTTONS_Y, OPAQUE_TEXT);
    /* set pointer on setting status currently selected (on/off) */
    if (notificationStatus == ON)
        setPointerPosition(ON_X, ON_OFF_Y);
    else
        setPointerPosition(OFF_X, ON_OFF_Y);

    displayPointer();

    setCurrentPage(NOTIFICATION);
}
void displayTimerSettings(){
    /* display timer settings title */
    Graphics_drawStringCentered(&titleContext, (int8_t *) timerPage.title , AUTO_STRING_LENGTH, TITLE_X, TITLE_Y, OPAQUE_TEXT);
    /* display "increase" row */
    Graphics_drawStringCentered(&btContext, (int8_t *) timerPage.increaseRow , AUTO_STRING_LENGTH, TIMER_X, TIMER_Y - DISTANCE_BETWEEN_ROWS, OPAQUE_TEXT);
    /* update timer value and displays it */
    sprintf(timerPage.timerValue, "%d", tempTimerValue);
    Graphics_drawStringCentered(&rtContext, (int8_t *) timerPage.timerValue , AUTO_STRING_LENGTH, TIMER_X, TIMER_Y, OPAQUE_TEXT);
    /* display "decrease" row */
    Graphics_drawStringCentered(&btContext, (int8_t *) timerPage.decreaseRow , AUTO_STRING_LENGTH, TIMER_X, TIMER_Y + DISTANCE_BETWEEN_ROWS, OPAQUE_TEXT);
    /* display back button */
    Graphics_drawString(&btContext, (int8_t *) notificationPage.backButtonNumber , AUTO_STRING_LENGTH, BACK_BUTTON_X, BUTTONS_Y, OPAQUE_TEXT);
    Graphics_drawString(&rtContext, (int8_t *) notificationPage.backButtonText , AUTO_STRING_LENGTH, BACK_BUTTON_X + BUTTONS_X_OFFSET, BUTTONS_Y, OPAQUE_TEXT);
    /* display select button */
    Graphics_drawString(&btContext, (int8_t *) notificationPage.selectButtonNumber , AUTO_STRING_LENGTH, SELECT_BUTTON_X, BUTTONS_Y, OPAQUE_TEXT);
    Graphics_drawString(&rtContext, (int8_t *) notificationPage.selectButtonText , AUTO_STRING_LENGTH, SELECT_BUTTON_X + BUTTONS_X_OFFSET, BUTTONS_Y, OPAQUE_TEXT);

    setCurrentPage(TIMER);
}
void displayWarningPage(){
    /* display warning message */
    Graphics_drawStringCentered(&titleContext, (int8_t *) warningPage.warningMessage, AUTO_STRING_LENGTH, WARNING_X, WARNING_Y + (0.5 * DISTANCE_BETWEEN_ROWS), OPAQUE_TEXT);
    /* if notifications are on display countdown message, don't send button, select button and start timer */
    if (notificationStatus == ON){
        sprintf(warningPage.countdownMessage, "alert in %d...",countdownValue);
        Graphics_drawStringCentered(&btContext, (int8_t *) warningPage.countdownMessage, AUTO_STRING_LENGTH, WARNING_X, WARNING_Y + (2 * DISTANCE_BETWEEN_ROWS), OPAQUE_TEXT);
        Graphics_drawStringCentered(&rtContext, (int8_t *) warningPage.dontSendButton, AUTO_STRING_LENGTH, WARNING_X, WARNING_Y + (3.5 * DISTANCE_BETWEEN_ROWS), OPAQUE_TEXT);
        Graphics_drawString(&btContext, (int8_t *) warningPage.selectButtonNumber , AUTO_STRING_LENGTH, SELECT_BUTTON_X, BUTTONS_Y, OPAQUE_TEXT);
        Graphics_drawString(&rtContext, (int8_t *) warningPage.selectButtonText , AUTO_STRING_LENGTH, SELECT_BUTTON_X + BUTTONS_X_OFFSET, BUTTONS_Y, OPAQUE_TEXT);

        setPointerPosition(DONT_SEND_X, DONT_SEND_Y);
        displayPointer();

        Timer_A_startCounter(TIMER_A0_BASE, TIMER_A_CONTINUOUS_MODE);
    } else {
        /* if notifications are off just display a "no notifications" message and back button without starting timer */
        Graphics_drawStringCentered(&btContext, (int8_t *) warningPage.noNotificationMessage, AUTO_STRING_LENGTH, WARNING_X, WARNING_Y + (2.5 * DISTANCE_BETWEEN_ROWS), OPAQUE_TEXT);
        Graphics_drawString(&btContext, (int8_t *) warningPage.backButtonNumber , AUTO_STRING_LENGTH, BACK_BUTTON_X, BUTTONS_Y, OPAQUE_TEXT);
        Graphics_drawString(&rtContext, (int8_t *) warningPage.backButtonText , AUTO_STRING_LENGTH, BACK_BUTTON_X + BUTTONS_X_OFFSET, BUTTONS_Y, OPAQUE_TEXT);
    }

    setCurrentPage(WARNING);
}
void updateTimerValue(){
    /* save temporary timer value into string */
    char string[MIN_STRING_LENGTH];
    sprintf(string, "%d", tempTimerValue);
    /* clear row where temp timer value is displayed */
    Graphics_drawStringCentered(&rtContext, (int8_t *) "   " , AUTO_STRING_LENGTH, TIMER_X, TIMER_Y, OPAQUE_TEXT);
    /* update row with new temp timer value */
    Graphics_drawStringCentered(&rtContext, (int8_t *) string , AUTO_STRING_LENGTH, TIMER_X, TIMER_Y, OPAQUE_TEXT);
}
void updateCountdownValue(){
    /* update countdown message on warning page */
    if (countdownValue == 99 || countdownValue == 9){
        Graphics_drawStringCentered(&btContext, (int8_t *) "                     ", AUTO_STRING_LENGTH, WARNING_X, WARNING_Y + (2 * DISTANCE_BETWEEN_ROWS), OPAQUE_TEXT);
    }
    sprintf(warningPage.countdownMessage, "alert in %d...",countdownValue);
    Graphics_drawStringCentered(&btContext, (int8_t *) warningPage.countdownMessage, AUTO_STRING_LENGTH, WARNING_X, WARNING_Y + (2 * DISTANCE_BETWEEN_ROWS), OPAQUE_TEXT);
}
void updateAlarmMessage(){
    /* when timer reaches 0 show a "message sent" button and remove the select button since you can't stop timer anymore */
    Graphics_drawStringCentered(&btContext, (int8_t *) "                     ", AUTO_STRING_LENGTH, WARNING_X, WARNING_Y + (2 * DISTANCE_BETWEEN_ROWS), OPAQUE_TEXT);
    Graphics_drawStringCentered(&btContext, (int8_t *) "Message sent!", AUTO_STRING_LENGTH, WARNING_X, WARNING_Y + (2.5 * DISTANCE_BETWEEN_ROWS), OPAQUE_TEXT);
    Graphics_drawStringCentered(&rtContext, (int8_t *) "             ", AUTO_STRING_LENGTH, WARNING_X, WARNING_Y + (3.5 * DISTANCE_BETWEEN_ROWS), OPAQUE_TEXT);
    Graphics_drawString(&btContext, (int8_t *) "        " , AUTO_STRING_LENGTH, SELECT_BUTTON_X, BUTTONS_Y, OPAQUE_TEXT);
}

