#include <stdio.h>
#include <unistd.h>
#include "input.h"
#include "led.h"
#include "display.h"
#include "game.h"
#include "score_display.h"

int main(int argc, char *argv[])
{
  Input_init();
  LED_init();
  Display_init(1000/16);
  score_starter();
	int i =0;
  while(1){
	
//Display_generateComponent(i);    
	Game_EnqueueBeat();
    sleep(1);
	i++;
	i = i % 4;
  }

}
