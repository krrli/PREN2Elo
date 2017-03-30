/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : GenI2C_ToF.h
**     Project     : PREN2-Freedom
**     Processor   : MKL25Z128VLK4
**     Component   : GenericI2C
**     Version     : Component 01.028, Driver 01.00, CPU db: 3.00.000
**     Repository  : My Components
**     Compiler    : GNU C Compiler
**     Date/Time   : 2017-03-30, 09:33, # CodeGen: 31
**     Abstract    :
**         This component implements a generic I2C driver wrapper to work both with LDD and non-LDD I2C components.
**     Settings    :
**          Component name                                 : GenI2C_ToF
**          Wait                                           : WAIT1
**          Support STOP_NOSTART                           : no
**          Write Buffer Size                              : 16
**          non-LDD I2C                                    : Disabled
**          LDD I2C                                        : Enabled
**            I2C                                          : I2C_ToF
**            Timeout                                      : Disabled
**          RTOS                                           : Disabled
**          Init() on startup                              : yes
**     Contents    :
**         SelectSlave       - uint8_t GenI2C_ToF_SelectSlave(uint8_t i2cAddr);
**         UnselectSlave     - uint8_t GenI2C_ToF_UnselectSlave(void);
**         RequestBus        - void GenI2C_ToF_RequestBus(void);
**         ReleaseBus        - void GenI2C_ToF_ReleaseBus(void);
**         WriteBlock        - uint8_t GenI2C_ToF_WriteBlock(void* data, uint16_t dataSize,...
**         ReadBlock         - uint8_t GenI2C_ToF_ReadBlock(void* data, uint16_t dataSize,...
**         ReadAddress       - uint8_t GenI2C_ToF_ReadAddress(uint8_t i2cAddr, uint8_t *memAddr, uint8_t...
**         WriteAddress      - uint8_t GenI2C_ToF_WriteAddress(uint8_t i2cAddr, uint8_t *memAddr, uint8_t...
**         ReadByteAddress8  - uint8_t GenI2C_ToF_ReadByteAddress8(uint8_t i2cAddr, uint8_t memAddr, uint8_t...
**         WriteByteAddress8 - uint8_t GenI2C_ToF_WriteByteAddress8(uint8_t i2cAddr, uint8_t memAddr,...
**         ProbeACK          - uint8_t GenI2C_ToF_ProbeACK(void* data, uint16_t dataSize,...
**         GetSemaphore      - void* GenI2C_ToF_GetSemaphore(void);
**         ScanDevice        - uint8_t GenI2C_ToF_ScanDevice(uint8_t i2cAddr);
**         Deinit            - void GenI2C_ToF_Deinit(void);
**         Init              - void GenI2C_ToF_Init(void);
**
**     * Copyright (c) 2013-2016, Erich Styger
**      * Web:         https://mcuoneclipse.com
**      * SourceForge: https://sourceforge.net/projects/mcuoneclipse
**      * Git:         https://github.com/ErichStyger/McuOnEclipse_PEx
**      * All rights reserved.
**      *
**      * Redistribution and use in source and binary forms, with or without modification,
**      * are permitted provided that the following conditions are met:
**      *
**      * - Redistributions of source code must retain the above copyright notice, this list
**      *   of conditions and the following disclaimer.
**      *
**      * - Redistributions in binary form must reproduce the above copyright notice, this
**      *   list of conditions and the following disclaimer in the documentation and/or
**      *   other materials provided with the distribution.
**      *
**      * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**      * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**      * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**      * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**      * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**      * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**      * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**      * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**      * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**      * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
** ###################################################################*/
/*!
** @file GenI2C_ToF.h
** @version 01.00
** @brief
**         This component implements a generic I2C driver wrapper to work both with LDD and non-LDD I2C components.
*/         
/*!
**  @addtogroup GenI2C_ToF_module GenI2C_ToF module documentation
**  @{
*/         

#ifndef __GenI2C_ToF_H
#define __GenI2C_ToF_H

/* MODULE GenI2C_ToF. */

/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* Include inherited beans */
#include "WAIT1.h"
#include "I2C_ToF.h"

#include "Cpu.h"


#ifndef __BWUserType_GenI2C_ToF_TTIME
#define __BWUserType_GenI2C_ToF_TTIME
  typedef struct {                     /* Time in binary format */
    byte hour;                         /* hours */
    byte min;                          /* minutes */
    byte sec;                          /* seconds */
    bool mode;                         /* clock mode, 0 for 12-hour mode, otherwise 0-24 hour mode */
    byte am_pm;                        /* 0: AM, otherwise PM */
  } GenI2C_ToF_TTIME;
#endif
#ifndef __BWUserType_GenI2C_ToF_TDATE
#define __BWUserType_GenI2C_ToF_TDATE
  typedef struct {                     /* Date in binary format */
    byte year;                         /* year */
    byte month;                        /* month */
    byte day;                          /* day */
    bool dayOfWeek;                    /* Day of week, where 0 is the first day. In the range of 0..6 */
  } GenI2C_ToF_TDATE;
#endif

#define GenI2C_ToF_WRITE_BUFFER_SIZE 16 /* size of internal buffer used, set in the component properties */

typedef enum GenI2C_ToF_EnumSendFlags_ {
  GenI2C_ToF_SEND_STOP,        /* STOP is sent */
  GenI2C_ToF_DO_NOT_SEND_STOP, /* STOP is not sent */
  GenI2C_ToF_STOP_NOSTART      /* send STOP without START condition */
} GenI2C_ToF_EnumSendFlags;

typedef enum GenI2C_ToF_EnumStartFlags_ {
  GenI2C_ToF_SEND_START,        /* Start is sent */
  GenI2C_ToF_DO_NOT_SEND_START  /* Start is not sent */
} GenI2C_ToF_EnumStartFlags;

typedef enum GenI2C_ToF_EnumAckFlags_ {
  GenI2C_ToF_SEND_LAST_ACK,   /* Nack after last received byte is sent */
  GenI2C_ToF_DO_NOT_LAST_ACK  /* Nack after last received byte is not sent */
} GenI2C_ToF_EnumAckFlags;

void I2C_ToF_OnMasterBlockSent(LDD_TUserData *UserDataPtr);

void I2C_ToF_OnMasterBlockReceived(LDD_TUserData *UserDataPtr);

void GenI2C_ToF_Init(void);
/*
** ===================================================================
**     Method      :  GenI2C_ToF_Init (component GenericI2C)
**     Description :
**         Initializes the driver.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void GenI2C_ToF_Deinit(void);
/*
** ===================================================================
**     Method      :  GenI2C_ToF_Deinit (component GenericI2C)
**     Description :
**         Deinitializes the driver.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

uint8_t GenI2C_ToF_ReadAddress(uint8_t i2cAddr, uint8_t *memAddr, uint8_t memAddrSize, uint8_t *data, uint16_t dataSize);
/*
** ===================================================================
**     Method      :  GenI2C_ToF_ReadAddress (component GenericI2C)
**     Description :
**         Read from the device. This writes (S+i2cAddr+0), (memAddr),
**         (Sr+i2cAddr+1), (data)...(data+P)
**     Parameters  :
**         NAME            - DESCRIPTION
**         i2cAddr         - I2C Address of device
**       * memAddr         - Pointer to device memory address
**         memAddrSize     - number of address bytes
**       * data            - Pointer to read buffer
**         dataSize        - Size of read buffer
**     Returns     :
**         ---             - Error code
** ===================================================================
*/

uint8_t GenI2C_ToF_WriteAddress(uint8_t i2cAddr, uint8_t *memAddr, uint8_t memAddrSize, uint8_t *data, uint16_t dataSize);
/*
** ===================================================================
**     Method      :  GenI2C_ToF_WriteAddress (component GenericI2C)
**     Description :
**         Write to the device: (S+i2cAddr+0), (memAddr), (data)...
**         (data+P)
**     Parameters  :
**         NAME            - DESCRIPTION
**         i2cAddr         - I2C address of device
**       * memAddr         - Pointer to device memory address
**         memAddrSize     - number of address bytes
**       * data            - Pointer to data write buffer
**         dataSize        - Size of data buffer in bytes
**     Returns     :
**         ---             - Error code
** ===================================================================
*/

void* GenI2C_ToF_GetSemaphore(void);
/*
** ===================================================================
**     Method      :  GenI2C_ToF_GetSemaphore (component GenericI2C)
**     Description :
**         Returns the currently allocated semaphore.
**     Parameters  : None
**     Returns     :
**         ---             - Error code
** ===================================================================
*/

uint8_t GenI2C_ToF_ReadBlock(void* data, uint16_t dataSize, GenI2C_ToF_EnumSendFlags flags);
/*
** ===================================================================
**     Method      :  GenI2C_ToF_ReadBlock (component GenericI2C)
**     Description :
**         Read from the device a block.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * data            - Read buffer
**         dataSize        - Size of read buffer
**         flags           - flags for the transaction
**     Returns     :
**         ---             - Error code
** ===================================================================
*/

uint8_t GenI2C_ToF_WriteBlock(void* data, uint16_t dataSize, GenI2C_ToF_EnumSendFlags flags);
/*
** ===================================================================
**     Method      :  GenI2C_ToF_WriteBlock (component GenericI2C)
**     Description :
**         Write a block to the device.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * data            - Data write buffer
**         dataSize        - 
**         flags           - flags for the transaction
**     Returns     :
**         ---             - Error code
** ===================================================================
*/

void GenI2C_ToF_RequestBus(void);
/*
** ===================================================================
**     Method      :  GenI2C_ToF_RequestBus (component GenericI2C)
**     Description :
**         Starts a critical section for accessing the bus.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void GenI2C_ToF_ReleaseBus(void);
/*
** ===================================================================
**     Method      :  GenI2C_ToF_ReleaseBus (component GenericI2C)
**     Description :
**         Finishes a critical section for accessing the bus.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

uint8_t GenI2C_ToF_SelectSlave(uint8_t i2cAddr);
/*
** ===================================================================
**     Method      :  GenI2C_ToF_SelectSlave (component GenericI2C)
**     Description :
**         Selects the slave device on the bus. Method might use a
**         semaphore to protect bus access.
**     Parameters  :
**         NAME            - DESCRIPTION
**         i2cAddr         - I2C Address of device
**     Returns     :
**         ---             - Error code
** ===================================================================
*/

uint8_t GenI2C_ToF_UnselectSlave(void);
/*
** ===================================================================
**     Method      :  GenI2C_ToF_UnselectSlave (component GenericI2C)
**     Description :
**         Unselects the device. Method will release a used a semaphore.
**     Parameters  : None
**     Returns     :
**         ---             - Error code
** ===================================================================
*/

uint8_t GenI2C_ToF_ReadByteAddress8(uint8_t i2cAddr, uint8_t memAddr, uint8_t *data);
/*
** ===================================================================
**     Method      :  GenI2C_ToF_ReadByteAddress8 (component GenericI2C)
**     Description :
**         Read a byte from the device using an 8bit memory address.
**         This writes (S+i2cAddr+0), (memAddr), (Sr+i2cAddr+1), (data)..
**         .(data+P)
**     Parameters  :
**         NAME            - DESCRIPTION
**         i2cAddr         - I2C Address of device
**         memAddr         - Device memory address
**       * data            - Pointer to read buffer (single byte)
**     Returns     :
**         ---             - Error code
** ===================================================================
*/

uint8_t GenI2C_ToF_WriteByteAddress8(uint8_t i2cAddr, uint8_t memAddr, uint8_t data);
/*
** ===================================================================
**     Method      :  GenI2C_ToF_WriteByteAddress8 (component GenericI2C)
**     Description :
**         Write a byte to the device using an 8bit memory address:
**         (S+i2cAddr+0), (memAddr), (data)...(data+P)
**     Parameters  :
**         NAME            - DESCRIPTION
**         i2cAddr         - I2C address of device
**         memAddr         - Device memory address
**         data            - Data value
**     Returns     :
**         ---             - Error code
** ===================================================================
*/

uint8_t GenI2C_ToF_ScanDevice(uint8_t i2cAddr);
/*
** ===================================================================
**     Method      :  GenI2C_ToF_ScanDevice (component GenericI2C)
**     Description :
**         Checks if a device responds on the bus with an ACK.
**     Parameters  :
**         NAME            - DESCRIPTION
**         i2cAddr         - 7bit I2C device address
**     Returns     :
**         ---             - Error code
** ===================================================================
*/

uint8_t GenI2C_ToF_ProbeACK(void* data, uint16_t dataSize, GenI2C_ToF_EnumSendFlags flags, uint16_t WaitTimeUS);
/*
** ===================================================================
**     Method      :  GenI2C_ToF_ProbeACK (component GenericI2C)
**     Description :
**         Accesses the bus to check if the device responds with an ACK
**         (ACK polling).
**     Parameters  :
**         NAME            - DESCRIPTION
**       * data            - Data write buffer
**         dataSize        - 
**         flags           - flags for the transaction
**         WaitTimeUS      - Waiting time in microseconds
**                           to wait for the ACK on the bus.
**     Returns     :
**         ---             - Error code
** ===================================================================
*/

/* END GenI2C_ToF. */

#endif
/* ifndef __GenI2C_ToF_H */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
