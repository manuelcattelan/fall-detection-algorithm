#ifndef MENU_POINTER_H_
#define MENU_POINTER_H_

#include "display/lcd.h"
#include "pages.h"

#define STATUS_PAGE_X        5  //default pointer x value for status page
#define STATUS_PAGE_Y       45  //default pointer y value for status page (points to detection row)

#define DETECTION_ROW       45  //y value for detection row
#define NOTIFICATION_ROW    65  //y value for notification row
#define TIMER_ROW           85  //y value for timer row

#define ON_OFF_Y            77  //y value for on/off row on settings pages
#define OFF_X               70  //x value for pointer on OFF
#define ON_X                22  //x value for pointer on ON

#define DONT_SEND_X         25  //x value for pointer on don't send button (warning page)
#define DONT_SEND_Y         88  //y value for pointer on don't send button (warning page)


/* pointer structure with symbol and x/y pos */
typedef struct pointer{
    char * symbol;
    int xPos;
    int yPos;
}pointer;

/* pointer declaration */
extern pointer puntatore;

/* displays pointer on lcd using x/y attibutes */
extern void displayPointer();
/* removes pointer in current position */
extern void clearPointer();
/* sets pointer coordinates to those given as arguments */
extern void setPointerPosition(int, int);
/* returns pointer x value */
extern int getPointerX();
/* returns pointer y value */
extern int getPointerY();
/* pointer movement functions */
extern void movePointerUp();
extern void movePointerDown();
extern void movePointerRight();
extern void movePointerLeft();

#endif /* MENU_POINTER_H_ */
