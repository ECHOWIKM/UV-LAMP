#ifndef __STM32F0xx_HAL_DEF_H
#define __STM32F0xx_HAL_DEF_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f0xx.h"

typedef enum 
{
  HAL_OK       = 0x00U,
  HAL_ERROR    = 0x01U,
  HAL_BUSY     = 0x02U,
  HAL_TIMEOUT  = 0x03U
} HAL_StatusTypeDef;

#define HAL_MAX_DELAY      0xFFFFFFFFU

#define __HAL_RCC_GPIOA_CLK_ENABLE()   do { } while(0)
#define __HAL_RCC_GPIOB_CLK_ENABLE()   do { } while(0)

#ifdef __cplusplus
}
#endif

#endif /* __STM32F0xx_HAL_DEF_H */ 