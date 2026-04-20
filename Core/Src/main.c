/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dma.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
HAL_StatusTypeDef uart_status;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
#include <stdio.h>
#include <string.h>
#include "IMU.h"

#define IMU_DATA_RAW_SIZE (14 + 1)

char gps_msg[128]; // Zväčšené pre istotu
int sec = 0;
int min = 15;
int hod = 12;

uint8_t Get_NMEA_Checksum(char *s) {
    uint8_t check = 0;
    for (int i = 1; s[i] != '*' && s[i] != '\0'; i++) {
        check ^= s[i];
    }
    return check;
}

uint8_t gprmc_flag = 0;
volatile uint16_t sec_total = 0; // 18 hours operational time max :p
volatile uint8_t imu_drdy_flag = 0;
c6dofimu24_data_t imu_data;
uint8_t imu_data_raw[IMU_DATA_RAW_SIZE]; // 14 for IMU data, 1 stop bit
uint8_t uart_debug_msg[100];
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_TIM1_Init();
  MX_USART1_UART_Init();
  MX_TIM2_Init();
  MX_USART2_UART_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */
  HAL_Delay(500);
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
  HAL_StatusTypeDef status = c6dofimu24_default_cfg();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  uint32_t timer_val = __HAL_TIM_GET_COUNTER(&htim1);

	// PPS je HIGH od 0 do 30000. Padá pri 5000 (500ms).
	// Čakáme, kým timer dosiahne 5050 (teda 505ms - tesne po páde na 0).
	if (timer_val >= 30050 && !gprmc_flag)
	{
		// Ochrana, aby sa neposlalo viackrát
		gprmc_flag = 1;
		// 1. Inkrementácia času (simulácia GPS sekúnd)
		++sec_total;
		if(++sec >= 60) {
			sec = 0;
			if(++min >= 60) { min = 0; hod++; }
		}

		// 2. Formátovanie GPRMC správy
		// Hesai vyžaduje platný dátum, tu je fixne 090326 (9. Marec 2026)
		sprintf(gps_msg, "$GPRMC,%02d%02d%02d,A,4808.0000,N,01706.0000,E,0.0,0.0,090323,,,A*", hod, min, sec);

		// 3. Pridanie Checksumu
		uint8_t crc = Get_NMEA_Checksum(gps_msg);
		char crc_str[10];
		sprintf(crc_str, "%02X\r\n", crc);
		strcat(gps_msg, crc_str);

		// 4. Odoslanie cez UART1 (PA9)
		// Správa sa začne posielať v 505ms a skončí cca v 580ms.
//		uart_status = HAL_UART_Transmit(&huart1, (uint8_t*)gps_msg, strlen(gps_msg), 100);
		uart_status = HAL_UART_Transmit_DMA(&huart1, (uint8_t*)gps_msg, strlen(gps_msg));

		//c6dofimu24_clear_data_ready();
	}
	if(gprmc_flag && timer_val <= 30000)
		gprmc_flag = 0;

	if(imu_drdy_flag)
	{
		imu_drdy_flag = 0;
		// c6dofimu24_read_data(&imu_data);
//		HAL_StatusTypeDef imu_status = c6dofimu24_read_data_raw(imu_data_raw);
//		HAL_StatusTypeDef imu_status = c6dofimu24_read_data(&imu_data);
//		HAL_StatusTypeDef imu_status = c6dofimu24_read_data(&imu_data);

	    HAL_StatusTypeDef status = HAL_I2C_Mem_Read_DMA(
	                                &hi2c1,
	                                C6DOFIMU24_DEVICE_ADDRESS,
	                                C6DOFIMU24_REG0_TEMP_DATA1,
	                                1,
									imu_data_raw,
	                                14);
//		imu_data_raw[14] = '\0';
//		c6dofimu24_clear_data_ready();
//		sprintf(uart_debug_msg, "IMU data: accel_x: %d, temp: %d\r\n", (int)(imu_data.accel.x*100), (int)(imu_data.temperature*100));

//		uart_status = HAL_UART_Transmit(&huart2, (uint8_t*)imu_data_raw, IMU_DATA_RAW_SIZE, 100);
//		uart_status = HAL_UART_Transmit(&huart2, (uint8_t*)uart_debug_msg, strlen(uart_debug_msg), 100);
	}

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }

  /** Enables the Clock Security System
  */
  HAL_RCC_EnableCSS();
}

/* USER CODE BEGIN 4 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == IMU_DRDY_Pin)
	{
		imu_drdy_flag = 1;
	}
}

void HAL_I2C_MemRxCpltCallback(I2C_HandleTypeDef *hi2c)
{
	uart_status = HAL_UART_Transmit(&huart2, (uint8_t*)imu_data_raw, IMU_DATA_RAW_SIZE, 100);
	c6dofimu24_clear_data_ready();
}


/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
