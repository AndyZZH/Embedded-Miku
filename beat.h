#ifndef __BEAT_H
#define __BEAT_H

#include <stdbool.h>


#ifdef __cplusplus
extern "C" {
#endif

/* Check if beat detection function is busy or not. 
 */
bool Beat_isIdle(void);

/* The function will examine the input array to analyze whether there is
 * onset in the array using an external library Aubio. If there happens
 * to be beats in the array, it will call enqueue beat function defined in
 * Game module. 
 *
 * Some part of this function is adapted from the official documentation 
 * of the library. 
 * Please check this link for details: https://aubio.org/doc/latest/examples_2aubioonset_8c-example.html
 *
 * Parameter: a pointer to a float array
 */
void Beat_enqueueIfIsBeat(float* frame);

void Beat_init(void);

#ifdef __cplusplus
}
#endif

#endif