/**
******************************************************************************
*   @file     Communication.h
*   @brief    Header file for communication part
*   @version  V0.3
*   @author   ADI
*   @date     March 2016
*  @par Revision History:
*  - V0.1, September 2015: initial version.
*  - V0.2, October 2015: added missing comments and revision history.
*  - V0.3, March 2016: added pin configuration based on pin selection.
*
*******************************************************************************
* Copyright 2015(c) Analog Devices, Inc.
*
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without modification,
* are permitted provided that the following conditions are met:
*  - Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
*  - Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in
*    the documentation and/or other materials provided with the
*    distribution.
*  - Neither the name of Analog Devices, Inc. nor the names of its
*    contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*  - The use of this software may or may not infringe the patent rights
*    of one or more patent holders.  This license does not release you
*    from the requirement that you obtain separate licenses from these
*    patent holders to use this software.
*  - Use of the software either in source or binary form, must be run
*    on or directly connected to an Analog Devices Inc. component.
*
* THIS SOFTWARE IS PROVIDED BY ANALOG DEVICES "AS IS" AND ANY EXPRESS OR IMPLIED
* WARRANTIES, INCLUDING, BUT NOT LIMITED TO, NON-INFRINGEMENT, MERCHANTABILITY
* AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL ANALOG DEVICES BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
* INTELLECTUAL PROPERTY RIGHTS, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*******************************************************************************
**/
#ifndef _COMMUNICATION_H_
#define _COMMUNICATION_H_

#include "Arduino.h"
#include "SPI.h"

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
**************************** Internal types ************************************
********************************************************************************/

/* Write data mode */
typedef enum {
   SPI_WRITE_DATA = 1,            /* Write data to LCD */
   SPI_WRITE_COMMAND,               /* Write command to LCD */
   SPI_WRITE_REG                 /* Write ACC register */

} enWriteData;

typedef enum {
   SPI_READ_ONE_REG = 1,            /* Read one ACC register */
   SPI_READ_TWO_REG               /* Read two ACC registers */

} enRegsNum;


/*******************************************************************************
**************************** Internal definitions ******************************
********************************************************************************/

/* Accelerometer write command */
#define COMM_WRITE         0x0A

/* Accelerometer read command */
#define COMM_READ          0x0B

/* Unused address */
#define ADDR_NOT_USE       0x00

/* LCD_CS_SEL pins */
#define CSLCD_PIN_P2_2           1   /* Select P2.2 */
#define CSLCD_PIN_P1_4           2   /* Select P1.4 */

/* ADXL_CS_SEL pins */
#define CSACC_PIN_P0_3           3   /* Select P0.3 */
#define CSACC_PIN_P0_4           4   /* Select P0.4 */

/* ADXL_INT_SEL pins */
#define INTACC_PIN_1             5   /* Select INT1 */
#define INTACC_PIN_2             6   /* Select INT2 */

/* LDC_RST_SEL pins */
#define RSLCD_PIN_IOREF           7   /* Select IOREF */
#define RSLCD_PIN_P1_1            8   /* Select P1.1 */

/*******************************************************************************
**************************** Functions declarations *****************************
********************************************************************************/
void SPI_Write(uint8_t ui8address, uint8_t ui8Data, enWriteData enMode);
uint16_t SPI_Read(uint8_t ui8address, enRegsNum enRegs);


/*******************************************************************************
******************Configuration parameters(set by the user)*********************
********************************************************************************/
/* Select LCD CS pin based on jumper P8 setting.
 * Available values:
 *    CSLCD_PIN_P2_2
 *    CSLCD_PIN_P1_4 */
#define LCD_CS_SEL          CSLCD_PIN_P1_4

/* Select ADXL362 CS pin based on jumper P9 setting.
 * Available values:
 *    CSACC_PIN_P0_3
 *    CSACC_PIN_P0_4 */
#define ADXL_CS_SEL         CSACC_PIN_P0_3

/* Select ADXL362 INT pin based on jumper P7 setting.
 * Available values:
 *    INTACC_PIN_1
 *    INTACC_PIN_2 */
#define ADXL_INT_SEL        INTACC_PIN_1

/* Select LCD RST pin based on jumper P6 setting.
 * Available values:
 *    RSLCD_PIN_IOREF
 *    RSLCD_PIN_P1_1 */
#define LDC_RST_SEL         RSLCD_PIN_IOREF


/*********************Pins configuration (not set by the user)*******************/
/*** LCD CS pin configuration ***/
#if(LCD_CS_SEL == CSLCD_PIN_P1_4)
/* CSLCD - P1.4 - output */
#define CSLCD_PIN        6
#elif(LCD_CS_SEL == CSLCD_PIN_P2_2)
/* CSLCD - P2.2 - output */
#define CSLCD_PIN        7
#endif

/*** LCD A0 pin configuration ***/
/* A0 - output */
#define A0LCD_PIN          5

/*** LCD BL pin configuration ***/
/* BL - P0.5 - output */
#define BLLCD_PIN          8


/*** LCD RST pin configuration ***/
#if(LDC_RST_SEL == RSLCD_PIN_P1_1)
/* RES - P1.1 - output */
#define RSLCD_PIN         3
#endif

/*** ACC CS pin configuration ***/
#if(ADXL_CS_SEL == CSACC_PIN_P0_4)
/* CSADXL362 - P0.4- output */
#define CSACC_PIN          9
#elif(ADXL_CS_SEL == CSACC_PIN_P0_3)
/* CSADXL362 - P0.3- output */
#define CSACC_PIN          10
#endif

/*** ACC INT pin configuration */
/* INT - P1.0 - input */
#define INTACC_PIN         2

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* _COMMUNICATION_H_ */
