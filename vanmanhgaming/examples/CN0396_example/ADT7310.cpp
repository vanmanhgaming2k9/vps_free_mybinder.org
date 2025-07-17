/***************************************************************************//**
 *   @file   ADT7310.c
 *   @brief  Implementation of ADT7310 Driver.
 *   @author
********************************************************************************
 * Copyright 2016(c) Analog Devices, Inc.
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
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
 * THIS SOFTWARE IS PROVIDED BY ANALOG DEVICES "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, NON-INFRINGEMENT,
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL ANALOG DEVICES BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, INTELLECTUAL PROPERTY RIGHTS, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
********************************************************************************/

#include "ADT7310.h"
#include "Communication.h"


/******************************************************************************
 * @brief Resets ADT7310.
 *
 * @param None.
 *
 * @return None.
*******************************************************************************/
void ADT7310_Reset(void)
{
   uint8_t dataToSend[4] = {0xFF, 0xFF, 0xFF, 0xFF};

   SPI_Write(dataToSend,4, ADT7310);
   delay(1);

}

/******************************************************************************
 * @brief Reads ADT7310 register value.
 *
 * @param reg - which register to read.
 * @param size - register size.
 *
 * @return uint16_t - reading result.
*******************************************************************************/
uint16_t ADT7310_ReadReg(uint8_t reg, uint8_t _size)
{
    uint8_t data[_size];
    uint16_t result = 0;

    data[0] = ADT7310_READ | (reg << 3);

    SPI_Read(data, _size, ADT7310);

    result = data[0];

    if(_size > 1){

       for(uint8_t byte = 1; byte < _size; byte++){
             result = (result << (byte * 8) | data[byte]);
       }
    }

    return result;

}

/******************************************************************************
 * @brief Writes an ADT7310 register.
 *
 * @param reg - in which register to write.
 * @param value - value to be written.
 * @param size - register size.
 *
 * @return None.
*******************************************************************************/
void ADT7310_WriteReg(uint8_t reg, uint16_t value, uint8_t _size)
{
     uint8_t data[_size + 1];
     uint8_t byte;
     uint16_t mask;

     data[0] = ADT7310_WRITE | (reg << 3);

     if(_size == 1){

           mask = 0x00FF;

        } else{

           mask = 0xFF00;
        }

     for(byte = 1; byte <= _size; byte++)
        {
           data[byte] = (uint8_t)((value & mask) >> ((_size - byte) * 8));
           mask = mask >> (byte * 8);
        }

     SPI_Write(data,(1 + _size), ADT7310);
}

/******************************************************************************
 * @brief Reads TEMP register and convert it into actual temperature.
 *
 * @param None.
 *
 * @return float - Temperature value.
*******************************************************************************/
float ADT7310_ReadTemp(void)
{
   uint16_t readData;
   float temp;

   readData = ADT7310_ReadReg(ADT7310_TEMP, 2);

   if(readData & 0x8000)
   {
     temp = (readData - 65536) / (128.0);
   }
   else
   {
     temp = readData / (128.0);
   }

   return temp;
}

/******************************************************************************
 * @brief Write setpoint value into setpoint registers.
 *
 * @param setpoint - which setpoint to write.
 * @param data - what value to write.
 *
 * @return None.
*******************************************************************************/
void ADT7310_WriteSetpoint(uint8_t setpoint, uint16_t data)
{
    ADT7310_WriteReg(setpoint, data, 2);
}

/******************************************************************************
 * @brief Start single conversion mode.
 *
 * @param None.
 *
 * @return None.
*******************************************************************************/
void ADT7310_StartSingleConversion(void)
{
    ADT7310_WriteReg(ADT7310_CONFIG, 0x20, 1);
}

