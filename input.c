#include <fcntl.h>
#include <stdio.h>
#include <linux/joystick.h>
#include <unistd.h>
#include <stdbool.h>
#include <pthread.h>
#include <stdlib.h>
#include "game.h"

#define DEVICE_NAME "/dev/input/js0"

static pthread_t input_thread_id;
static bool input_thread_done;
static const char *device;
static int js;
static struct js_event event;

/**
 * Reads a joystick event from the joystick device.
 *
 * Returns 0 on success. Otherwise -1 is returned.
 */
static int read_event(int fd, struct js_event *event)
{
    ssize_t bytes;

    bytes = read(fd, event, sizeof(*event));

    if (bytes == sizeof(*event))
        return 0;

    /* Error, could not read full event. */
    return -1;
}


/**
 * Input_thread that keep check if a button is pressed
 * If there is, call the Game_checkBeat() of game.c
 */

static void* input_thread()
{
    js = open(device, O_RDONLY);

    if (js == -1)
        perror("Could not open joystick");

    /* This loop will exit if the controller is unplugged. */
    while ((read_event(js, &event) == 0) && !input_thread_done)
    {
      if(event.type == JS_EVENT_BUTTON && event.value && ((event.number < 4) || (event.number == 6))){
        Game_checkBeat((int)event.number);
      }
    }

    close(js);
    return NULL;
}

/**
 * start the input thread
 */
void Input_init(){
  device = "/dev/input/js0";
  input_thread_done = false;

  if(pthread_create(&input_thread_id, NULL, input_thread, NULL) == -1){
      printf("Error: failed to create input thread.\n");
      exit(-1);
  }
}


/**
 * stop the input thread
 */
void Input_cleanup(){
  input_thread_done = true;
  pthread_join(input_thread_id, NULL);
}
