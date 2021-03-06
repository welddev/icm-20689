/*
* File Name: mpu.c
*
* Code generated for mpu using API: v0.1.12.
*
* Author						: <author>	
* Application Version			: <appVersion>
* C source code generated on    : Fri, 05 Mar 2021 19:14:56 GMT
*
*/

//Include user defined headers.
#include "main.h"
#include "stm32f4xx_it.h"
#include "libs.h"

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
	switch(wS_mpu_master){
		case wS_IN_start:
			if(wD_TIMER_COMPARE(wT_TIMER1, 999)){
				spi2Handle.tx_buff[0] = 0x6B;
				spi2Handle.tx_buff[1] = 0x80;
				CS_LOW;
				HAL_SPI_Transmit_DMA(&hspi2, spi2Handle.tx_buff, 2);
				wD_TIMER_RESET(wT_TIMER1);
				wS_mpu_master = wS_IN_init_299;
			}else{
				wD_TIMER_INCREMENT(wT_TIMER1);
			}
			break;
		case wS_IN_init_299:
			if(wD_TIMER_COMPARE(wT_TIMER1, 999)){
				spi2Handle.tx_buff[0] = 0x6A;
				spi2Handle.tx_buff[1] = 1<<4;
				CS_LOW;
				HAL_SPI_Transmit_DMA(&hspi2, spi2Handle.tx_buff, 2);
				wD_TIMER_RESET(wT_TIMER1);
				wS_mpu_master = wS_IN_State595;
			}else{
				wD_TIMER_INCREMENT(wT_TIMER1);
			}
			break;
		case wS_IN_State595:
			if(wD_TIMER_COMPARE(wT_TIMER1, 999)){
				spi2Handle.tx_buff[0] = 0x75 + (1<<7);
				spi2Handle.tx_buff[1] = 0;
				CS_LOW;
				HAL_SPI_TransmitReceive_DMA(&hspi2, spi2Handle.tx_buff, spi2Handle.rx_buff, 2);
				wD_TIMER_RESET(wT_TIMER1);
				wS_mpu_master = wS_IN_State703;
			}else{
				wD_TIMER_INCREMENT(wT_TIMER1);
			}
			break;
		case wS_IN_State703:
			if(wD_TIMER_COMPARE(wT_TIMER1, 999)){
				spi2Handle.tx_buff[0] = 0x75 + (1<<7);
				spi2Handle.tx_buff[1] = 0;
				CS_LOW;
				HAL_SPI_TransmitReceive_DMA(&hspi2, spi2Handle.tx_buff, spi2Handle.rx_buff, 2);
				wD_TIMER_RESET(wT_TIMER1);
			}else{
				wD_TIMER_INCREMENT(wT_TIMER1);
			}
			break;
		default:
			
			wD_TIMER_RESET(wT_TIMER1);
			wS_mpu_master = wS_IN_start;
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
