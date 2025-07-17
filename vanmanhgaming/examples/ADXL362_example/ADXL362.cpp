/**
******************************************************************************
*   @file     ADXL362.c
*   @brief    Source file for ADXL362 accelerometer control.
*   @version  V0.3
*   @author   ADI
*   @date     March 2016
*  @par Revision History:
*  - V0.1, September 2015: initial version.
*  - V0.2, October 2015: removed ACC definitions, added configuration for CSACC pin and revision history.
*  - V0.3, March 2016: added support for ADXL362 INT pin.
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

/***************************** Include Files **********************************/
#include <stdio.h>

#include "ADXL362.h"
#include "Communication.h"

/****************************** Global Data ***********************************/

int16_t i16SensorX;
int16_t i16SensorY;
int16_t i16SensorZ;
int16_t i16SensorT;

volatile uint32_t ui32timer_counter = 0;


/*************************** Module static data *******************************/

/* Accelerometer scan counter */
static uint32_t ui32ScanSensorCounter;

/************************* Global scope functions *****************************/

/**
   @brief Initialization the accelerometer sensor

   @return none

**/
void Sensor_Init(void)
{          
   pinMode(CSACC_PIN, OUTPUT); /* Set CSACC pin as output */

   pinMode(INTACC_PIN, INPUT); /* Set INTACC pin as input */

   SPI_Write(SOFT_RESET_REG, 0x52, SPI_WRITE_REG);  /* Soft reset accelerometer */

   delay(100);                         /* Wait at least 0.5 ms */

   /* Set activity threshold */
   SPI_Write(THRESH_ACT_L, ACT_VALUE & 0xFF, SPI_WRITE_REG);
   SPI_Write(THRESH_ACT_H, ACT_VALUE >> 8, SPI_WRITE_REG);

   SPI_Write(TIME_ACT, (ACT_TIMER / 10), SPI_WRITE_REG);          /* Set activity time at 100Hz data rate */

   /* Set inactivity threshold */
   SPI_Write(THRESH_INACT_L, INACT_VALUE & 0xFF, SPI_WRITE_REG);
   SPI_Write(THRESH_INACT_H, INACT_VALUE >> 8, SPI_WRITE_REG);

   /* Set inactivity time at 100Hz data rate */
   SPI_Write(TIME_INACT_L, ((INACT_TIMER * 100) & 0xFF), SPI_WRITE_REG);
   SPI_Write(TIME_INACT_H, ((INACT_TIMER * 100) >> 8), SPI_WRITE_REG);

   SPI_Write(ACT_INACT_CTL, 0x3F, SPI_WRITE_REG);         /* Set Loop mode, referenced mode for activity and inactivity, enable activity and inactivity functionality */

#if(ADXL_INT_SEL == INTACC_PIN_1)
   SPI_Write(INTMAP1, 0x40, SPI_WRITE_REG);                  /* Map the awake status to INT1 pin */
#elif(ADXL_INT_SEL == INTACC_PIN_2)
   SPI_Write(INTMAP2, 0x40, SPI_WRITE_REG);                  /* Map the awake status to INT2 pin */
#endif
}

/**
   @brief Turns on accelerometer measurement mode.

   @return none

**/
void Sensor_Start(void)
{
   uint8_t ui8temp;

   ui8temp = (uint8_t)SPI_Read(POWER_CTL_REG, SPI_READ_ONE_REG);       /* Read POWER_CTL register, before modifying it */

   ui8temp = ui8temp | 0x02;                                          /* Set measurement bit in POWER_CTL register */

   SPI_Write(POWER_CTL_REG, ui8temp, SPI_WRITE_REG);                    /* Write the new value to POWER_CTL register */
}


/**
   @brief Puts the accelerometer into standby mode.

   @return none

**/
void Sensor_Stop(void)
{
   uint8_t ui8temp;

   ui8temp = (uint8_t)SPI_Read(POWER_CTL_REG, SPI_READ_ONE_REG);        /*Read POWER_CTL register, before modifying it */

   ui8temp = ui8temp & 0xFC;                                      /* Clear measurement bit in POWER_CTL register */

   SPI_Write(POWER_CTL_REG, ui8temp, SPI_WRITE_REG);                 /* Write the new value to POWER_CTL register */

}

/**
   @brief Reads the accelerometer data.

   @return none

**/
void Sensor_Scan(void)
{
      i16SensorX = SPI_Read(XDATA_L_REG, SPI_READ_TWO_REG);

      i16SensorY = SPI_Read(YDATA_L_REG, SPI_READ_TWO_REG);

      i16SensorZ = SPI_Read(ZDATA_L_REG, SPI_READ_TWO_REG);

      i16SensorT = SPI_Read(TEMP_L_REG, SPI_READ_TWO_REG);

      delay(200);
}

