/*
 * libs.h
 *
 *  Created on: Mar 3, 2021
 *      Author: VD
 */

#ifndef LIBS_H_
#define LIBS_H_

//#include "main.h"
#include "stm32f4xx_hal.h"
#include "stdint.h"
#include "stdio.h"

#define CS_LOW HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);
#define CS_HIGH HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);
//forward declaration of SPI handle struct
struct SPI_HANDLE;

typedef void (*spiActionFcnPtr)(struct SPI_HANDLE spiHandle);

typedef enum{
	NO_ACTION,
	MPU_WRITE_REG,
	MPU_READ_REG,
	MPU_READ_WHOAMI,
}SPI_ACTION;

typedef struct SPI_HANDLE{
	uint8_t tx_buff[10];
	uint8_t rx_buff[10];
	uint8_t size;
	SPI_ACTION pendingAction;
	spiActionFcnPtr actionFcn;
	spiActionFcnPtr reactionFcn;
}SPI_HANDLE_TYPE;

typedef struct MPU_HANDLE{
	uint8_t whoAmI;
	uint8_t accel_data_in[6];
	uint8_t gyro_data_in[10];
	uint8_t size;
	SPI_ACTION pendingAction;
	spiActionFcnPtr actionFcn;
	spiActionFcnPtr reactionFcn;
}MPU_HANDLE_TYPE;

extern SPI_HandleTypeDef hspi2;

SPI_HANDLE_TYPE spi2Handle;
MPU_HANDLE_TYPE mpuHandle;


void spiAction(SPI_ACTION action, uint8_t reg, uint8_t value);
void spiReaction();
void clearSpiBuff();

#endif /* LIBS_H_ */
