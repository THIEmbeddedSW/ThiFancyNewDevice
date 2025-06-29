/******************************************************************************
 ** COPYRIGHT:           Rudi Bauer
 ** DESCRIPTION:    	 Main module.
 ** DATE CREATED:        25.12.2022
  ******************************************************************************/

/******************************************************************************
 *  COMPILER SWITCHES
 ******************************************************************************/

/******************************************************************************
  *   INCLUDE FILES
 ******************************************************************************/
#include <Arduino.h>
#include "GlobalConfig.h"

#if (ENABLE_AVR_DEBUG == TRUE)
#include "avr8-stub.h"
#include "app_api.h"
#endif

#include "BIOS/BiosImport.h"
#include "BIOS/Bios.h"

#include "SCHEDULER/SchedulerImport.h"
#include "SCHEDULER/Scheduler.h"

#include "UI/UI.h"

#include "HT/ht.h"

/******************************************************************************
 *   DEFINES AND MACROS
 ******************************************************************************/

/******************************************************************************
 *   LOCAL VARIABLES AND CONSTANTS
 ******************************************************************************/

 /******************************************************************************
 *   EXPORTED VARIABLES AND CONSTANTS (AS EXTERN IN H-FILES)
 ******************************************************************************/
char programVersion[] = "1.0";
u8 errorCode = 0;
u16 last_time = 0;

/******************************************************************************
*   PRIVATE FUNCTIONS
******************************************************************************/

/******************************************************************************
  *   EXPORTED FUNCTIONS (AS EXTERN IN H-FILES)
 ******************************************************************************/

/********************************************************************/
// Initialization
/********************************************************************/
void setup() {

#if (ENABLE_AVR_DEBUG == TRUE)
	debug_init(); // initialize the debug interface
#endif

#if (USE_SERIAL_DEBUG == TRUE)
	BiosSerialInit(); // initialize the BIOS serial communication
#endif

	BiosIoInit(); // initialize the BIOS I/O
	BiosAdcInit(); // initialize the BIOS ADC
	BiosTimerInit(); // initialize the BIOS timer for the scheduler
	BiosWdtInit(); // initialize watchdog timer

	UI_init(); // initialize the user interface

	scd_init(); // initialize the operating system

 	ht_init(); // initialize the humidity and temperature module

	// let the system run
	BiosEnableInterrupts();

	BiosWdtService();  // Service the Watchdog for the 1st time

#if (USE_SERIAL_DEBUG == TRUE)
	Serial.println(" ");
	Serial.println("===== Welcome to THI Embedded SW version " + String(programVersion) + "=====");
	Serial.println("Init finished");
#endif
}

/*-----------------------------------------------------------------------------
 *  Implement Timer ISR Callout
 -----------------------------------------------------------------------------*/
void TimerIsrCallout(){
	scd_high_prio_tasks();
	scd_low_prio_counter();
}
/*-----------------------------------------------------------------------------
 *  Endless loop
 -----------------------------------------------------------------------------*/
void loop() {
	scd_low_prio_tasks(); // call the scheduler
	BiosWdtService();  // Service the Watchdog

}

/*-----------------------------------------------------------------------------
 *  Task 1 - high-prio
 -----------------------------------------------------------------------------*/
void task_100ms_high_prio(){
	if (errorCode > 0) BiosToggleLed(); // toggle the LED
}

/*-----------------------------------------------------------------------------
 *  Task 2
 -----------------------------------------------------------------------------*/
void task_100ms(){
	UI_100ms();
}

/*-----------------------------------------------------------------------------
 *  Task 3
 -----------------------------------------------------------------------------*/
void task_500ms(){
	if (errorCode == 0) BiosToggleLed(); // toggle the LED
}

/*-----------------------------------------------------------------------------
 *  Task 4
 -----------------------------------------------------------------------------*/
void task_1s(){
#if (USE_SERIAL_DEBUG == TRUE)
	Serial.println("System time: " + String(scd_get_system_time()) + " ms");
	last_time = scd_get_system_time();
#endif
	ht_1s(); // call the humidity & temperature process
	UI_1s();
#if (USE_SERIAL_DEBUG == TRUE)
	Serial.println("Time since: " + String(scd_time_passed(last_time)) + " ms");
#endif
}


