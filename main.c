#include <stdio.h>
#include <unistd.h>
#include "led.h"
#include "display.h"

int main() {
    int result = LED_init();
    if (result > 0)
        return 0;
    result = Display_init(300);
    if (result > 0)
        return 0;
    printf("led is inited\n");
    Display_generateComponent(1);
    sleep(1);
    Display_generateComponent(0);
    sleep(1);
    Display_generateComponent(2);
    Display_generateComponent(3);

    
    sleep(10);
    Display_cleanup();

    return 0;
}
