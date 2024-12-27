#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* 包含标准库 */
#include "stm32f0xx_hal.h"

/* 导出变量 */
extern ADC_HandleTypeDef hadc;
extern TIM_HandleTypeDef htim3;

/* 定义常量 */
#define BATTERY_LOW_THRESHOLD    2800    // 电池低电压阈值 (mV)
#define TEMP_HIGH_THRESHOLD      60      // 高温阈值 (℃)

/* GPIO定义 */
#define LED_Pin                  GPIO_PIN_0
#define LED_GPIO_Port           GPIOA
#define KEY_Pin                 GPIO_PIN_1
#define KEY_GPIO_Port          GPIOA
#define CHARGING_Pin           GPIO_PIN_2
#define CHARGING_GPIO_Port    GPIOA
#define CHARGE_LED_Pin        GPIO_PIN_3
#define CHARGE_LED_GPIO_Port GPIOA

/* 函数声明 */
void Error_Handler(void);

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */ 