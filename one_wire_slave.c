/*
 * File:   one_wire_slave.c
 * Author: kpats
 *
 * Created on September 12, 2023, 3:46 AM
 */

#include "one_wire_slave.h"

//this function needs to be called right after the bus has been driven low
    //setting up an external interrupt is ideal given the importance of timing
//
//if the message does not start with a reset signal this will simply return 0
//if the message does start with a reset signal,
    //this will respond to it and read the instruction byte send right after.
//if bus has frozen for too long, the function will return error code -1
//
//the instruction byte will be written into the "byte" operant and 
    //the function will return 1
//the instruction byte must be sent in LSB order
int8_t one_wire_slave_read_instruction(uint8_t * byte){
    //if communication did not start with a reset signal return 0
    if(!one_wire_slave_detect_high_safe(__SPLIT(100), __SPLIT(500))){
        return 0;
    }
        
    //send "connected" signal
    __delay_us(40);
    WIRE_TRIS &= ~(1<<WIRE_PIN);
    __delay_us(60);
    WIRE_TRIS |= 1<<WIRE_PIN;
    
    __delay_us(370);//wait for reset to end
    
    uint8_t return_value = 0;
    for(uint8_t i = 0; i < 8; ++i){
        //wait until new bit is sent
        if(!one_wire_slave_detect_low_safe(__SPLIT(0), __SPLIT(50)))
            return -1; //if more than 16us passed, return -1
        return_value |= one_wire_slave_read_bit() << i;
    }
    
    *byte = return_value;
    return 1;
}

//call this right after the device search command has been sent
//ID must be sent in LSB order
//this returns -1 if errors occurred during communication
    //1 if the whole address was transmitted
    //and 0 if the master continued communication with an other device 
int8_t one_wire_slave_handle_device_search(){
    for(uint8_t i = 0; i < 8; ++i){

        //wait until new bit is sent
        if(!one_wire_slave_detect_low_safe(__SPLIT(0), __SPLIT(50)))
            return -1; //if more than 16us passed, return -1


        uint8_t read_from_bus = one_wire_slave_read_bit();  

        if(read_from_bus == !!(one_wire_slave_ID & (1<<i))){
            
            //wait until read signal is sent
            if(!one_wire_slave_detect_low_safe(__SPLIT(0), __SPLIT(50)))
                return -1; //if more than 16us passed, return -1
            //and wait until read signal is finished
            if(!one_wire_slave_detect_high_safe(__SPLIT(0), __SPLIT(50)))
                return -1; //if more than 10us passed, return -1



            //send "correct bit" signal
            __delay_us(4);
            WIRE_TRIS &= ~(1<<WIRE_PIN);
            __delay_us(10);
            WIRE_TRIS |= 1<<WIRE_PIN;
            __delay_us(35); //wait for read to end
        }
        else{
            //wait until read signal is sent
            if(!one_wire_slave_detect_low_safe(__SPLIT(0), __SPLIT(50)))
                return -1; //if more than 16us passed, return -1
            //and wait until read signal is finished
            if(!one_wire_slave_detect_high_safe(__SPLIT(0), __SPLIT(50)))
                return -1; //if more than 10us passed, return -1
            __delay_us(9);

            //check if other device responded
            //if no device responded, stay in this function and wait for next guess
                //for current bit (not incrementing i)
            //if a device did respond, communication continues only with that
                //device(maybe multiple devices). This function should then return
            if(WIRE_PORT & (1<<WIRE_PIN)){
                i--;
                __delay_us(50); //delay until read is finished
            }
            else{
                return 0;
            }
        }  
    }
    return 1;
}

//call this right after the bus was set low and a bit sent is expected
uint8_t one_wire_slave_read_bit(){
    __delay_us(10);
    uint8_t ret = WIRE_PORT & (1<<WIRE_PIN);
    __delay_us(45);
    return !!ret;
}

//requires timer to have a period of 2us and a period value of 255
//this function returns once the one wire pin has detected low or time_out_us_X2 has been surpassed
//it returns 1 if low was detected within the min/max range specified by arguments
//and returns 0 otherwise
uint8_t one_wire_slave_detect_low_safe(uint8_t min_us_X2, uint8_t timeout_us_X2){
    WIRE_TIMER_COUNTER = 0;
    while(WIRE_PORT & (1<<WIRE_PIN))
        if(WIRE_TIMER_COUNTER>timeout_us_X2)
            return 0;
    if(WIRE_TIMER_COUNTER<min_us_X2)
        return 0;
    return 1;
}

//requires timer to have a period of 2us and a period value of 255
//this function returns once the one wire pin has detected high or time_out_us_X2 has been surpassed
//it returns 1 if high was detected within the min/max range specified by arguments
//and returns 0 otherwise
uint8_t one_wire_slave_detect_high_safe(uint8_t min_us_X2, uint8_t timeout_us_X2){
    WIRE_TIMER_COUNTER = 0;
    while(!(WIRE_PORT & (1<<WIRE_PIN)))
        if(WIRE_TIMER_COUNTER>timeout_us_X2)
            return 0;
    if(WIRE_TIMER_COUNTER<min_us_X2)
        return 0;
    return 1;
}
