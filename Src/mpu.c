/*
* File Name: mpu.c
*
* Code generated for mpu using API: v0.1.12.
*
* Author						: <author>	
* Application Version			: <appVersion>
* C source code generated on    : Thu, 04 Mar 2021 17:36:49 GMT
*
*/

//Include user defined headers.
#include "main.h"

//Include generated header.
#include "mpu.h"

static wT_TIMER16 wT_TIMER1;
static wT_TIMER8 wT_TIMER2;

static Active_State wS_app = wS_INACTIVE;
static Active_State wS_spi_master = wS_INACTIVE;
static Active_State wS_mpu_master = wS_INACTIVE;
static Active_State wS_blink = wS_INACTIVE;


/*
* This function initializes the variables that are required
* for the operation of generated code.
* This function should be called once before the main thread function
* is called. Please include the generated headers in your main.c file and 
* call this function before initializing the peripherals.
*/
void wF_init(void){
}

void run_app_1000hz(void){
	switch(wS_mpu_master){
		case wS_IN_start:
			if(wD_TIMER_COMPARE(wT_TIMER1, 999)){
				wS_mpu_master = wS_IN_init_299;
			}else{
				wD_TIMER_INCREMENT(wT_TIMER1);
			}
			break;
		case wS_IN_init_299:
			break;
		default:
			
			wD_TIMER_RESET(wT_TIMER1);
			wS_mpu_master = wS_IN_start;
	}
	switch(wS_blink){
		case wS_IN_State383:
			if(wD_TIMER_COMPARE(wT_TIMER2, 99)){
				HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
				wD_TIMER_RESET(wT_TIMER2);
			}else{
				wD_TIMER_INCREMENT(wT_TIMER2);
			}
			break;
		default:
			
			HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
			wD_TIMER_RESET(wT_TIMER2);
			wS_blink = wS_IN_State383;
	}

}
void run_spi_master_nonehz(void){
	switch(wS_spi_master){
		case wS_IN_init:
			wS_spi_master = wS_IN_wait;
			break;
		case wS_IN_wait:
			wS_spi_master = wS_IN_State101;
			break;
		case wS_IN_State101:
			break;
		default:
			
			wS_spi_master = wS_IN_init;
	}

}
