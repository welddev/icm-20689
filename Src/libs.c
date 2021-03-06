/*
 * libs.c
 *
 *  Created on: Mar 3, 2021
 *      Author: VD
 */


#include "libs.h"
#include "main.h"


void spiAction(SPI_ACTION action, uint8_t reg, uint8_t value){
	clearSpiBuff(spi2Handle);

	spi2Handle.pendingAction = action;
	switch(action){
	case MPU_WRITE_REG:
		spi2Handle.tx_buff[0] = reg;
		spi2Handle.tx_buff[1] = value;
		HAL_SPI_Transmit_DMA(&hspi2, spi2Handle.tx_buff, 2);
		break;
	case MPU_READ_REG:
		spi2Handle.tx_buff[0] = reg;
		HAL_SPI_TransmitReceive_DMA(&hspi2, spi2Handle.tx_buff, spi2Handle.rx_buff, 2);
		break;
	case MPU_READ_WHOAMI:
		spi2Handle.tx_buff[0] = 0x75 + (1<<7);
		HAL_SPI_TransmitReceive_DMA(&hspi2, spi2Handle.tx_buff, spi2Handle.rx_buff, 2);
	default:
		break;
	}
}

void spiReaction(){
	switch(spi2Handle.pendingAction){
	case MPU_READ_WHOAMI:
		mpuHandle.whoAmI = spi2Handle.rx_buff[1];
	}
}

void clearSpiBuff(){
	uint8_t i=0;
	for(i=0; i<10; i++){
		spi2Handle.tx_buff[i] = 0;
		spi2Handle.rx_buff[i] = 0;
	}
}

void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi){
	CS_HIGH;
}

void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi){
	CS_HIGH;
}
