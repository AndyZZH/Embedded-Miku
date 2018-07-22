// led.h
// Module to support 16 X 32 LED
// Translated from https://learn.adafruit.com/connecting-a-16x32-rgb-led-matrix-panel-to-a-raspberry-pi/experimental-python-code
// Refered : https://www.cs.sfu.ca/CourseCentral/433/bfraser/other/2015-student-howtos/Adafruit16x32LEDMatrixGuideForBBB-Code/test_ledMatrix.c

#ifndef __LED_H
#define __LED_H

enum eXBOXButton{
    XBOX_A,
    XBOX_B,
    XBOX_X,
    XBOX_Y,
    XBOX_NUM_TYPE // 4 button in total
};

// export GPIOs and set Directions to out for them
int LED_init(void);

void LED_cleanup(void);

// display rectangle on LED
// @params:
//      two vertexs for diagonal of the rectangle
//      (x1, y1) : one of Vertex for rectangle
//      (x2, y2) : the other vertex for rectangle 
void LED_display_rectagle(int x1, int y1, int x2, int y2, int color);

// Clean up LED 
void LED_clean_display(void);
#endif