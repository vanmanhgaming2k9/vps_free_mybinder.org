/**
*   @file     ADT7310.h
*   @brief    Header file for ADT7310.
*   @author   Analog Devices Inc.
*
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
#ifndef ADT7310_H
#define ADT7310_H

#include <stdint.h>

#ifdef  __cplusplus
extern "C" {
#endif

#define ADT7310_READ (1<<6)
#define ADT7310_WRITE (0)
#define ADT7310_DUMMY (0)
#define ADT7310_STATUS (0)
#define ADT7310_CONFIG (1)
#define ADT7310_TEMP  (2)
#define ADT7310_ID    (3)
#define ADT7310_TCRIT (4)
#define ADT7310_THYST (5)
#define ADT7310_THIGH (6)
#define ADT7310_TLOW  (7)


 void ADT7310_Reset(void);
 uint16_t ADT7310_ReadReg(uint8_t reg, uint8_t _size);
 void ADT7310_WriteReg(uint8_t reg, uint16_t value, uint8_t _size);
 float ADT7310_ReadTemp(void);
 void ADT7310_WriteSetpoint(uint8_t setpoint, uint16_t data);
 void ADT7310_StartSingleConversion(void);
 uint8_t ADT7310_Ready(void);

#ifdef  __cplusplus
}
#endif // __cplusplus

#endif
