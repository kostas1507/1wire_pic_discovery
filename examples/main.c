/*
 * File:   main.c
 * Author: kpats
 *
 * Created on September 4, 2023, 6:16 PM
 */


// PIC16F15244 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FEXTOSC = OFF    // External Oscillator Mode Selection bits (Oscillator not enabled)
#pragma config RSTOSC = HFINTOSC_32MHZ// Power-up Default Value for COSC bits (HFINTOSC (32 MHz))
#pragma config CLKOUTEN = OFF   // Clock Out Enable bit (CLKOUT function is disabled; I/O function on RA4)
#pragma config VDDAR = HI       // VDD Range Analog Calibration Selection bit (Internal analog systems are calibrated for operation between VDD = 2.3V - 5.5V)

// CONFIG2
#pragma config MCLRE = EXTMCLR  // Master Clear Enable bit (If LVP = 0, MCLR pin is MCLR; If LVP = 1, RA3 pin function is MCLR)
#pragma config PWRTS = PWRT_OFF // Power-up Timer Selection bits (PWRT is disabled)
#pragma config WDTE = OFF       // WDT Operating Mode bits (WDT disabled; SEN is ignored)
#pragma config BOREN = ON       // Brown-out Reset Enable bits (Brown-out Reset Enabled, SBOREN bit is ignored)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection bit (Brown-out Reset Voltage (VBOR) set to 1.9V)
#pragma config PPS1WAY = ON     // PPSLOCKED One-Way Set Enable bit (The PPSLOCKED bit can be set once after an unlocking sequence is executed; once PPSLOCKED is set, all future changes to PPS registers are prevented)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable bit (Stack Overflow or Underflow will cause a reset)

// CONFIG3

// CONFIG4
#pragma config BBSIZE = BB512   // Boot Block Size Selection bits (512 words boot block size)
#pragma config BBEN = OFF       // Boot Block Enable bit (Boot Block is disabled)
#pragma config SAFEN = OFF      // SAF Enable bit (SAF is disabled)
#pragma config WRTAPP = OFF     // Application Block Write Protection bit (Application Block is not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot Block is not write-protected)
#pragma config WRTC = OFF       // Configuration Registers Write Protection bit (Configuration Registers are not write-protected)
#pragma config WRTSAF = OFF     // Storage Area Flash (SAF) Write Protection bit (SAF is not write-protected)
#pragma config LVP = ON         // Low Voltage Programming Enable bit (Low Voltage programming enabled. MCLR/Vpp pin function is MCLR. MCLRE Configuration bit is ignored.)

// CONFIG5
#pragma config CP = OFF         // User Program Flash Memory Code Protection bit (User Program Flash Memory code protection is disabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
#define IS_MASTER 1

#define _XTAL_FREQ 32000000
#include <xc.h>
#include "one_wire_master.h"
#include "one_wire_slave.h"

//variables for master
#if IS_MASTER
uint8_t device_ids[15];
int8_t devices;
#endif

//variables for slave
#if !IS_MASTER
uint8_t been_discovered = 1;
#endif

//#include "1wire_master.c"
void main(void) {
    //setup one wire pin
    TRISA |= 1<<2; //initially set to input mode
    ANSELA &= ~(1<<2); //is digital input
    LATA &= ~(1<<2); //its output value is preset to 0
    WPUA |= 1<<2; //when in input mode, an internal pull-up resistor is activated
    
    //setup timer, in this case timer0. Period of 2 us, period value 255
    //this is required for one wire
    T0CON0 = 0b10000000; //enabled, 8 bit, 1:1 postscaler
    T0CON1 = 0b01110110; //source is HFINTOSC(needs to be 32MHz), async, 1:64 prescaler
    TMR0H = 0xFF; //period value set to 255

    
    //setup led testing pin
    LATA |= 1<<1;
    TRISA &= ~(1<<1);
    
    
    while(1){
#if IS_MASTER
        //for master
        devices = one_wire_master_search_devices(device_ids);
        if(devices>0 && device_ids[0] == one_wire_slave_ID)
            LATA |= 1<<1;
        else
            LATA &= ~(1<<1);
        __delay_ms(100);
#endif
        
#if !IS_MASTER
        //for slave


        if(!(WIRE_PORT & (1<<WIRE_PIN))){
            LATA &= ~(1<<1);
            uint8_t instruction = 0;
            int8_t ret_code = one_wire_slave_read_instruction(&instruction);
            if((instruction == ONE_WIRE_DEVICE_SEARCH_COMMAND)||
                    (instruction == ONE_WIRE_CONTINUE_DEVICE_SEARCH_COMMAND && (!been_discovered))){
                if(one_wire_slave_handle_device_search() == 1) //if device completed communication
                    been_discovered = 1;
                else
                    been_discovered = 0;
            }
            LATA |= 1<<1;
        }    
#endif  
        
        
    }
    return;
}
