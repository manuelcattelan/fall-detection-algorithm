#include "lcd.h"

void initDisplay(){
    /* initializes display */
    Crystalfontz128x128_Init();
    /* sets default screen orientation */
    Crystalfontz128x128_SetOrientation(LCD_ORIENTATION_UP);
    /* initializes graphics context structs */
    Graphics_initContext(&btContext, &g_sCrystalfontz128x128, &g_sCrystalfontz128x128_funcs);
    Graphics_initContext(&rtContext, &g_sCrystalfontz128x128, &g_sCrystalfontz128x128_funcs);
    Graphics_initContext(&titleContext, &g_sCrystalfontz128x128, &g_sCrystalfontz128x128_funcs);
    /* sets foreground and background colors */
    Graphics_setForegroundColor(&btContext, GRAPHICS_COLOR_BLACK);
    Graphics_setBackgroundColor(&btContext, GRAPHICS_COLOR_WHITE);
    Graphics_setForegroundColor(&rtContext, GRAPHICS_COLOR_RED);
    Graphics_setBackgroundColor(&rtContext, GRAPHICS_COLOR_WHITE);
    Graphics_setForegroundColor(&titleContext, GRAPHICS_COLOR_RED);
    Graphics_setBackgroundColor(&titleContext, GRAPHICS_COLOR_WHITE);
    /* sets contexts fonts */
    GrContextFontSet(&btContext, &g_sFontFixed6x8);
    GrContextFontSet(&rtContext, &g_sFontFixed6x8);
    GrContextFontSet(&titleContext, &g_sFontCmss12);
    /* wipes display content */
    Graphics_clearDisplay(&btContext);
    Graphics_clearDisplay(&rtContext);
    Graphics_clearDisplay(&titleContext);
}
void clearDisplay(){
    /* wipes display content for every context */
    Graphics_clearDisplay(&btContext);
    Graphics_clearDisplay(&rtContext);
    Graphics_clearDisplay(&titleContext);
}
