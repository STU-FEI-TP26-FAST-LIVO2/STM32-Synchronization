/**
 * @brief 6DOF IMU 24 USER BANK 0 register map summary.
 * @details The list of USER BANK 0 registers.
 */
#define C6DOFIMU24_REG0_DEVICE_CONFIG               0x11
#define C6DOFIMU24_REG0_DRIVE_CONFIG                0x13
#define C6DOFIMU24_REG0_INT_CONFIG                  0x14
#define C6DOFIMU24_REG0_FIFO_CONFIG                 0x16
#define C6DOFIMU24_REG0_TEMP_DATA1                  0x1D
#define C6DOFIMU24_REG0_TEMP_DATA0                  0x1E
#define C6DOFIMU24_REG0_ACCEL_DATA_X1               0x1F
#define C6DOFIMU24_REG0_ACCEL_DATA_X0               0x20
#define C6DOFIMU24_REG0_ACCEL_DATA_Y1               0x21
#define C6DOFIMU24_REG0_ACCEL_DATA_Y0               0x22
#define C6DOFIMU24_REG0_ACCEL_DATA_Z1               0x23
#define C6DOFIMU24_REG0_ACCEL_DATA_Z0               0x24
#define C6DOFIMU24_REG0_GYRO_DATA_X1                0x25
#define C6DOFIMU24_REG0_GYRO_DATA_X0                0x26
#define C6DOFIMU24_REG0_GYRO_DATA_Y1                0x27
#define C6DOFIMU24_REG0_GYRO_DATA_Y0                0x28
#define C6DOFIMU24_REG0_GYRO_DATA_Z1                0x29
#define C6DOFIMU24_REG0_GYRO_DATA_Z0                0x2A
#define C6DOFIMU24_REG0_TMST_FSYNCH                 0x2B
#define C6DOFIMU24_REG0_TMST_FSYNCL                 0x2C
#define C6DOFIMU24_REG0_INT_STATUS                  0x2D
#define C6DOFIMU24_REG0_FIFO_COUNTH                 0x2E
#define C6DOFIMU24_REG0_FIFO_COUNTL                 0x2F
#define C6DOFIMU24_REG0_FIFO_DATA                   0x30
#define C6DOFIMU24_REG0_INT_STATUS2                 0x37
#define C6DOFIMU24_REG0_SIGNAL_PATH_RESET           0x4B
#define C6DOFIMU24_REG0_INTF_CONFIG0                0x4C
#define C6DOFIMU24_REG0_INTF_CONFIG1                0x4D
#define C6DOFIMU24_REG0_PWR_MGMT0                   0x4E
#define C6DOFIMU24_REG0_GYRO_CONFIG0                0x4F
#define C6DOFIMU24_REG0_ACCEL_CONFIG0               0x50
#define C6DOFIMU24_REG0_GYRO_CONFIG1                0x51
#define C6DOFIMU24_REG0_GYRO_ACCEL_CONFIG0          0x52
#define C6DOFIMU24_REG0_ACCEL_CONFIG1               0x53
#define C6DOFIMU24_REG0_TMST_CONFIG                 0x54
#define C6DOFIMU24_REG0_WOM_CONFIG                  0x57
#define C6DOFIMU24_REG0_FIFO_CONFIG1                0x5F
#define C6DOFIMU24_REG0_FIFO_CONFIG2                0x60
#define C6DOFIMU24_REG0_FIFO_CONFIG3                0x61
#define C6DOFIMU24_REG0_FSYNC_CONFIG                0x62
#define C6DOFIMU24_REG0_INT_CONFIG0                 0x63
#define C6DOFIMU24_REG0_INT_CONFIG1                 0x64
#define C6DOFIMU24_REG0_INT_SOURCE0                 0x65
#define C6DOFIMU24_REG0_INT_SOURCE1                 0x66
#define C6DOFIMU24_REG0_INT_SOURCE3                 0x68
#define C6DOFIMU24_REG0_INT_SOURCE4                 0x69
#define C6DOFIMU24_REG0_FIFO_LOST_PKT0              0x6C
#define C6DOFIMU24_REG0_FIFO_LOST_PKT1              0x6D
#define C6DOFIMU24_REG0_SELF_TEST_CONFIG            0x70
#define C6DOFIMU24_REG0_WHO_AM_I                    0x75
#define C6DOFIMU24_REG0_REG_BANK_SEL                0x76

/**
 * @brief 6DOF IMU 24 USER BANK 1 register map summary.
 * @details The list of USER BANK 1 registers.
 */
#define C6DOFIMU24_REG1_SENSOR_CONFIG               0x03
#define C6DOFIMU24_REG1_GYRO_CONFIG_STATIC2         0x0B
#define C6DOFIMU24_REG1_GYRO_CONFIG_STATIC3         0x0C
#define C6DOFIMU24_REG1_GYRO_CONFIG_STATIC4         0x0D
#define C6DOFIMU24_REG1_GYRO_CONFIG_STATIC5         0x0E
#define C6DOFIMU24_REG1_GYRO_CONFIG_STATIC6         0x0F
#define C6DOFIMU24_REG1_GYRO_CONFIG_STATIC7         0x10
#define C6DOFIMU24_REG1_GYRO_CONFIG_STATIC8         0x11
#define C6DOFIMU24_REG1_GYRO_CONFIG_STATIC9         0x12
#define C6DOFIMU24_REG1_GYRO_CONFIG_STATIC10        0x13
#define C6DOFIMU24_REG1_XG_ST_DATA                  0x5F
#define C6DOFIMU24_REG1_YG_ST_DATA                  0x60
#define C6DOFIMU24_REG1_ZG_ST_DATA                  0x61
#define C6DOFIMU24_REG1_TMSTVAL0                    0x62
#define C6DOFIMU24_REG1_TMSTVAL1                    0x63
#define C6DOFIMU24_REG1_TMSTVAL2                    0x64
#define C6DOFIMU24_REG1_INTF_CONFIG4                0x7A
#define C6DOFIMU24_REG1_INTF_CONFIG5                0x7B

/**
 * @brief 6DOF IMU 24 USER BANK 2 register map summary.
 * @details The list of USER BANK 2 registers.
 */
#define C6DOFIMU24_REG2_ACCEL_CONFIG_STATIC2        0x03
#define C6DOFIMU24_REG2_ACCEL_CONFIG_STATIC3        0x04
#define C6DOFIMU24_REG2_ACCEL_CONFIG_STATIC4        0x05
#define C6DOFIMU24_REG2_XA_ST_DATA                  0x3B
#define C6DOFIMU24_REG2_YA_ST_DATA                  0x3C
#define C6DOFIMU24_REG2_ZA_ST_DATA                  0x3D

/**
 * @brief 6DOF IMU 24 USER BANK 4 register map summary.
 * @details The list of USER BANK 4 registers.
 */
#define C6DOFIMU24_REG4_ACCEL_WOM_X_THR             0x4A
#define C6DOFIMU24_REG4_ACCEL_WOM_Y_THR             0x4B
#define C6DOFIMU24_REG4_ACCEL_WOM_Z_THR             0x4C
#define C6DOFIMU24_REG4_OFFSET_USER_0               0x77
#define C6DOFIMU24_REG4_OFFSET_USER_1               0x78
#define C6DOFIMU24_REG4_OFFSET_USER_2               0x79
#define C6DOFIMU24_REG4_OFFSET_USER_3               0x7A
#define C6DOFIMU24_REG4_OFFSET_USER_4               0x7B
#define C6DOFIMU24_REG4_OFFSET_USER_5               0x7C
#define C6DOFIMU24_REG4_OFFSET_USER_6               0x7D
#define C6DOFIMU24_REG4_OFFSET_USER_7               0x7E
#define C6DOFIMU24_REG4_OFFSET_USER_8               0x7F

/*! @} */ // c6dofimu24_reg

/**
 * @defgroup c6dofimu24_set 6DOF IMU 24 Registers Settings
 * @brief Settings for registers of 6DOF IMU 24 Click driver.
 */

/**
 * @addtogroup c6dofimu24_set
 * @{
 */

/**
 * @brief 6DOF IMU 24 USER BANK register selection.
 * @details Specified setting for USER BANK register selection of 6DOF IMU 24 Click driver.
 */
#define C6DOFIMU24_USER_BANK_0                      0x00
#define C6DOFIMU24_USER_BANK_1                      0x01
#define C6DOFIMU24_USER_BANK_2                      0x02
#define C6DOFIMU24_USER_BANK_4                      0x04

/**
 * @brief 6DOF IMU 24 DEVICE_CONFIG register setting.
 * @details Specified setting for DEVICE_CONFIG register of 6DOF IMU 24 Click driver.
 */
#define C6DOFIMU24_DEVICE_CONFIG_SPI_MODE_0_3       0x00
#define C6DOFIMU24_DEVICE_CONFIG_SPI_MODE_1_2       0x10
#define C6DOFIMU24_DEVICE_CONFIG_SPI_MODE_MASK      0x10
#define C6DOFIMU24_DEVICE_CONFIG_SOFT_RESET         0x01

/**
 * @brief 6DOF IMU 24 INT_CONFIG register setting.
 * @details Specified setting for INT_CONFIG register of 6DOF IMU 24 Click driver.
 */
#define C6DOFIMU24_INT_CONFIG_INT2_MODE_PULSE       0x00
#define C6DOFIMU24_INT_CONFIG_INT2_MODE_LATCH       0x20
#define C6DOFIMU24_INT_CONFIG_INT2_MODE_MASK        0x20
#define C6DOFIMU24_INT_CONFIG_INT2_DRV_OD           0x00
#define C6DOFIMU24_INT_CONFIG_INT2_DRV_PP           0x10
#define C6DOFIMU24_INT_CONFIG_INT2_DRV_MASK         0x10
#define C6DOFIMU24_INT_CONFIG_INT2_POL_LOW          0x00
#define C6DOFIMU24_INT_CONFIG_INT2_POL_HIGH         0x08
#define C6DOFIMU24_INT_CONFIG_INT2_POL_MASK         0x08
#define C6DOFIMU24_INT_CONFIG_INT1_MODE_PULSE       0x00
#define C6DOFIMU24_INT_CONFIG_INT1_MODE_LATCH       0x04
#define C6DOFIMU24_INT_CONFIG_INT1_MODE_MASK        0x04
#define C6DOFIMU24_INT_CONFIG_INT1_DRV_OD           0x00
#define C6DOFIMU24_INT_CONFIG_INT1_DRV_PP           0x02
#define C6DOFIMU24_INT_CONFIG_INT1_DRV_MASK         0x02
#define C6DOFIMU24_INT_CONFIG_INT1_POL_LOW          0x00
#define C6DOFIMU24_INT_CONFIG_INT1_POL_HIGH         0x01
#define C6DOFIMU24_INT_CONFIG_INT1_POL_MASK         0x01

/**
 * @brief 6DOF IMU 24 INT_CONFIG1 register setting.
 * @details Specified setting for INT_CONFIG1 register of 6DOF IMU 24 Click driver.
 */
#define C6DOFIMU24_INT_CONFIG1_TPULSE_100US         0x00
#define C6DOFIMU24_INT_CONFIG1_TPULSE_8US           0x40
#define C6DOFIMU24_INT_CONFIG1_TPULSE_MASK          0x40
#define C6DOFIMU24_INT_CONFIG1_TDEASSERT_100US      0x00
#define C6DOFIMU24_INT_CONFIG1_TDEASSERT_DIS        0x20
#define C6DOFIMU24_INT_CONFIG1_TDEASSERT_MASK       0x20
#define C6DOFIMU24_INT_CONFIG1_ASYNC_RESET_DIS      0x00
#define C6DOFIMU24_INT_CONFIG1_ASYNC_RESET_EN       0x10
#define C6DOFIMU24_INT_CONFIG1_ASYNC_RESET_MASK     0x10

/**
 * @brief 6DOF IMU 24 PWR_MGMT0 register setting.
 * @details Specified setting for PWR_MGMT0 register of 6DOF IMU 24 Click driver.
 */
#define C6DOFIMU24_PWR_MGMT0_TEMP_EN                0x00
#define C6DOFIMU24_PWR_MGMT0_TEMP_DIS               0x20
#define C6DOFIMU24_PWR_MGMT0_TEMP_MASK              0x20
#define C6DOFIMU24_PWR_MGMT0_IDLE                   0x10
#define C6DOFIMU24_PWR_MGMT0_GYRO_MODE_OFF          0x00
#define C6DOFIMU24_PWR_MGMT0_GYRO_MODE_STBY         0x04
#define C6DOFIMU24_PWR_MGMT0_GYRO_MODE_LN           0x0C
#define C6DOFIMU24_PWR_MGMT0_GYRO_MODE_MASK         0x0C
#define C6DOFIMU24_PWR_MGMT0_ACCEL_MODE_OFF         0x00
#define C6DOFIMU24_PWR_MGMT0_ACCEL_MODE_LP          0x02
#define C6DOFIMU24_PWR_MGMT0_ACCEL_MODE_LN          0x03
#define C6DOFIMU24_PWR_MGMT0_ACCEL_MODE_MASK        0x03

/**
 * @brief 6DOF IMU 24 GYRO_CONFIG0 register setting.
 * @details Specified setting for GYRO_CONFIG0 register of 6DOF IMU 24 Click driver.
 */
#define C6DOFIMU24_GYRO_CONFIG0_FS_SEL_2000DPS      0x00
#define C6DOFIMU24_GYRO_CONFIG0_FS_SEL_1000DPS      0x20
#define C6DOFIMU24_GYRO_CONFIG0_FS_SEL_500DPS       0x40
#define C6DOFIMU24_GYRO_CONFIG0_FS_SEL_250DPS       0x60
#define C6DOFIMU24_GYRO_CONFIG0_FS_SEL_125DPS       0x80
#define C6DOFIMU24_GYRO_CONFIG0_FS_SEL_62_5DPS      0xA0
#define C6DOFIMU24_GYRO_CONFIG0_FS_SEL_31_25DPS     0xC0
#define C6DOFIMU24_GYRO_CONFIG0_FS_SEL_15_625DPS    0xE0
#define C6DOFIMU24_GYRO_CONFIG0_FS_SEL_MASK         0xE0
#define C6DOFIMU24_GYRO_CONFIG0_ODR_32000HZ         0x01
#define C6DOFIMU24_GYRO_CONFIG0_ODR_16000HZ         0x02
#define C6DOFIMU24_GYRO_CONFIG0_ODR_8000HZ          0x03
#define C6DOFIMU24_GYRO_CONFIG0_ODR_4000HZ          0x04
#define C6DOFIMU24_GYRO_CONFIG0_ODR_2000HZ          0x05
#define C6DOFIMU24_GYRO_CONFIG0_ODR_1000HZ          0x06
#define C6DOFIMU24_GYRO_CONFIG0_ODR_200HZ           0x07
#define C6DOFIMU24_GYRO_CONFIG0_ODR_100HZ           0x08
#define C6DOFIMU24_GYRO_CONFIG0_ODR_50HZ            0x09
#define C6DOFIMU24_GYRO_CONFIG0_ODR_25HZ            0x0A
#define C6DOFIMU24_GYRO_CONFIG0_ODR_12_5HZ          0x0B
#define C6DOFIMU24_GYRO_CONFIG0_ODR_500HZ           0x0F
#define C6DOFIMU24_GYRO_CONFIG0_ODR_MASK            0x0F

/**
 * @brief 6DOF IMU 24 ACCEL_CONFIG0 register setting.
 * @details Specified setting for ACCEL_CONFIG0 register of 6DOF IMU 24 Click driver.
 */
#define C6DOFIMU24_ACCEL_CONFIG0_FS_SEL_32G         0x00
#define C6DOFIMU24_ACCEL_CONFIG0_FS_SEL_16G         0x20
#define C6DOFIMU24_ACCEL_CONFIG0_FS_SEL_8G          0x40
#define C6DOFIMU24_ACCEL_CONFIG0_FS_SEL_4G          0x60
#define C6DOFIMU24_ACCEL_CONFIG0_FS_SEL_MASK        0xE0
#define C6DOFIMU24_ACCEL_CONFIG0_ODR_32000HZ        0x01
#define C6DOFIMU24_ACCEL_CONFIG0_ODR_16000HZ        0x02
#define C6DOFIMU24_ACCEL_CONFIG0_ODR_8000HZ         0x03
#define C6DOFIMU24_ACCEL_CONFIG0_ODR_4000HZ         0x04
#define C6DOFIMU24_ACCEL_CONFIG0_ODR_2000HZ         0x05
#define C6DOFIMU24_ACCEL_CONFIG0_ODR_1000HZ         0x06
#define C6DOFIMU24_ACCEL_CONFIG0_ODR_200HZ          0x07
#define C6DOFIMU24_ACCEL_CONFIG0_ODR_100HZ          0x08
#define C6DOFIMU24_ACCEL_CONFIG0_ODR_50HZ           0x09
#define C6DOFIMU24_ACCEL_CONFIG0_ODR_25HZ           0x0A
#define C6DOFIMU24_ACCEL_CONFIG0_ODR_12_5HZ         0x0B
#define C6DOFIMU24_ACCEL_CONFIG0_ODR_6_25HZ         0x0C
#define C6DOFIMU24_ACCEL_CONFIG0_ODR_3_125HZ        0x0D
#define C6DOFIMU24_ACCEL_CONFIG0_ODR_1_5625HZ       0x0E
#define C6DOFIMU24_ACCEL_CONFIG0_ODR_500HZ          0x0F
#define C6DOFIMU24_ACCEL_CONFIG0_ODR_MASK           0x0F

/**
 * @brief 6DOF IMU 24 INT_SOURCE0 register setting.
 * @details Specified setting for INT_SOURCE0 register of 6DOF IMU 24 Click driver.
 */
#define C6DOFIMU24_INT_SOURCE0_UI_FSYNC_INT1_EN     0x40
#define C6DOFIMU24_INT_SOURCE0_PLL_RDY_INT1_EN      0x20
#define C6DOFIMU24_INT_SOURCE0_RESET_DONE_INT1_EN   0x10
#define C6DOFIMU24_INT_SOURCE0_UI_DRDY_INT1_EN      0x08
#define C6DOFIMU24_INT_SOURCE0_FIFO_THS_INT1_EN     0x04
#define C6DOFIMU24_INT_SOURCE0_FIFO_FULL_INT1_EN    0x02
#define C6DOFIMU24_INT_SOURCE0_AGC_RDY_INT1_EN      0x01

/**
 * @brief 6DOF IMU 24 INT_STATUS register setting.
 * @details Specified setting for INT_STATUS register of 6DOF IMU 24 Click driver.
 */
#define C6DOFIMU24_INT_STATUS_UI_FSYNC              0x40
#define C6DOFIMU24_INT_STATUS_PLL_RDY               0x20
#define C6DOFIMU24_INT_STATUS_RESET_DONE            0x10
#define C6DOFIMU24_INT_STATUS_DATA_RDY              0x08
#define C6DOFIMU24_INT_STATUS_FIFO_THS              0x04
#define C6DOFIMU24_INT_STATUS_FIFO_FULL             0x02
#define C6DOFIMU24_INT_STATUS_AGC_RDY               0x01

/**
 * @brief 6DOF IMU 24 WHO_AM_I register setting.
 * @details Specified setting for WHO_AM_I register of 6DOF IMU 24 Click driver.
 */
#define C6DOFIMU24_WHO_AM_I                         0x3B

/**
 * @brief 6DOF IMU 24 gyro fs sel and odr setting.
 * @details Specified setting for gyro full scale resolution and output data rate of 6DOF IMU 24 Click driver.
 */
#define C6DOFIMU24_GYRO_FS_SEL_15_625DPS            0x00
#define C6DOFIMU24_GYRO_FS_SEL_31_25DPS             0x01
#define C6DOFIMU24_GYRO_FS_SEL_62_5DPS              0x02
#define C6DOFIMU24_GYRO_FS_SEL_125DPS               0x03
#define C6DOFIMU24_GYRO_FS_SEL_250DPS               0x04
#define C6DOFIMU24_GYRO_FS_SEL_500DPS               0x05
#define C6DOFIMU24_GYRO_FS_SEL_1000DPS              0x06
#define C6DOFIMU24_GYRO_FS_SEL_2000DPS              0x07
#define C6DOFIMU24_GYRO_ODR_12_5HZ                  0x00
#define C6DOFIMU24_GYRO_ODR_25HZ                    0x01
#define C6DOFIMU24_GYRO_ODR_50HZ                    0x02
#define C6DOFIMU24_GYRO_ODR_100HZ                   0x03
#define C6DOFIMU24_GYRO_ODR_200HZ                   0x04
#define C6DOFIMU24_GYRO_ODR_500HZ                   0x05
#define C6DOFIMU24_GYRO_ODR_1000HZ                  0x06
#define C6DOFIMU24_GYRO_ODR_2000HZ                  0x07
#define C6DOFIMU24_GYRO_ODR_4000HZ                  0x08
#define C6DOFIMU24_GYRO_ODR_8000HZ                  0x09
#define C6DOFIMU24_GYRO_ODR_16000HZ                 0x0A
#define C6DOFIMU24_GYRO_ODR_32000HZ                 0x0B
#define C6DOFIMU24_GYRO_DATA_RES                    0x7FFF
#define C6DOFIMU24_GYRO_MIN_DPS                     15.625f

/**
 * @brief 6DOF IMU 24 accel fs sel and odr setting.
 * @details Specified setting for accel full scale resolution and output data rate of 6DOF IMU 24 Click driver.
 */
#define C6DOFIMU24_ACCEL_FS_SEL_4G                  0x00
#define C6DOFIMU24_ACCEL_FS_SEL_8G                  0x01
#define C6DOFIMU24_ACCEL_FS_SEL_16G                 0x02
#define C6DOFIMU24_ACCEL_FS_SEL_32G                 0x03
#define C6DOFIMU24_ACCEL_ODR_1_5625HZ               0x00
#define C6DOFIMU24_ACCEL_ODR_3_125HZ                0x01
#define C6DOFIMU24_ACCEL_ODR_6_25HZ                 0x02
#define C6DOFIMU24_ACCEL_ODR_12_5HZ                 0x03
#define C6DOFIMU24_ACCEL_ODR_25HZ                   0x04
#define C6DOFIMU24_ACCEL_ODR_50HZ                   0x05
#define C6DOFIMU24_ACCEL_ODR_100HZ                  0x06
#define C6DOFIMU24_ACCEL_ODR_200HZ                  0x07
#define C6DOFIMU24_ACCEL_ODR_500HZ                  0x08
#define C6DOFIMU24_ACCEL_ODR_1000HZ                 0x09
#define C6DOFIMU24_ACCEL_ODR_2000HZ                 0x0A
#define C6DOFIMU24_ACCEL_ODR_4000HZ                 0x0B
#define C6DOFIMU24_ACCEL_ODR_8000HZ                 0x0C
#define C6DOFIMU24_ACCEL_ODR_16000HZ                0x0D
#define C6DOFIMU24_ACCEL_ODR_32000HZ                0x0E
#define C6DOFIMU24_ACCEL_DATA_RES                   0x7FFF
#define C6DOFIMU24_ACCEL_MIN_G                      4

/**
 * @brief 6DOF IMU 24 temperature calculation setting.
 * @details Specified setting for temperature calculation of 6DOF IMU 24 Click driver.
 */
#define C6DOFIMU24_TEMP_RES                         132.48f
#define C6DOFIMU24_TEMP_OFFSET                      25

/**
 * @brief 6DOF IMU 24 device address setting.
 * @details Specified setting for device slave address selection of
 * 6DOF IMU 24 Click driver.
 */
#define C6DOFIMU24_DEVICE_ADDRESS_0                 0x68
#define C6DOFIMU24_DEVICE_ADDRESS_1                 0x69

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU.
 * Can be overwritten with @b c6dofimu24_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define C6DOFIMU24_SET_DATA_SAMPLE_EDGE             SET_SPI_DATA_SAMPLE_EDGE
#define C6DOFIMU24_SET_DATA_SAMPLE_MIDDLE           SET_SPI_DATA_SAMPLE_MIDDLE
