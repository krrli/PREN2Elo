/* ###################################################################
**     Filename    : main.c
**     Project     : PREN2-Freedom
**     Processor   : MKL25Z128VLK4
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2017-03-23, 10:05, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.01
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
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
#include "MT1_IN1.h"
#include "BitIoLdd9.h"
#include "MT1_IN2.h"
#include "BitIoLdd10.h"
#include "MT1_IN3.h"
#include "BitIoLdd11.h"
#include "MT1_IN4.h"
#include "BitIoLdd12.h"
#include "MT2_IN1.h"
#include "BitIoLdd13.h"
#include "MT2_IN2.h"
#include "BitIoLdd14.h"
#include "MT2_IN3.h"
#include "BitIoLdd15.h"
#include "MT2_IN4.h"
#include "BitIoLdd16.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* User includes (#include below this line is not maintained by Processor Expert) */

#include "program.h"
#include "test.h"

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  /* For example: for(;;) { } */
WAIT1_Waitms(1000);
  starttest();
  start();

  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
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
