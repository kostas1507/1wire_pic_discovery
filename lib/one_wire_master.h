/* 
 * File:   one_wire_master.h
 * Author: kpats
 *
 * Created on September 4, 2023, 11:52 PM
 */

#ifndef ONE_WIRE_MASTER_H
#define	ONE_WIRE_MASTER_H

#include <xc.h>
#include "one_wire_conf.h"


//all functions expect the pin used to be set to digital inputs:
    //TRISx_pin = 1 (input), ANSELx_pin = 0 (digital)
//also the pins output state should be preset to low:
    //LATx_pin = 0
//if there is NO external pull-up resistor, the pin should have an internal pullup
//WPUx_pin = 1 (pullup). Otherwise, the pin needs to be open drain: WPUx_pin = 0



uint8_t one_wire_master_reset();
void one_wire_master_write_zero();
void one_wire_master_write_one();
void one_wire_master_send_read_signal();
uint8_t one_wire_master_read_bit();
uint8_t one_wire_master_write(uint8_t * data, uint8_t len);
uint8_t one_wire_master_byte_write(uint8_t byte);
int8_t one_wire_master_search_devices(uint8_t * ids);

#endif	/* 1WIRE_MASTER_H */

