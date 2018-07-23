#ifndef __DISPLAY_H
#define __DISPLAY_H

/*
 * Function: Display_init()
 * -------------------------
 *  init Display
 *
 *  @ delaytime : the period which it takes for the component to reach its destination and disapper
 */
int Didsplay_init(int delaytime);

void Display_cleanup(void);

/*
 * Function: Display_geneationComponenet()
 * ---------------------------
 * Function to check the free slots for displaying component
 * - if there is, enqueue in it
 * - if no slot available, skip
 *
 *   @ button:
 *      - 0 : A (Green)
 *      - 1 : B (Red)
 *      - 2 : X (Blue)
 *      - 3 : Y (Yellow)
 */
void Display_generateComponenet(int button);
