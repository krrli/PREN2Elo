/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : GenI2C_ToF.c
**     Project     : PREN2-Freedom
**     Processor   : MKL25Z128VLK4
**     Component   : GenericI2C
**     Version     : Component 01.028, Driver 01.00, CPU db: 3.00.000
**     Repository  : My Components
**     Compiler    : GNU C Compiler
**     Date/Time   : 2017-03-24, 16:17, # CodeGen: 14
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
** @file GenI2C_ToF.c
** @version 01.00
** @brief
**         This component implements a generic I2C driver wrapper to work both with LDD and non-LDD I2C components.
*/         
/*!
**  @addtogroup GenI2C_ToF_module GenI2C_ToF module documentation
**  @{
*/         

/* MODULE GenI2C_ToF. */

#include "GenI2C_ToF.h"
#ifndef NULL
  #define NULL 0L
#endif /* NULL */

typedef struct {
  volatile bool dataReceivedFlg; /* set to TRUE by the interrupt if we have received data */
  volatile bool dataTransmittedFlg; /* set to TRUE by the interrupt if we have set data */
  LDD_TDeviceData *handle; /* pointer to the device handle */
} GenI2C_ToF_TDataState;

static GenI2C_ToF_TDataState GenI2C_ToF_deviceData;

/*
** ===================================================================
**     Method      :  GenI2C_ToF_RequestBus (component GenericI2C)
**     Description :
**         Starts a critical section for accessing the bus.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void GenI2C_ToF_RequestBus(void)
{
  /*lint -save -e522 function lacks side effect  */
  /*lint -restore */
}

/*
** ===================================================================
**     Method      :  GenI2C_ToF_ReleaseBus (component GenericI2C)
**     Description :
**         Finishes a critical section for accessing the bus.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void GenI2C_ToF_ReleaseBus(void)
{
  /*lint -save -e522 function lacks side effect  */
  /*lint -restore */
}

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
uint8_t GenI2C_ToF_SelectSlave(uint8_t i2cAddr)
{
  if (I2C_ToF_SelectSlaveDevice(GenI2C_ToF_deviceData.handle, LDD_I2C_ADDRTYPE_7BITS, i2cAddr)!=ERR_OK) {
    return ERR_FAILED;
  }
  return ERR_OK;
}

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
uint8_t GenI2C_ToF_UnselectSlave(void)
{
  return ERR_OK;
}

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
uint8_t GenI2C_ToF_ReadBlock(void* data, uint16_t dataSize, GenI2C_ToF_EnumSendFlags flags)
{
  uint8_t res = ERR_OK;

  for(;;) { /* breaks */
    GenI2C_ToF_deviceData.dataReceivedFlg = FALSE;
    res = I2C_ToF_MasterReceiveBlock(GenI2C_ToF_deviceData.handle, data, dataSize, flags==GenI2C_ToF_SEND_STOP?LDD_I2C_SEND_STOP:LDD_I2C_NO_SEND_STOP);
    if (res!=ERR_OK) {
      break; /* break for(;;) */
    }
    do { /* Wait until data is received */
    } while (!GenI2C_ToF_deviceData.dataReceivedFlg);
    break; /* break for(;;) */
  } /* for(;;) */
  return res;
}

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
uint8_t GenI2C_ToF_WriteBlock(void* data, uint16_t dataSize, GenI2C_ToF_EnumSendFlags flags)
{
  uint8_t res = ERR_OK;

  for(;;) { /* breaks */
    GenI2C_ToF_deviceData.dataTransmittedFlg = FALSE;
    res = I2C_ToF_MasterSendBlock(GenI2C_ToF_deviceData.handle, data, dataSize, flags==GenI2C_ToF_SEND_STOP?LDD_I2C_SEND_STOP:LDD_I2C_NO_SEND_STOP);
    if (res!=ERR_OK) {
      break; /* break for(;;) */
    }
    do { /* Wait until data is sent */
    } while (!GenI2C_ToF_deviceData.dataTransmittedFlg);
    break; /* break for(;;) */
  } /* for(;;) */
  return res;
}

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
uint8_t GenI2C_ToF_ReadAddress(uint8_t i2cAddr, uint8_t *memAddr, uint8_t memAddrSize, uint8_t *data, uint16_t dataSize)
{
  uint8_t res = ERR_OK;

  if (GenI2C_ToF_SelectSlave(i2cAddr)!=ERR_OK) {
    return ERR_FAILED;
  }
  for(;;) { /* breaks */
    if(memAddr!=NULL) { /* only if we want to send an address */
      /* send device address and memory address */
      GenI2C_ToF_deviceData.dataTransmittedFlg = FALSE;
      res = I2C_ToF_MasterSendBlock(GenI2C_ToF_deviceData.handle, memAddr, memAddrSize, LDD_I2C_NO_SEND_STOP);
      if (res!=ERR_OK) {
        break; /* break for(;;) */
      }
    }
    do { /* Wait until data is sent */
    } while (!GenI2C_ToF_deviceData.dataTransmittedFlg);
    /* receive data */
    GenI2C_ToF_deviceData.dataReceivedFlg = FALSE;
    res = I2C_ToF_MasterReceiveBlock(GenI2C_ToF_deviceData.handle, data, dataSize, LDD_I2C_SEND_STOP);
    if (res!=ERR_OK) {
      break; /* break for(;;) */
    }
    do { /* Wait until data is received */
    } while (!GenI2C_ToF_deviceData.dataReceivedFlg);
    break; /* break for(;;) */
  } /* for(;;) */
  if (GenI2C_ToF_UnselectSlave()!=ERR_OK) {
    return ERR_FAILED;
  }
  return res;
}

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
uint8_t GenI2C_ToF_WriteAddress(uint8_t i2cAddr, uint8_t *memAddr, uint8_t memAddrSize, uint8_t *data, uint16_t dataSize)
{
  static uint8_t writeBuf[GenI2C_ToF_WRITE_BUFFER_SIZE];
  uint8_t *p;
  uint16_t i;
  uint8_t res = ERR_OK;

  if (GenI2C_ToF_SelectSlave(i2cAddr)!=ERR_OK) {
    return ERR_FAILED;
  }
  if (memAddrSize+dataSize>GenI2C_ToF_WRITE_BUFFER_SIZE) {
    return ERR_FAILED;
  }
  i = 0; p = memAddr;
  while(i<GenI2C_ToF_WRITE_BUFFER_SIZE && memAddrSize>0) {
    writeBuf[i++] = *p++;
    memAddrSize--;
  }
  p = data;
  while(i<GenI2C_ToF_WRITE_BUFFER_SIZE && dataSize>0) {
    writeBuf[i++] = *p++;
    dataSize--;
  }
  for(;;) { /* breaks */
    /* send device address, memory address and data */
    GenI2C_ToF_deviceData.dataTransmittedFlg = FALSE;
    if (I2C_ToF_MasterSendBlock(GenI2C_ToF_deviceData.handle, writeBuf, i, LDD_I2C_SEND_STOP)!=ERR_OK) {
      break; /* break for(;;) */
    }
    do { /* Wait until data is sent */
    } while (!GenI2C_ToF_deviceData.dataTransmittedFlg);
    break; /* break for(;;) */
  } /* for(;;) */
  if (GenI2C_ToF_UnselectSlave()!=ERR_OK) {
    return ERR_FAILED;
  }
  return res;
}

/*
** ===================================================================
**     Method      :  GenI2C_ToF_OnMasterBlockSent (component GenericI2C)
**
**     Description :
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void I2C_ToF_OnMasterBlockSent(LDD_TUserData *UserDataPtr)
{
  if (UserDataPtr==&GenI2C_ToF_deviceData) { /* it is our own message */
    GenI2C_ToF_TDataState *devicePtr = (GenI2C_ToF_TDataState*)UserDataPtr;

    devicePtr->dataTransmittedFlg = TRUE;
  }
}

/*
** ===================================================================
**     Method      :  GenI2C_ToF_OnMasterBlockReceived (component GenericI2C)
**
**     Description :
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void I2C_ToF_OnMasterBlockReceived(LDD_TUserData *UserDataPtr)
{
  if (UserDataPtr==&GenI2C_ToF_deviceData) { /* it is our own message */
    GenI2C_ToF_TDataState *devicePtr = (GenI2C_ToF_TDataState*)UserDataPtr;

    devicePtr->dataReceivedFlg = TRUE;
  }
}

/*
** ===================================================================
**     Method      :  GenI2C_ToF_Init (component GenericI2C)
**     Description :
**         Initializes the driver.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void GenI2C_ToF_Init(void)
{
  GenI2C_ToF_deviceData.handle = I2C_ToF_Init(&GenI2C_ToF_deviceData);
  if (GenI2C_ToF_deviceData.handle==NULL) {
    for(;;){} /* failure! */
  }
}

/*
** ===================================================================
**     Method      :  GenI2C_ToF_Deinit (component GenericI2C)
**     Description :
**         Deinitializes the driver.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void GenI2C_ToF_Deinit(void)
{
  I2C_ToF_Deinit(&GenI2C_ToF_deviceData);
}

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
void* GenI2C_ToF_GetSemaphore(void)
{
  return NULL; /* RTOS and Semaphore enabled in properties */
}

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
uint8_t GenI2C_ToF_ReadByteAddress8(uint8_t i2cAddr, uint8_t memAddr, uint8_t *data)
{
  return GenI2C_ToF_ReadAddress(i2cAddr, &memAddr, sizeof(memAddr), data, 1);
}

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
uint8_t GenI2C_ToF_WriteByteAddress8(uint8_t i2cAddr, uint8_t memAddr, uint8_t data)
{
  return GenI2C_ToF_WriteAddress(i2cAddr, &memAddr, sizeof(memAddr), &data, 1);
}

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
uint8_t GenI2C_ToF_ScanDevice(uint8_t i2cAddr)
{
  uint8_t res = ERR_OK;
  LDD_I2C_TErrorMask errMask;
  uint8_t dummy;

  if (GenI2C_ToF_SelectSlave(i2cAddr)!=ERR_OK) {
    return ERR_FAILED;
  }
  for(;;) { /* breaks */
    /* send device address */
    GenI2C_ToF_deviceData.dataTransmittedFlg = FALSE;
    res = I2C_ToF_MasterReceiveBlock(GenI2C_ToF_deviceData.handle, &dummy, 1, LDD_I2C_SEND_STOP);
    if (res!=ERR_OK) {
      break; /* break for(;;) */
    }
    do { /* Wait until data is sent */
    } while (!GenI2C_ToF_deviceData.dataTransmittedFlg);
    errMask = 0;
    (void)I2C_ToF_GetError(GenI2C_ToF_deviceData.handle, &errMask);
    if (errMask&LDD_I2C_MASTER_NACK) { /* master did not receive ACK from slave */
      res = ERR_NOTAVAIL; /* device did not respond with ACK */
    }
    break; /* break for(;;) */
  } /* for(;;) */
  if (GenI2C_ToF_UnselectSlave()!=ERR_OK) {
    return ERR_FAILED;
  }
  return res;
}

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
uint8_t GenI2C_ToF_ProbeACK(void* data, uint16_t dataSize, GenI2C_ToF_EnumSendFlags flags, uint16_t WaitTimeUS)
{
  uint8_t res = ERR_OK;

  GenI2C_ToF_deviceData.dataTransmittedFlg = FALSE;
  res = I2C_ToF_MasterSendBlock(GenI2C_ToF_deviceData.handle, data, dataSize, flags==GenI2C_ToF_SEND_STOP?LDD_I2C_SEND_STOP:LDD_I2C_NO_SEND_STOP);
  if (res!=ERR_OK) {
    return res;
  }
  /*lint -save -e522 Lacks side effect */
  WAIT1_Waitus(WaitTimeUS);
  /*lint -restore */
  if (!GenI2C_ToF_deviceData.dataTransmittedFlg) {
    return ERR_FAILED; /* no ACK received? */
  }
  return res;
}

/* END GenI2C_ToF. */

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
