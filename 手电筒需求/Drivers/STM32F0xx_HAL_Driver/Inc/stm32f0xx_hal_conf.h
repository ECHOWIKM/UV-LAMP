#ifndef __STM32F0xx_HAL_CONF_H
#define __STM32F0xx_HAL_CONF_H

#ifdef __cplusplus
 extern "C" {
#endif

#define HAL_MODULE_ENABLED
#define HAL_ADC_MODULE_ENABLED
#define HAL_GPIO_MODULE_ENABLED
#define HAL_TIM_MODULE_ENABLED
#define HAL_RCC_MODULE_ENABLED

#include "stm32f0xx_hal_rcc.h"
#include "stm32f0xx_hal_gpio.h"
#include "stm32f0xx_hal_adc.h"
#include "stm32f0xx_hal_tim.h"

#ifdef __cplusplus
}
#endif

#endif /* __STM32F0xx_HAL_CONF_H */ 