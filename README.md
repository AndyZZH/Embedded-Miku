# Embedded-Miku

Embedded-Miku is a program which processes audio input in real-time and create a rythm game out of the processed input. This project is inspired by [Hatsune Miku](https://en.wikipedia.org/wiki/Hatsune_Miku), a rythm game. This is made for final project in Embedded System course, CMPT433, in [SFU](https://www.sfu.ca/).

Refer [Detailed information](https://github.com/AndyZZH/Embedded-Miku/blob/master/demo/WRITE_UP.pdf) for more detailed information.

![alt text](https://github.com/AndyZZH/Embedded-Miku/blob/master/demo/demo.png)
<Figure 1: The picture of playing Embedded-Miku>

## Initial Setup for Dependencies

Follow the instructions below in BBG:

1. Add Debian 9's apt-get repo (branch `stretch`) in `/etc/apt/sources.list` for `libc++6` library
2. Add Debian 9.5's apt-get repo (branch `buster`) in `/etc/apt/sources.list` for `libaubio5` library

## Install Dependencies 

1. Replace all `jessie` word in `/etc/apt/sources.list` with `stretch` and then execute the following:
   ```
   # apt-get update
   # apt-get install libc++6
   ```

2. Command out "`deb http://httpredir.debian.org/debian/ stretch main contrib non-free`" in `/etc/apt/sources.list` and use "`deb http://httpredir.debian.org/debian/ buster main contrib non-free`" instead. 

    The difference between the two is to replace `stretch` with `buster`. 

    After you finish replacing the main repo URL, execute the following: 

    ```
    # apt-get update
    # apt-get install libaubio5 libaubio-dev
    ```

3. After installing `libsubio5` and `libaubio-dev`, you can reenable the `stretch` spt-get repo and comment out the `buster` one. 

## Initial Setup

1. To install XBox controller driver, execute the script `script/joystick_script`.

   (You may need to add executing permission by the command `chmod +x joystick_script`.)

2. Enable the I2C in the BeagleBone by executing `echo BB-I2C1 > sys/devices/platform/bone_capemgr/slots`. 

3. Run the executable `miku` 


## Building an executable

1. Reboot the BeagleBone after finishing Intial Setup. 

2. Change directory to the root folder and then run the `Makefile` with command `make`. 

   With default settings, it will use `arm-linux-gnueabihf-g++` and `arm-linux-gnueabihf-gcc` to cross compile. 
   If you don't want cross compilation, run the `Makefile` with `make CROSS_TOOL=`, which erases out the cross tool prefix before `g++` and `gcc`.

3. The executable will be generated and located in `~/cmpt433/public/myApps/miku`. 

## Author

See [contributor](https://github.com/AndyZZH/Embedded-Miku/graphs/contributors) page.
