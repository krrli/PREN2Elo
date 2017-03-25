/* ###################################################################
**     Filename    : Events.h
**     Project     : PREN2-Freedom
**     Processor   : MKL25Z128VLK4
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2017-03-23, 10:05, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Contents    :
**         Cpu_OnNMIINT - void Cpu_OnNMIINT(void);
**
** ###################################################################*/
/*!
** @file Events.h
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         

#ifndef __Events_H
#define __Events_H
/* MODULE Events */

#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "CLS1.h"
#include "WAIT1.h"
#include "MCUC1.h"
#include "UTIL1.h"
#include "XF1.h"
#include "CS1.h"
#include "AS1.h"
#include "ASerialLdd1.h"
#include "CLS2.h"
#include "AS2.h"
#include "ASerialLdd2.h"
#include "MT1_IN1.h"
#include "MT1_IN2.h"
#include "MT1_IN3.h"
#include "MT1_IN4.h"
#include "MT2_IN1.h"
#include "MT2_IN2.h"
#include "MT2_IN3.h"
#include "MT2_IN4.h"
#include "MT1_PWM1.h"
#include "PwmLdd1.h"
#include "TPM0.h"
#include "MT1_PWM2.h"
#include "PwmLdd2.h"
#include "MT2_PWM1.h"
#include "PwmLdd3.h"
#include "MT2_PWM2.h"
#include "PwmLdd4.h"
#include "GenI2C_ToF.h"
#include "I2C_ToF.h"
#include "ToF1.h"
#include "BitIoLdd1.h"
#include "ToF2.h"
#include "BitIoLdd2.h"
#include "ToF3.h"
#include "BitIoLdd3.h"
#include "ToF4.h"
#include "BitIoLdd4.h"
#include "ToF5.h"
#include "BitIoLdd5.h"
#include "ToF6.h"
#include "BitIoLdd6.h"
#include "SW_Parc.h"
#include "BitIoLdd7.h"
#include "SW_Zent.h"
#include "BitIoLdd8.h"

#ifdef __cplusplus
extern "C" {
#endif 

/*
** ===================================================================
**     Event       :  Cpu_OnNMIINT (module Events)
**
**     Component   :  Cpu [MKL25Z128LK4]
*/
/*!
**     @brief
**         This event is called when the Non maskable interrupt had
**         occurred. This event is automatically enabled when the [NMI
**         interrupt] property is set to 'Enabled'.
*/
/* ===================================================================*/
void Cpu_OnNMIINT(void);


/*
** ===================================================================
**     Event       :  AS1_OnError (module Events)
**
**     Component   :  AS1 [AsynchroSerial]
**     Description :
**         This event is called when a channel error (not the error
**         returned by a given method) occurs. The errors can be read
**         using <GetError> method.
**         The event is available only when the <Interrupt
**         service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void AS1_OnError(void);

/*
** ===================================================================
**     Event       :  AS1_OnRxChar (module Events)
**
**     Component   :  AS1 [AsynchroSerial]
**     Description :
**         This event is called after a correct character is received.
**         The event is available only when the <Interrupt
**         service/event> property is enabled and either the <Receiver>
**         property is enabled or the <SCI output mode> property (if
**         supported) is set to Single-wire mode.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void AS1_OnRxChar(void);

/*
** ===================================================================
**     Event       :  AS1_OnTxChar (module Events)
**
**     Component   :  AS1 [AsynchroSerial]
**     Description :
**         This event is called after a character is transmitted.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void AS1_OnTxChar(void);

/*
** ===================================================================
**     Event       :  AS2_OnError (module Events)
**
**     Component   :  AS2 [AsynchroSerial]
**     Description :
**         This event is called when a channel error (not the error
**         returned by a given method) occurs. The errors can be read
**         using <GetError> method.
**         The event is available only when the <Interrupt
**         service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void AS2_OnError(void);

/*
** ===================================================================
**     Event       :  AS2_OnRxChar (module Events)
**
**     Component   :  AS2 [AsynchroSerial]
**     Description :
**         This event is called after a correct character is received.
**         The event is available only when the <Interrupt
**         service/event> property is enabled and either the <Receiver>
**         property is enabled or the <SCI output mode> property (if
**         supported) is set to Single-wire mode.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void AS2_OnRxChar(void);

/*
** ===================================================================
**     Event       :  AS2_OnTxChar (module Events)
**
**     Component   :  AS2 [AsynchroSerial]
**     Description :
**         This event is called after a character is transmitted.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void AS2_OnTxChar(void);

/* END Events */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

#endif 
/* ifndef __Events_H*/
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
