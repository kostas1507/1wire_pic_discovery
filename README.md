# 1wire_pic_discovery
A simple 1 wire implementation for pic16 8bit microcontrollers with a discovery algorith built in. 

This is a custom discovery algorithm that I created that is different to the typical discovery algorithm found in most 1wire implementations. It is not compatible with other devices and both slave and master devices need to be flashed with the appropriate code.

This has been tested to work on pic16f15244.

Once you have set this up, you should be able to get a list of all your slave devices attached to the 1wire line!

You need to make a project in mplab and put all one_wire*.c files in source files and one_wire*.h files in header files. You could only include master files for master (or slave files for slave) but I recommend just having one project and defining the type of device using a #define in main.c as I have done here

There is an example implementation in main.c but you need to change #pragma variables according to your microcontroller, I'm building this on pic16f15244. I is required that you run this at 32MHz and I recommend disabling watchdog timer.

make sure to configure pins and peripherals in one_wire_conf.h and reading the instucting comments found there
