/* 
 * File:   one_wire_utils.h
 * Author: kpats
 *
 * Created on September 28, 2023, 12:50 AM
 */

#ifndef ONE_WIRE_UTILS_H
#define	ONE_WIRE_UTILS_H

#include <xc.h>

//some functions require an 8 bit timer to be setup with a period of 2us and 
    //a period value of 255
//set this to the timer counter address
#define TIMER_COUNTER TMR0L //TMR0L

void one_wire_detect_low_safe(uint8_t timeout_us_X2);
void one_wire_detect_high_safe(uint8_t timeout_us_X2);

#endif	/* ONE_WIRE_UTILS_H */

