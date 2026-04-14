/*
 * IMU.c
 *
 *  Created on: Apr 8, 2026
 *      Author: Michal
 */
#include "stm32f1xx_hal.h"
#include "C6DOFIMU24_Registers.h"
#include "IMU.h"


float gyro_sens;
float accel_sens;

HAL_StatusTypeDef c6dofimu24_reset()
{
	// Reset device
	uint8_t data_write = C6DOFIMU24_DEVICE_CONFIG_SOFT_RESET;
	HAL_StatusTypeDef status = HAL_I2C_Mem_Write
					(&hi2c1,
					C6DOFIMU24_DEVICE_ADDRESS,
					C6DOFIMU24_REG0_DEVICE_CONFIG,
					1,
					&data_write,
					1,
					100);

	if(status != HAL_OK)
		return status;

	HAL_Delay(100);

	uint8_t data_read = 0;
	status = HAL_I2C_Mem_Read
					(&hi2c1,
					C6DOFIMU24_DEVICE_ADDRESS,
					C6DOFIMU24_REG0_INT_STATUS,
					1,
					&data_read,
					1,
					100);

	if(status != HAL_OK)
		return status;

	if(data_read & C6DOFIMU24_INT_STATUS_RESET_DONE)
		return HAL_OK;

	return HAL_ERROR;
}

HAL_StatusTypeDef c6dofimu24_ping()
{
    uint8_t who_am_i = 0;

    HAL_StatusTypeDef status = HAL_I2C_Mem_Read(
                                &hi2c1,
                                C6DOFIMU24_DEVICE_ADDRESS,
                                C6DOFIMU24_REG0_WHO_AM_I,
                                1,
                                &who_am_i,
                                1,
                                100);

    if (status != HAL_OK)
        return status;

    if (who_am_i == C6DOFIMU24_WHO_AM_I)
        return HAL_OK;

    return HAL_ERROR;
}

HAL_StatusTypeDef c6dofimu24_clear_data_ready()
{
    uint8_t status = 0;

    return HAL_I2C_Mem_Read(
                &hi2c1,
                C6DOFIMU24_DEVICE_ADDRESS,
                C6DOFIMU24_REG0_INT_STATUS,
                1,
                &status,
                1,
                100);
}

HAL_StatusTypeDef c6dofimu24_set_gyro_fs_odr(uint8_t fs_sel, uint8_t odr)
{
    uint8_t reg_data = 0;

    if ((fs_sel > C6DOFIMU24_GYRO_FS_SEL_2000DPS) || (odr > C6DOFIMU24_GYRO_ODR_32000HZ))
        return HAL_ERROR;

    HAL_StatusTypeDef status = HAL_I2C_Mem_Read(
                                &hi2c1,
                                C6DOFIMU24_DEVICE_ADDRESS,
                                C6DOFIMU24_REG0_GYRO_CONFIG0,
                                1,
                                &reg_data,
                                1,
                                100);

    if (status != HAL_OK)
        return status;

    reg_data &= ~(C6DOFIMU24_GYRO_CONFIG0_FS_SEL_MASK | C6DOFIMU24_GYRO_CONFIG0_ODR_MASK);
    reg_data |= (((C6DOFIMU24_GYRO_FS_SEL_2000DPS - fs_sel) << 5) & C6DOFIMU24_GYRO_CONFIG0_FS_SEL_MASK);

    if (odr < C6DOFIMU24_GYRO_ODR_500HZ)
    {
        reg_data |= ((C6DOFIMU24_GYRO_CONFIG0_ODR_12_5HZ - odr) & C6DOFIMU24_GYRO_CONFIG0_ODR_MASK);
    }
    else if (odr > C6DOFIMU24_GYRO_ODR_500HZ)
    {
        reg_data |= ((C6DOFIMU24_GYRO_CONFIG0_ODR_12_5HZ - odr + 1) & C6DOFIMU24_GYRO_CONFIG0_ODR_MASK);
    }
    else
    {
        reg_data |= C6DOFIMU24_GYRO_CONFIG0_ODR_500HZ;
    }

    status = HAL_I2C_Mem_Write(
                &hi2c1,
                C6DOFIMU24_DEVICE_ADDRESS,
                C6DOFIMU24_REG0_GYRO_CONFIG0,
                1,
                &reg_data,
                1,
                100);

    if (status != HAL_OK)
        return status;

    gyro_sens = (float)C6DOFIMU24_GYRO_DATA_RES / (C6DOFIMU24_GYRO_MIN_DPS * (1 << fs_sel));

    return HAL_OK;
}

HAL_StatusTypeDef c6dofimu24_set_accel_fs_odr(uint8_t fs_sel, uint8_t odr)
{
    uint8_t reg_data = 0;

    if ((fs_sel > C6DOFIMU24_ACCEL_FS_SEL_32G) || (odr > C6DOFIMU24_ACCEL_ODR_32000HZ))
        return HAL_ERROR;

    HAL_StatusTypeDef status = HAL_I2C_Mem_Read(
                                &hi2c1,
                                C6DOFIMU24_DEVICE_ADDRESS,
                                C6DOFIMU24_REG0_ACCEL_CONFIG0,
                                1,
                                &reg_data,
                                1,
                                100);

    if (status != HAL_OK)
        return status;

    reg_data &= ~(C6DOFIMU24_ACCEL_CONFIG0_FS_SEL_MASK | C6DOFIMU24_ACCEL_CONFIG0_ODR_MASK);
    reg_data |= (((C6DOFIMU24_ACCEL_FS_SEL_32G - fs_sel) << 5) & C6DOFIMU24_ACCEL_CONFIG0_FS_SEL_MASK);

    if (odr < C6DOFIMU24_ACCEL_ODR_500HZ)
    {
        reg_data |= ((C6DOFIMU24_ACCEL_CONFIG0_ODR_1_5625HZ - odr) & C6DOFIMU24_GYRO_CONFIG0_ODR_MASK);
    }
    else if (odr > C6DOFIMU24_ACCEL_ODR_500HZ)
    {
        reg_data |= ((C6DOFIMU24_ACCEL_CONFIG0_ODR_1_5625HZ - odr + 1) & C6DOFIMU24_GYRO_CONFIG0_ODR_MASK);
    }
    else
    {
        reg_data |= C6DOFIMU24_ACCEL_CONFIG0_ODR_500HZ;
    }

    status = HAL_I2C_Mem_Write(
                &hi2c1,
                C6DOFIMU24_DEVICE_ADDRESS,
                C6DOFIMU24_REG0_ACCEL_CONFIG0,
                1,
                &reg_data,
                1,
                100);

    if (status != HAL_OK)
        return status;

    accel_sens = (float)C6DOFIMU24_ACCEL_DATA_RES / (C6DOFIMU24_ACCEL_MIN_G << fs_sel);

    return HAL_OK;
}

HAL_StatusTypeDef c6dofimu24_read_gyro(c6dofimu24_axes_t *gyro)
{
    uint8_t data_buf[6] = {0};

    HAL_StatusTypeDef status = HAL_I2C_Mem_Read(
                                &hi2c1,
                                C6DOFIMU24_DEVICE_ADDRESS,
                                C6DOFIMU24_REG0_GYRO_DATA_X1,
                                1,
                                data_buf,
                                6,
                                100);

    if (status != HAL_OK)
        return status;

    int16_t raw_data;

    raw_data = ((int16_t)data_buf[0] << 8) | data_buf[1];
    gyro->x = (float)raw_data / gyro_sens;

    raw_data = ((int16_t)data_buf[2] << 8) | data_buf[3];
    gyro->y = (float)raw_data / gyro_sens;

    raw_data = ((int16_t)data_buf[4] << 8) | data_buf[5];
    gyro->z = (float)raw_data / gyro_sens;

    return HAL_OK;
}

HAL_StatusTypeDef c6dofimu24_read_accel(c6dofimu24_axes_t *accel)
{
    uint8_t data_buf[6] = {0};

    HAL_StatusTypeDef status = HAL_I2C_Mem_Read(
                                &hi2c1,
                                C6DOFIMU24_DEVICE_ADDRESS,
                                C6DOFIMU24_REG0_ACCEL_DATA_X1,
                                1,
                                data_buf,
                                6,
                                100);

    if (status != HAL_OK)
        return status;

    int16_t raw_data;

    raw_data = ((int16_t)data_buf[0] << 8) | data_buf[1];
    accel->x = (float)raw_data / accel_sens;

    raw_data = ((int16_t)data_buf[2] << 8) | data_buf[3];
    accel->y = (float)raw_data / accel_sens;

    raw_data = ((int16_t)data_buf[4] << 8) | data_buf[5];
    accel->z = (float)raw_data / accel_sens;

    return HAL_OK;
}

HAL_StatusTypeDef c6dofimu24_read_temperature(float *temperature)
{
    uint8_t data_buf[2] = {0};

    HAL_StatusTypeDef status = HAL_I2C_Mem_Read(
                                &hi2c1,
                                C6DOFIMU24_DEVICE_ADDRESS,
                                C6DOFIMU24_REG0_TEMP_DATA1,
                                1,
                                data_buf,
                                2,
                                100);

    if (status != HAL_OK)
        return status;

    int16_t raw_data = ((int16_t)data_buf[0] << 8) | data_buf[1];
    *temperature = ((float)raw_data / C6DOFIMU24_TEMP_RES) + C6DOFIMU24_TEMP_OFFSET;

    return HAL_OK;
}

HAL_StatusTypeDef c6dofimu24_read_data(c6dofimu24_data_t *data_out)
{
    uint8_t data_buf[14] = {0};

    HAL_StatusTypeDef status = HAL_I2C_Mem_Read(
                                &hi2c1,
                                C6DOFIMU24_DEVICE_ADDRESS,
                                C6DOFIMU24_REG0_TEMP_DATA1,
                                1,
                                data_buf,
                                14,
                                100);

    if (status != HAL_OK)
        return status;

    int16_t raw_data;

    raw_data = ((int16_t)data_buf[0] << 8) | data_buf[1];
    data_out->temperature = ((float)raw_data / C6DOFIMU24_TEMP_RES) + C6DOFIMU24_TEMP_OFFSET;

    raw_data = ((int16_t)data_buf[2] << 8) | data_buf[3];
    data_out->accel.x = (float)raw_data / accel_sens;

    raw_data = ((int16_t)data_buf[4] << 8) | data_buf[5];
    data_out->accel.y = (float)raw_data / accel_sens;

    raw_data = ((int16_t)data_buf[6] << 8) | data_buf[7];
    data_out->accel.z = (float)raw_data / accel_sens;

    raw_data = ((int16_t)data_buf[8] << 8) | data_buf[9];
    data_out->gyro.x = (float)raw_data / gyro_sens;

    raw_data = ((int16_t)data_buf[10] << 8) | data_buf[11];
    data_out->gyro.y = (float)raw_data / gyro_sens;

    raw_data = ((int16_t)data_buf[12] << 8) | data_buf[13];
    data_out->gyro.z = (float)raw_data / gyro_sens;

    return HAL_OK;
}

HAL_StatusTypeDef c6dofimu24_default_cfg()
{
    HAL_StatusTypeDef status;
    uint8_t reg_data = 0;

    // Reset device and check communication
    status = c6dofimu24_reset();
    if (status != HAL_OK)
        return status;

    HAL_Delay(100);

    status = c6dofimu24_ping();
    if (status != HAL_OK)
        return status;

    // Configure interrupt (INT1)
    status = HAL_I2C_Mem_Read(
                &hi2c1,
                C6DOFIMU24_DEVICE_ADDRESS,
                C6DOFIMU24_REG0_INT_CONFIG,
                1,
                &reg_data,
                1,
                100);
    if (status != HAL_OK)
        return status;

    reg_data &= ~(C6DOFIMU24_INT_CONFIG_INT1_MODE_MASK |
                  C6DOFIMU24_INT_CONFIG_INT1_DRV_MASK |
                  C6DOFIMU24_INT_CONFIG_INT1_POL_MASK);

    // config interrupt 1 in Latch mode, Push-pull, Active low
    reg_data |= (C6DOFIMU24_INT_CONFIG_INT1_MODE_LATCH |
                 C6DOFIMU24_INT_CONFIG_INT1_DRV_PP |
                 C6DOFIMU24_INT_CONFIG_INT1_POL_LOW);

    status = HAL_I2C_Mem_Write(
                &hi2c1,
                C6DOFIMU24_DEVICE_ADDRESS,
                C6DOFIMU24_REG0_INT_CONFIG,
                1,
                &reg_data,
                1,
                100);
    if (status != HAL_OK)
        return status;

    // INT_CONFIG1
    status = HAL_I2C_Mem_Read(
                &hi2c1,
                C6DOFIMU24_DEVICE_ADDRESS,
                C6DOFIMU24_REG0_INT_CONFIG1,
                1,
                &reg_data,
                1,
                100);
    if (status != HAL_OK)
        return status;

    reg_data &= ~C6DOFIMU24_INT_CONFIG1_ASYNC_RESET_MASK;
    reg_data |= C6DOFIMU24_INT_CONFIG1_ASYNC_RESET_DIS;

    status = HAL_I2C_Mem_Write(
                &hi2c1,
                C6DOFIMU24_DEVICE_ADDRESS,
                C6DOFIMU24_REG0_INT_CONFIG1,
                1,
                &reg_data,
                1,
                100);
    if (status != HAL_OK)
        return status;

    // Enable data ready interrupt
    uint8_t int_src = C6DOFIMU24_INT_SOURCE0_UI_DRDY_INT1_EN;
    status = HAL_I2C_Mem_Write(
                &hi2c1,
                C6DOFIMU24_DEVICE_ADDRESS,
                C6DOFIMU24_REG0_INT_SOURCE0,
                1,
                &int_src,
                1,
                100);
    if (status != HAL_OK)
        return status;

    // Configure gyro and accel (reuse your functions)
    status = c6dofimu24_set_gyro_fs_odr(
                C6DOFIMU24_GYRO_FS_SEL_2000DPS,
                C6DOFIMU24_GYRO_ODR_12_5HZ);
    if (status != HAL_OK)
        return status;

    status = c6dofimu24_set_accel_fs_odr(
                C6DOFIMU24_ACCEL_FS_SEL_4G,
                C6DOFIMU24_ACCEL_ODR_12_5HZ);
    if (status != HAL_OK)
        return status;

    // Power management (enable gyro + accel LN mode)
    status = HAL_I2C_Mem_Read(
                &hi2c1,
                C6DOFIMU24_DEVICE_ADDRESS,
                C6DOFIMU24_REG0_PWR_MGMT0,
                1,
                &reg_data,
                1,
                100);
    if (status != HAL_OK)
        return status;

    reg_data &= ~(C6DOFIMU24_PWR_MGMT0_GYRO_MODE_MASK |
                  C6DOFIMU24_PWR_MGMT0_ACCEL_MODE_MASK);

    reg_data |= (C6DOFIMU24_PWR_MGMT0_GYRO_MODE_LN |
                 C6DOFIMU24_PWR_MGMT0_ACCEL_MODE_LN);

    status = HAL_I2C_Mem_Write(
                &hi2c1,
                C6DOFIMU24_DEVICE_ADDRESS,
                C6DOFIMU24_REG0_PWR_MGMT0,
                1,
                &reg_data,
                1,
                100);
    if (status != HAL_OK)
        return status;

    HAL_Delay(100);

    return HAL_OK;
}

