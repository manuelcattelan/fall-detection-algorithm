#include "pointer.h"

pointer puntatore = {
                     ">",
                     STATUS_PAGE_X,
                     STATUS_PAGE_Y
};

void displayPointer(){
    /* display pointer on current x and y coordinates */
    Graphics_drawString(&btContext, (int8_t *) puntatore.symbol , AUTO_STRING_LENGTH, puntatore.xPos, puntatore.yPos, OPAQUE_TEXT);
}
void clearPointer(){
    /* display blank space on current x and y pointer coordinates */
    Graphics_drawString(&btContext, (int8_t *) " " , AUTO_STRING_LENGTH, puntatore.xPos, puntatore.yPos, OPAQUE_TEXT);
}
void setPointerPosition(int newX, int newY){
    /* set function arguments as new pointer coordinates */
    puntatore.xPos = newX;
    puntatore.yPos = newY;
}
int getPointerX(){
    return puntatore.xPos;
}
int getPointerY(){
    return puntatore.yPos;
}
void movePointerUp(){
    /* remove pointer from current position */
    clearPointer();
    /* update pointer y position based on its current y position */
    switch(puntatore.yPos){
        case DETECTION_ROW:
            break;
        case NOTIFICATION_ROW:
            setPointerPosition(STATUS_PAGE_X, DETECTION_ROW);
            break;
        case TIMER_ROW:
            setPointerPosition(STATUS_PAGE_X, NOTIFICATION_ROW);
            break;
        default:
            break;
    }
    /* display pointer on new position */
    displayPointer();
}
void movePointerDown(){
    /* remove pointer from current position */
    clearPointer();
    /* update pointer y position based on its current y position */
    switch(puntatore.yPos){
        case DETECTION_ROW:
            setPointerPosition(STATUS_PAGE_X, NOTIFICATION_ROW);
            break;
        case NOTIFICATION_ROW:
            setPointerPosition(STATUS_PAGE_X, TIMER_ROW);
            break;
        case TIMER_ROW:
            break;
        default:
            break;
    }
    /* display pointer on new position */
    displayPointer();
}
void movePointerRight(){
    /* remove pointer from current position */
    clearPointer();
    /* update pointer x position based on its current x position */
    switch(puntatore.xPos){
        case ON_X:
            setPointerPosition(OFF_X, ON_OFF_Y);
            break;
        case OFF_X:
            break;
        default:
            break;
    }
    /* display pointer on new position */
    displayPointer();
}
void movePointerLeft(){
    /* remove pointer from current position */
    clearPointer();
    /* update pointer x position based on its current x position */
    switch(puntatore.xPos){
        case ON_X:
            break;
        case OFF_X:
            setPointerPosition(ON_X, ON_OFF_Y);
            break;
        default:
            break;
    }
    /* display pointer on new position */
    displayPointer();
}
