/*
 * aht20.c
 *
 *  Created on: Jan 24, 2025
 *      Author: ASUS
 */


#include "aht20.h"

#define AHT20_ADDRESS 0x70


/*
 * AHT20 initialization
 *
 * refer to AHT20 datasheet
 * initialization and criteria
 * 1. wait 40ms
 * 2. Read I2C
 * 3. check if the 3 bit is 1 == okay, if 0 then do something as instructed.
 *
 */

void AHT_Init(){
	uint8_t readBuffer;
	HAL_Delay(40);
	HAL_I2C_Master_Receive(&hi2c1, AHT20_ADDRESS, &readBuffer, 1, HAL_MAX_DELAY);
	if ((readBuffer & 0x08) == 0x00) {
		uint8_t sendBuffer[3] = {0xBE, 0x08, 0x00};	// see datasheet
		HAL_I2C_Master_Transmit(&hi2c1, AHT20_ADDRESS, sendBuffer, 3, HAL_MAX_DELAY);

	}
}

void AHT20_Read(float *Temperature, float *Humidity){
	uint8_t sendBuffer[3] = {0xAC, 0x33, 0x00};	// read command
	uint8_t readBuffer[6];	// read buffer

	HAL_I2C_Master_Transmit(&hi2c1, AHT20_ADDRESS, sendBuffer, 3, HAL_MAX_DELAY);
	HAL_Delay(75);
	HAL_I2C_Master_Receive(&hi2c1, AHT20_ADDRESS, readBuffer, 6, HAL_MAX_DELAY);
	if ((readBuffer[0] & 0x80) == 0x00) {
		uint32_t data = 0;
		// get humudity data in raw
		data = ((uint32_t)readBuffer[1]<<12) + ((uint32_t)readBuffer[2]<<4) + ((uint32_t)readBuffer[3]>>4);
		*Humidity = data * 100.0f / (1 <<20);

		// get temperature data in raw
		data = (((uint32_t)readBuffer[3] & 0x0F) <<16) + ((uint32_t)readBuffer[4]<<8) + (uint32_t)readBuffer[5];
		*Temperature = data * 200.0f / (1 <<20) - 50;
	}



}
