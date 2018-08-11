# Embedded-Miku

Embedded-Miku is a real-time music game runs on embedded system, inspired by [Hatsune Miku](https://en.wikipedia.org/wiki/Hatsune_Miku) music game. This is also final project in Embedded System course in [SFU](https://www.sfu.ca/).

## Initial Dependency Setup for BeagleBone Green

You will need to do the following in target (BBG):

1. `libc++6` library. For this one to work, you need to add Debian 9's apt-get repo (branch `stretch`) in `/etc/apt/sources.list`.
2. `libaubio5` library for audio beat detection. For this one to work, you need to add Debian 9.5's apt-get repo (branch `buster`) in `/etc/apt/sources.list`.

## Prerequisites

1. Replace all `jessie` word in `/etc/apt/sources.list` with `stretch` and then execute the following:
   ```
   # apt-get update
   # apt-get install libc++6
   ```

2. Command out "`deb http://httpredir.debian.org/debian/ stretch main contrib non-free`" in `/etc/apt/sources.list` and use this one: "`deb http://httpredir.debian.org/debian/ buster main contrib non-free`". 

    The difference between the two is to replace `stretch` with `buster`. 

    After you finish replacing the main repo URL, execute the following: 

    ```
    # apt-get update
    # apt-get install libaubio5 libaubio-dev
    ```

3. After installing `libsubio5` and `libaubio-dev`, you can reenable the `stretch` spt-get repo and comment out the `buster` one. 

## Building an executable

1. Reboot the BeagleBone after installing the driver. 

2. Change directory to the root folder and then run the `Makefile` with command `make`. 

    With default settings, it will use `arm-linux-gnueabihf-g++` and `arm-linux-gnueabihf-gcc` to cross compile. 

    If you don't want cross compilation, run the `Makefile` with `make CROSS_TOOL=`, which erases out the cross tool prefix before `g++` and `gcc`.

3. The executable will be generated and located in `~/cmpt433/public/myApps/miku`. 

## Initial Setup for Running the executable

1. We need to install XBox controller driver first before running the program. Finish this step by executing the script located in `script/joystick_script`. You may need to add executing permission (`chmod +x joystick_script`) first. 
2. Enable the I2C in the BeagleBone by executing `echo BB-I2C1 > sys/devices/platform/bone_capemgr/slots`. 
3. Run the executable `miku` and have fun!

## Author

See [contributor](https://github.com/AndyZZH/Embedded-Miku/graphs/contributors) page.