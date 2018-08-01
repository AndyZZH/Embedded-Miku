#ifndef __DISPLAY_H
#define __DISPLAY_H

/*
 * Function: Display_init()
 * -------------------------
 *  init Display
 *
 *  @ delaytime : the period which it takes for the component to go down one row in ms
 */
int Display_init(int delaytime);

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
void Display_generateComponent(int button);

/*
 * Function: Display_decreaseLife()
 * ---------------------------
 * Function to decrease life to @life
 *
 */
void Display_decreaseLife(int life);


/*
 * Function: Display_decreaseLife()
 * ---------------------------
 * Function to recharge life to @life
 * if @life is more than MAX_LIFE, it recharge just as much as MAX_LIFE
 *
 */
void Display_decreaseLife(int life);
void Display_rechargeLife(int life);
#endif
