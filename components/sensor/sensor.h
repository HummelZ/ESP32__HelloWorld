/*
 * sensor.h
 *
 * Interface to one or more sensor devices. Returns valid measurement values,
 * no raw values. Setup of hardware and required communication interfaces.

 *
 *  Created on: 19.07.2018
 *      Author: HummelZ
 */

#ifndef COMPONENTS_SENSOR_SENSOR_H_
#define COMPONENTS_SENSOR_SENSOR_H_


#ifdef __cplusplus
extern "C" {
#endif

typedef struct bme280_data sensor_data_t;

sensor_data_t* sensor_get_data( void );

int32_t sensor_get_temperature( void );
uint32_t sensor_get_humidity( void );
uint32_t sensor_get_pressure( void );


void sensor_task( void * pvParameters );

#ifdef __cplusplus
}
#endif
#endif /* COMPONENTS_SENSOR_SENSOR_H_ */
