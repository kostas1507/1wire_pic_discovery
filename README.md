# 1wire_pic_discovery
A simple 1 wire implementation for pic16 8bit microcontrollers with a discovery algorith built in. 

This is a custom discovery algorithm that I created that is different to the typical discovery algorithm found in most 1wire implementations. It is not compatible with other devices and both slave and master devices need to be flashed with code found in this repository.

This has been tested to work on pic16f15244.

Once you have set this up, you should be able to get a list of all your slave devices attached to the 1wire line!

**How to Use**
1. Create an mplab project for your microcontroller, using the xc8 compiler
2. Navigate to the project's folder and clone this repository
3. Inside of mplab, right click on header files and select "add existing item". Then select all .h files found in the lib/ directory . Do the same for source files
4. Configure pins and peripherals in one_wire_conf.h and make sure you follow the instructions on comments found there


*You could include only master files for master (or slave files for slave) but I recommend just having one project and defining the type of device using a #define in main.c as I have done here*

There is an example implementation in examples/main.c but you need to change #pragma variables depending to your microcontroller, I'm building this on pic16f15244. It is required that you run this at 32MHz and I recommend disabling watchdog timer (I have not tested it with watchdog timer enabled).

