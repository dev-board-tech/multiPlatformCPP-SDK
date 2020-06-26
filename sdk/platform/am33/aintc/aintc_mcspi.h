/*
 * aintc_mcspi.h
 *
 *  Created on: Dec 12, 2012
 *      Author: XxXx
 */
/*#####################################################*/
#ifndef AINTC_MCSPI_H_
#define AINTC_MCSPI_H_
/*#####################################################*/
#include "api/spi.h"
//#include "include/mcspi.h"
/*#####################################################*/
typedef struct
{
    GI::Dev::Spi* Mcspi0;
    GI::Dev::Spi* Mcspi1;
}Mcspi_Int_Service_t;
/*#####################################################*/
void McSPIAintcConfigure(unsigned char instance);
void McSPIAintcUnConfigure(unsigned char instance);
/*#####################################################*/
#ifdef HEADER_INCLUDE_C_FILES
#include "aintc_mcspi.c"
#endif
/*#####################################################*/
#endif /* AINTC_MCSPI_H_ */
/*#####################################################*/
