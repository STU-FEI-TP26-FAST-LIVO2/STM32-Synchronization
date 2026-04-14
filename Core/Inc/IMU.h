/*
 * IMU.h
 *
 *  Created on: Apr 8, 2026
 *      Author: Michal
 */

#ifndef INC_IMU_H_
#define INC_IMU_H_

#include "C6DOFIMU24_Registers.h"
#define C6DOFIMU24_DEVICE_ADDRESS					(0x69<<1)

extern I2C_HandleTypeDef hi2c1;

typedef struct
{
	float x;                        /**< X axis. */
	float y;                        /**< Y axis. */
	float z;                        /**< Z axis. */

} c6dofimu24_axes_t;

/**
 * @brief 6DOF IMU 24 Click data structure.
 * @details Data object definition of 6DOF IMU 24 Click driver.
 */
typedef struct
{
	c6dofimu24_axes_t gyro;         /**< Gyro data. */
	c6dofimu24_axes_t accel;        /**< Accel data. */
	float temperature;              /**< Temperature data. */

} c6dofimu24_data_t;

HAL_StatusTypeDef c6dofimu24_reset();
HAL_StatusTypeDef c6dofimu24_ping();
HAL_StatusTypeDef c6dofimu24_clear_data_ready();
HAL_StatusTypeDef c6dofimu24_set_gyro_fs_odr(uint8_t fs_sel, uint8_t odr);
HAL_StatusTypeDef c6dofimu24_set_accel_fs_odr(uint8_t fs_sel, uint8_t odr);
HAL_StatusTypeDef c6dofimu24_read_gyro(c6dofimu24_axes_t *gyro);
HAL_StatusTypeDef c6dofimu24_read_accel(c6dofimu24_axes_t *accel);
HAL_StatusTypeDef c6dofimu24_read_temperature(float *temperature);
HAL_StatusTypeDef c6dofimu24_read_data(c6dofimu24_data_t *data_out);
HAL_StatusTypeDef c6dofimu24_read_data_raw(uint8_t data_buf[14]);
HAL_StatusTypeDef c6dofimu24_default_cfg();

#endif /* INC_IMU_H_ */
