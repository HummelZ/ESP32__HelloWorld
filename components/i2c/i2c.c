/*
 * i2c.c
 *
 *  Created on: 19.07.2018
 *      Author: HummelZ
 */

#include "i2c.h"

SemaphoreHandle_t i2c_semaphore;

void i2c_init()
{
	i2c_config_t    i2c_config;

	i2c_config.mode             = I2C_MODE_MASTER;
	i2c_config.sda_io_num       = 21;
	i2c_config.sda_pullup_en    = GPIO_PULLUP_ENABLE;
	i2c_config.scl_io_num       = 22;
	i2c_config.scl_pullup_en    = GPIO_PULLUP_ENABLE;
	i2c_config.master.clk_speed = 100000;

	i2c_param_config( I2C_NUM_0, &i2c_config );
	i2c_driver_install( I2C_NUM_0, i2c_config.mode, 0, 0, 0 );

	i2c_semaphore = xSemaphoreCreateBinary();
}


int8_t i2c_read(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len)
{
    int8_t rslt = 0; /* Return 0 for Success, non-zero for failure */

    /*
     * The parameter dev_id can be used as a variable to store the I2C address of the device
     */

    /*
     * Data on the bus should be like
     * |------------+---------------------|
     * | I2C action | Data                |
     * |------------+---------------------|
     * | Start      | -                   |
     * | Write      | (reg_addr)          |
     * | Stop       | -                   |
     * | Start      | -                   |
     * | Read       | (reg_data[0])       |
     * | Read       | (....)              |
     * | Read       | (reg_data[len - 1]) |
     * | Stop       | -                   |
     * |------------+---------------------|
     */

    // Step 1: address slave in write mode and write register address
	i2c_cmd_handle_t cmd = i2c_cmd_link_create();
	i2c_master_start( cmd );
	// address of slave in write mode with acknowledge
	i2c_master_write_byte( cmd, (dev_id << 1) | I2C_MASTER_WRITE, true );

	// write register address with acknowledge
	i2c_master_write_byte( cmd, reg_addr, true );

	// send everything to slave
	i2c_master_stop( cmd );
	i2c_master_cmd_begin( I2C_NUM_0, cmd, 500 / portTICK_RATE_MS );
	i2c_cmd_link_delete( cmd );


	// Step 2: address slave in read mode and read register contents
	cmd = i2c_cmd_link_create();
	i2c_master_start(cmd);
	// address of slave in read mode with acknowledge
	i2c_master_write_byte( cmd, (dev_id << 1) | I2C_MASTER_READ, true );
	// read content of register
	i2c_master_read( cmd, reg_data, len, I2C_MASTER_LAST_NACK );

	// send everything to slave
	i2c_master_stop( cmd );
	i2c_master_cmd_begin( I2C_NUM_0, cmd, 500 / portTICK_RATE_MS );
	i2c_cmd_link_delete( cmd );

    return rslt;
}


int8_t i2c_write(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len)
{
	int8_t rslt = 0; /* Return 0 for Success, non-zero for failure */

	/*
	 * The parameter dev_id can be used as a variable to store the I2C address of the device
	 */

	/*
	 * Data on the bus should be like
	 * |------------+---------------------|
	 * | I2C action | Data                |
	 * |------------+---------------------|
	 * | Start      | -                   |
	 * | Write      | (reg_addr)          |
	 * | Write      | (reg_data[0])       |
	 * | Write      | (....)              |
	 * | Write      | (reg_data[len - 1]) |
	 * | Stop       | -                   |
	 * |------------+---------------------|
	 */

	// Step 1: address slave in write mode and write register address
	i2c_cmd_handle_t cmd = i2c_cmd_link_create();
	i2c_master_start( cmd );
	// address of slave in write mode with acknowledge
	i2c_master_write_byte( cmd, (dev_id << 1) | I2C_MASTER_WRITE, true );

	// Step 2: send register address
	i2c_master_write_byte( cmd, reg_addr, true );

	// Step 3: send data
	i2c_master_write( cmd, reg_data, len, true );


	// send everything to slave
	i2c_master_stop( cmd );
	i2c_master_cmd_begin( I2C_NUM_0, cmd, 500 / portTICK_RATE_MS );
	i2c_cmd_link_delete( cmd );


    return rslt;
}




void i2c_delay_ms(uint32_t period)
{
	/* Die minimale Auflösung bzw. Wartezeit ist portTICK_PERIOD_MS,
	 * darum wird die übergebene Wartezeit auf das Mindesmaß angepasst */
	uint32_t wartezeit = period < portTICK_PERIOD_MS ? portTICK_PERIOD_MS : period;
	vTaskDelay( wartezeit / portTICK_PERIOD_MS );
}

