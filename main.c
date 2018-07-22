#include "led.h"
#include <stdio.h>


int main() {
    int result = LED_init();
    LED_cleanup();
    printf("hello !\n");
    return 0;
}
