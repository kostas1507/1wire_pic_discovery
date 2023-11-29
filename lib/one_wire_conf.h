/* 
 * File:   one_wire_conf.h
 * Author: kpats
 *
 * Created on September 18, 2023, 11:12 PM
 */

#ifndef ONE_WIRE_CONF_H
#define	ONE_WIRE_CONF_H

//define the following depending on configuration
#define WIRE_PIN 2 //this is the pin number of the 1 wire pin within its port
#define WIRE_PORT PORTA //this register contains the state of 1 wire port pins
#define WIRE_TRIS TRISA //this register controls I-O modes for 1 wire port pins
#define _XTAL_FREQ 32000000 //this is requred as the __delay_us() function is used


//some functions require an 8 bit timer to be setup with a period of 2us and 
    //a period value of 255
//set this to the timer counter address
#define WIRE_TIMER_COUNTER TMR0L //TMR0L

#define ONE_WIRE_DEVICE_SEARCH_COMMAND 0x69 
#define ONE_WIRE_CONTINUE_DEVICE_SEARCH_COMMAND 0x42


#endif	/* ONE_WIRE_CONF_H */

