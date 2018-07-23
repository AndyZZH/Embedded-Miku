
#ifndef __GAME_H
#define __GAME_H

void Game_init(void);
void Game_cleanup(void);

/*
 * Function:  Game_EnqueueBeat()
 * --------------------
 * Function to enqueue beat in BeatSlot
 * - if there is slot is overdue, replace
 * - if no slot available, skip
 * 
 * Randomly choice start point at BeatSlot
 * 
 * 
 *  returns: void
 */
void Game_EnqueueBeat(void);

/*
 * Function:  Game_EnqueueBeat()
 * --------------------
 *                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
 * 
 *  returns: delayTime
 */
long Game_getDelayTime(void);

/*
 * Function:  Game_checkBeat()
 * --------------------
 * Function to get the button_id, genereate button struct {timestamp, button_id}
 * Compare {timestamp, button_id} with BeatSlot
 * If valid: score++, set timestamp in slot{button_id} 0 (make it overdue)
 * otherwise do nothing
 * 
 *  returns: void
 */
void Game_checkBeat(int button_id);

#endif
