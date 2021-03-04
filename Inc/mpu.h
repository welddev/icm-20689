/*
* File Name: mpu.h
*
* Code generated for mpu using API: v0.1.12.
*
* Author						: <author>	
* Application Version			: <appVersion>
* C source code generated on    : Thu, 04 Mar 2021 17:36:49 GMT
*
*/

#include "stdint.h"


//Max value that a timer can keep
#ifndef wD_TIMER_MAX
#define wD_TIMER_MAX(x)  (~(x & 0x0))
#endif

//Increment the timer
#ifndef wD_TIMER_INCREMENT
#define wD_TIMER_INCREMENT(x)   ((++x) ? x : --x)
#endif

//Increment and compare the timer
#ifndef wD_TIMER_INCCOMP
#define wD_TIMER_INCCOMP(x, y)  (wD_TIMER_INCREMENT(x) >= y)
#endif

//Reset the timer
#ifndef wD_TIMER_RESET
#define wD_TIMER_RESET(x)  (x = 0x0)
#endif

//Compare the timer with a reference time
#ifndef wD_TIMER_COMPARE
#define wD_TIMER_COMPARE(x, y)  (x >= y)
#endif


//8-bit timer type definition
typedef uint8_t     wT_TIMER8; 

//16-bit timer type definition
typedef uint16_t    wT_TIMER16;

//32-bit timer type definition
typedef uint32_t    wT_TIMER32;

//64-bit timer type definition
typedef uint64_t    wT_TIMER64;



typedef enum{
	wS_INACTIVE= 0,
	wS_IN_init,
	wS_IN_wait,
	wS_IN_State101,
	wS_IN_mpu_master,
	wS_IN_start,
	wS_IN_init_299,
	wS_IN_blink,
	wS_IN_State383,
}Active_State;

void wF_init(void);

void run_app_1000hz(void);
void run_spi_master_nonehz(void);
