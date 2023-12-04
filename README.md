# 1wire_pic_discovery
A simple 1 wire protocol implementation for pic16 8bit microcontrollers with a discovery algorith built in. 

This is a custom discovery algorithm that I created that is different to the typical discovery algorithm found in most 1wire implementations. It is not compatible with other devices and both slave and master devices need to be flashed with code found in this repository.

***

You can set the 7 bit slave ID through a #define on one_wire_slave.h. Once you connect all your slaves on the same bus with the master, the master should be able to create an array with all the slave addresses. The best part, only one data wire is needed for the whole bus.

If you don't need to power your slaves externally, all that is needed is a ground connection and the 1wire line. If you do need to power your slaves, a third cable is normally required but since 1wire is a normally-high protocol you could parasitically power your device with the 1 wire line ( I have not tried this but it should be pretty simple to implement using a simple diode and capacitor on the 1 wire line ) 

This is great for small battery powered devices that need to be docked as it enables the dock device to both charge them and detect the presence of each separate slave device using a single bus of two or three lines instead of dozens of separate cables along with dozens of i/o pins on the master device.

This has been tested to work on pic16f15244.

***

**How to Use**
1. Create an mplab project for your microcontroller, using the xc8 compiler
2. Navigate to the project's folder and clone this repository
3. Inside of mplab, right click on header files and select "add existing item". Then select all .h files found in the lib/ directory . Do the same for source files
4. Configure pins and peripherals in one_wire_conf.h and make sure you follow the instructions on comments found there


*You could include only master files for master (or slave files for slave) but I recommend just having one project and defining the type of device using a #define in main.c as I have done here*

There is an example implementation in examples/main.c but you need to change #pragma variables depending to your microcontroller, I'm building this on pic16f15244. It is required that you run this at 32MHz and I recommend disabling watchdog timer (I have not tested it with watchdog timer enabled).

****

## Disclaimer (ChatGPT generated):

This project, "1wire-pic-discovery," is an independent software implementation for PIC microcontrollers aimed at supporting the 1-wire protocol. It is not affiliated with, endorsed by, or connected to any products or services associated with the trademark "1wire" or its owner. The use of the term "1wire" in this project is descriptive and refers solely to the implementation of the 1-wire protocol for PIC microcontrollers. Any reference to "1wire" is not intended to create confusion with or infringe upon the rights of the trademark owner. All trademarks and registered trademarks mentioned in this project belong to their respective owners.

