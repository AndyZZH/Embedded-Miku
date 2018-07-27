#include "score_display.h"

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <stdbool.h>

#define I2CDRV_LINUX_BUS0 "/dev/i2c-0"
#define I2CDRV_LINUX_BUS1 "/dev/i2c-1"
#define I2CDRV_LINUX_BUS2 "/dev/i2c-2"

#define I2C_DEVICE_ADDRESS 0x20

#define REG_DIRA 0x00
#define REG_DIRB 0x01
#define REG_OUTA 0x14
#define REG_OUTB 0x15

#define PIN_NUM_1 61
#define PIN_NUM_2 44

#define OFF 0
#define ON 1

#define FLASH_TIME 5000000
pthread_t I2C_thread;
static bool I2C_done = false;

static const int DISPLAY_HEX_1[] = {0xA3, 0x80, 0x31, 0xB0, 0x90, 0x28, 0xB1, 0x80, 0xB1, 0xB0};
static const int DISPLAY_HEX_2[] = {0x96, 0x12, 0x0E, 0x06, 0x8A, 0x8C, 0x8C, 0x06, 0x8E, 0x8E};

static int digitDisplay = 0;

static void turnGPIO(int pinNum, int switchPin){
    char str[50];
    sprintf(str, "/sys/class/gpio/gpio%d/value",pinNum);
    FILE *pfile  = fopen(str, "w");
    fprintf(pfile, "%d", switchPin);
    fclose(pfile);
}


static int initI2cBus(char* bus, int address)
{
    int i2cFileDesc = open(bus, O_RDWR);
    if (i2cFileDesc < 0) {
        printf("I2C DRV: Unable to open bus for read/write (%s)\n", bus);
        printf("try: echo BB-I2C1 > /sys/devices/platform/bone_capemgr/slots\n");
        perror("Error is:");
        exit(-1);
    }

    int result = ioctl(i2cFileDesc, I2C_SLAVE, address);
    if (result < 0) {
        perror("Unable to set I2C device to slave address.");
        exit(-1);
    }
    return i2cFileDesc;
}

static void writeI2cReg(int i2cFileDesc, unsigned char regAddr, unsigned char value)
{
    unsigned char buff[2];
    buff[0] = regAddr;
    buff[1] = value;
    int res = (int)write(i2cFileDesc, buff, 2);
    if (res != 2) {
        perror("Unable to write i2c register");
        exit(-1);
    }
}

static void GPIO() {
    char str[50];
    sprintf(str, "/sys/class/gpio/export");
    FILE *pfile  = fopen(str, "w");
    fprintf(pfile, "%d", PIN_NUM_1);
    fclose(pfile);

    sprintf(str, "/sys/class/gpio/export");
    pfile  = fopen(str, "w");
    fprintf(pfile, "%d", PIN_NUM_2);
    fclose(pfile);

    sprintf(str, "/sys/class/gpio/gpio%d/direction",PIN_NUM_1);
    pfile  = fopen(str, "w");
    fprintf(pfile, "%s", "out");
    fclose(pfile);

    sprintf(str, "/sys/class/gpio/gpio%d/direction",PIN_NUM_2);
    pfile  = fopen(str, "w");
    fprintf(pfile, "%s", "out");
    fclose(pfile);

    int i2cFileDesc = initI2cBus(I2CDRV_LINUX_BUS1, I2C_DEVICE_ADDRESS);

    writeI2cReg(i2cFileDesc, REG_DIRA, 0x00);
    writeI2cReg(i2cFileDesc, REG_DIRB, 0x00);

    // Cleanup I2C access;
    close(i2cFileDesc);
}

void score_setDigit(long long digit){
    printf("Number of arrays sorted per second: %lld\n", digit);
    if(digit >= 99){
        digitDisplay = 99;
    }
    else{
        digitDisplay = (int)digit;
    }
}

static void changeHex(int showDigit){
    int i2cFileDesc = initI2cBus(I2CDRV_LINUX_BUS1, I2C_DEVICE_ADDRESS);

    writeI2cReg(i2cFileDesc, REG_OUTA, DISPLAY_HEX_1[showDigit]);
    writeI2cReg(i2cFileDesc, REG_OUTB, DISPLAY_HEX_2[showDigit]);

    // Cleanup I2C access;
    close(i2cFileDesc);
}

static void* changeDisplay(){
    turnGPIO(PIN_NUM_1, OFF);
    turnGPIO(PIN_NUM_2, OFF);
    while(!I2C_done){

        int leftDigit = digitDisplay / 10;
        int rightDigit = digitDisplay % 10;

        changeHex(leftDigit);
        turnGPIO(PIN_NUM_1, ON);
        nanosleep((const struct timespec[]){{0,FLASH_TIME}}, NULL);
        turnGPIO(PIN_NUM_1, OFF);

        changeHex(rightDigit);
        turnGPIO(PIN_NUM_2, ON);
        nanosleep((const struct timespec[]){{0,FLASH_TIME}}, NULL);
        turnGPIO(PIN_NUM_2, OFF);
    }

    return NULL;
}



void score_starter() {
    printf("Drive display (assumes GPIO #61 and #44 are output and 1)\n");
    GPIO();
    if(pthread_create(&I2C_thread, NULL, changeDisplay, NULL) == -1){
        printf("Error: failed to create I2C thread.\n");
        exit(-1);
    }
}



void score_stop(){
    I2C_done = true;
}

void score_waitForStop(){
    pthread_join(I2C_thread, NULL);
}
