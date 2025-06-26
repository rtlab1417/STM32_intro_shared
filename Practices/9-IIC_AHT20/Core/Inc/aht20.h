/*
 * aht20.h
 *
 *  Created on: Jan 24, 2025
 *      Author: ASUS
 */

#ifndef INC_AHT20_H_
#define INC_AHT20_H_

#include "i2c.h"

void AHT_Init();
void AHT20_Read(float *Temperature, float *Humidity);


#endif /* INC_AHT20_H_ */
