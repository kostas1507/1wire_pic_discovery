/* 
 * File:   one_wire_slave.h
 * Author: kpats
 *
 * Created on September 12, 2023, 3:45 AM
 */

#ifndef ONE_WIRE_SLAVE_H
#define	ONE_WIRE_SLAVE_H

#include <xc.h>
#include "one_wire_conf.h"

//all functions expect the pin used to be set to digital inputs:
    //TRISx_pin = 1 (input), ANSELx_pin = 0 (digital)
//also the pins output state should be preset to low:
    //LATx_pin = 0

#define one_wire_slave_ID 0xAB

uint8_t one_wire_slave_read_bit();
int8_t one_wire_slave_read_instruction(uint8_t * byte);
int8_t one_wire_slave_handle_device_search();

uint8_t one_wire_slave_detect_low_safe(uint8_t min_us_X2, uint8_t timeout_us_X2);
uint8_t one_wire_slave_detect_high_safe(uint8_t min_us_X2, uint8_t timeout_us_X2);

#define __SPLIT(x) x/2

#endif	/* ONE_WIRE_SLAVE_H */

