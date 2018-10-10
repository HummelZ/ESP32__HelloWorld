/*
 * sensor.c
 *
 *  Created on: 19.07.2018
 *      Author: HummelZ
 */

#include "sensor.h"


struct {
	struct bme280_dev 	device;
	struct bme280_data 	comp_data;
} bme280;


static void sensor_init();
static void sensor_run( void );


static void sensor_init( void )
{
	uint8_t settings_sel;

	bme280.device.dev_id 	= BME280_I2C_ADDR_PRIM;
	bme280.device.intf 		= BME280_I2C_INTF;
	bme280.device.read 		= i2c_read;
	bme280.device.write 	= i2c_write;
	bme280.device.delay_ms 	= i2c_delay_ms;

	bme280_init(&bme280.device);

	/* Recommended mode of operation: Indoor navigation */
	bme280.device.settings.osr_h 		= BME280_OVERSAMPLING_1X;
	bme280.device.settings.osr_p 		= BME280_OVERSAMPLING_16X;
	bme280.device.settings.osr_t 		= BME280_OVERSAMPLING_2X;
	bme280.device.settings.filter 		= BME280_FILTER_COEFF_16;
	bme280.device.settings.standby_time = BME280_STANDBY_TIME_62_5_MS;

	settings_sel 	 = BME280_OSR_PRESS_SEL;
	settings_sel	|= BME280_OSR_TEMP_SEL;
	settings_sel 	|= BME280_OSR_HUM_SEL;
	settings_sel 	|= BME280_STANDBY_SEL;
	settings_sel 	|= BME280_FILTER_SEL;

	bme280_set_sensor_settings(settings_sel, &bme280.device);
	bme280_set_sensor_mode(BME280_NORMAL_MODE, &bme280.device);
}


static void sensor_run( void )
{
	/* take i2c_semaphore to get exclusive access to i2c-interface */
	xSemaphoreTake(i2c_semaphore, 100);

	/* now interface the sensor and get data */
	bme280_get_sensor_data(BME280_ALL, &bme280.comp_data, &bme280.device);

	/* give back the i2c-interface lock */
	xSemaphoreGive(i2c_semaphore);

	//printf("%d, %d, %d\r\n", bme280.comp_data.temperature, bme280.comp_data.pressure, bme280.comp_data.humidity);
	//printf("%0.2f, %0.2f, %0.2f\r\n",comp_data.temperature, comp_data.pressure, comp_data.humidity);
}


sensor_data_t* sensor_get_data( void )
{

	return (sensor_data_t *)&bme280.comp_data;
}

int32_t sensor_get_temperature( void )
{
	return bme280.comp_data.temperature;
}


uint32_t sensor_get_humidity( void )
{
	return bme280.comp_data.humidity;
}


uint32_t sensor_get_pressure( void )
{
	return bme280.comp_data.pressure;
}


void sensor_task( void * pvParameters )
{
	sensor_init();

	while ( 1 )
	{
		sensor_run();

		vTaskDelay( 1000  / portTICK_PERIOD_MS );
	}
}
