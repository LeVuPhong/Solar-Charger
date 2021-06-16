/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */
#define MON_OUT_SLAVE	0x80 //0x40<<1
#define MON_IN_SLAVE	0x8A //0x45<<1
/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define COMP1_IN_Pin GPIO_PIN_1
#define COMP1_IN_GPIO_Port GPIOA
#define CPU_MPPT_Pin GPIO_PIN_2
#define CPU_MPPT_GPIO_Port GPIOA
#define COMP2_IN_Pin GPIO_PIN_3
#define COMP2_IN_GPIO_Port GPIOA
#define SOLAR_SHDN_CTL_Pin GPIO_PIN_5
#define SOLAR_SHDN_CTL_GPIO_Port GPIOA
#define SOLAR_CHRG_SENSE_Pin GPIO_PIN_6
#define SOLAR_CHRG_SENSE_GPIO_Port GPIOA
#define SOLAR_CHRG_SENSE_EXTI_IRQn EXTI9_5_IRQn
#define SOLAR_FAULT_SENSE_Pin GPIO_PIN_7
#define SOLAR_FAULT_SENSE_GPIO_Port GPIOA
#define SOLAR_FAULT_SENSE_EXTI_IRQn EXTI9_5_IRQn
#define RS485_RE_Pin GPIO_PIN_1
#define RS485_RE_GPIO_Port GPIOB
#define RS485_TX_Pin GPIO_PIN_10
#define RS485_TX_GPIO_Port GPIOB
#define RS485_RX_Pin GPIO_PIN_11
#define RS485_RX_GPIO_Port GPIOB
#define CPU_LED_Pin GPIO_PIN_11
#define CPU_LED_GPIO_Port GPIOA
#define CPU_ALERT_Pin GPIO_PIN_5
#define CPU_ALERT_GPIO_Port GPIOB
#define CPU_ALERT_EXTI_IRQn EXTI9_5_IRQn
#define CPU_SCL_Pin GPIO_PIN_6
#define CPU_SCL_GPIO_Port GPIOB
#define CPU_SDA_Pin GPIO_PIN_7
#define CPU_SDA_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
