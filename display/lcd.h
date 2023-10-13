#ifndef DISPLAY_LCD_H_
#define DISPLAY_LCD_H_

#include "Crystalfontz128x128_ST7735.h"

/* black text on white background context (used for normal text) */
Graphics_Context btContext;
/* red text on white background context (used for status indicators and buttons) */
Graphics_Context rtContext;
/* red text on white background context with cmss font (used for page titles) */
Graphics_Context titleContext;

/* initializes display orientation, colors, fonts */
extern void initDisplay();
/* wipes all display content from display contexts */
extern void clearDisplay();

#endif /* DISPLAY_LCD_H_ */
