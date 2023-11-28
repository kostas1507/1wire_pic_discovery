# 1wire_pic_discovery
A simple 1 wire implementation with a discovery algorith built in. It is different to the default search algo for 1 wire but should work on all 8bit pic microcontrollers without problem. One device should be defined as master and the rest as slaves
Once you have set this up, you should be able to get a list of all your slave devices attached to the 1wire line!

You need to make a project in mplab and put all one_wire*.c files in source files and one_wire*.h files in header files. 
There is an example implementation in main.c but you need to change #pragma variables for your microcontroller, I'm building this on pic16f15244
make sure to configure pins and peripherals used in one_wire_conf.h and make sure to read the instucting comments in one_wire_conf.h
