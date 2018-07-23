#ifndef __DISPLAY_H
#define __DISPLAY_H

int Didsplay_init(void);
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
