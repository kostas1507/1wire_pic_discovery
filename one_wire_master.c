#include "one_wire_master.h"


//return 1 if there are devices attached, 0 if there are no devices attached
//@param port is PORTx regitster for pin and tris is TRISx register for pin
uint8_t one_wire_master_reset(){
    WIRE_TRIS &= ~(1<<WIRE_PIN);
    //asm("MOVLB 0x0\nBCF TRISA, 0x2");
    __delay_us(480);
    WIRE_TRIS |= 1<<WIRE_PIN;
    //asm("MOVLB 0x0\nBSF TRISA, 0x2");
    __delay_us(70);
    uint8_t ret = !(WIRE_PORT & 1<<WIRE_PIN);
    __delay_us(410);
    return ret;
}

void one_wire_master_write_zero(){
    WIRE_TRIS &= ~(1<<WIRE_PIN);
    __delay_us(60);
    WIRE_TRIS |= 1<<WIRE_PIN;
    __delay_us(10);
}

void one_wire_master_write_one(){
    WIRE_TRIS &= ~(1<<WIRE_PIN);
    __delay_us(6);
    WIRE_TRIS |= 1<<WIRE_PIN;
    __delay_us(64);
}

void one_wire_master_send_read_signal(){
    WIRE_TRIS &= ~(1<<WIRE_PIN);
    __delay_us(6);
    WIRE_TRIS |= 1<<WIRE_PIN;
    __delay_us(9);
}

uint8_t one_wire_master_read_bit(){
    one_wire_master_send_read_signal();
    uint8_t ret = WIRE_PORT & 1<<WIRE_PIN;
    __delay_us(55);
    return !!ret;
}

//returns 0 if there are no devices(and doesn't transmit if so)
    //attached and 1 if there are
uint8_t one_wire_master_write(uint8_t * data, uint8_t len){
    uint8_t ret = one_wire_master_reset();
    if(ret == 0) return 0;
    for(uint8_t j = 0; j<len; ++j){
        uint8_t byte = data[j];
        for(uint8_t i = 0; i<8; ++i){
            if(byte & 1<<i)
                one_wire_master_write_one();
            else
                one_wire_master_write_zero();
        }
    }
    return 1;
}

//returns 0 if there are no devices(and doesn't transmit if so)
    //attached and 1 if there are
uint8_t one_wire_master_byte_write(uint8_t byte){
    uint8_t ret = one_wire_master_reset();
    if(ret == 0) return 0;
    for(uint8_t i = 0; i<8; ++i){
        if(byte & 1<<i)
            one_wire_master_write_one();
        else
            one_wire_master_write_zero();
    }
    return 1;
}

//returns number of devices attached (127 max). -1 if no devices attached
//"ids" will hold IDs of attached devices, make sure there is enough space
    //to hold all 32bit addresses
int8_t one_wire_master_search_devices(uint8_t * ids){
    
    int8_t count = 0;
    while(1){
        //send device search command the first time
            //and continue device search command the rest of the times
        uint8_t command = count == 0? ONE_WIRE_DEVICE_SEARCH_COMMAND 
                                            : ONE_WIRE_CONTINUE_DEVICE_SEARCH_COMMAND;
        if(one_wire_master_byte_write(command) == 0) return 0;
                
        uint8_t current_id = 0;
        for(uint8_t j = 0; j < 8; ++j){
            one_wire_master_write_zero(); //try zero
            if(one_wire_master_read_bit()){ //if no device responded
                one_wire_master_write_one(); //try one
                if(!one_wire_master_read_bit()) //if guess was correct
                    current_id |= 1<<j;
                else
                    return count;
            }
            //else, if guess was correct, leave bit as is (zero)
        }
        ids[count] = current_id;
        ++count;
    }
}