/*
 * i2c.h
 *
 *  Created on: 19.07.2018
 *      Author: HummelZ
 */

#ifndef COMPONENTS_I2C_I2C_H_
#define COMPONENTS_I2C_I2C_H_


#include <inttypes.h>
#include <stdbool.h>
#include "driver/i2c.h"

#ifdef __cplusplus
extern "C" {
#endif



extern SemaphoreHandle_t i2c_semaphore;

void i2c_init();


int8_t i2c_read(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len);


int8_t i2c_write(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len);


void i2c_delay_ms(uint32_t period);


#ifdef __cplusplus
}
#endif
#endif /* COMPONENTS_I2C_I2C_H_ */
