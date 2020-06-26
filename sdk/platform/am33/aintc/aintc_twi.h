/*
 * aintc_twi.h
 *
 *  Created on: Dec 3, 2012
 *      Author: XxXx
 */
/*#####################################################*/
#ifndef AINTC_TWI_H_
#define AINTC_TWI_H_
/*#####################################################*/
#include "stdbool.h"
#include "api/i2c.h"
/*#####################################################*/
typedef struct
{
    //GI::Dev::I2c* Twi0;
   // GI::Dev::I2c* Twi1;
   // GI::Dev::I2c* Twi2;
}Twi_Int_Service_t;
/*#####################################################*/
void I2CAINTCConfigure(unsigned char unit_nr);
void I2CAINTCUnConfigure(unsigned char unit_nr);
void CleanUpInterrupts(unsigned char unit_nr);
/*#####################################################*/
extern Twi_Int_Service_t Twi_Int_Service;
/*#####################################################*/
#ifdef HEADER_INCLUDE_C_FILES
#include "aintc_twi.c"
#endif
/*#####################################################*/
#endif /* AINTC_TWI_H_ */
/*#####################################################*/
