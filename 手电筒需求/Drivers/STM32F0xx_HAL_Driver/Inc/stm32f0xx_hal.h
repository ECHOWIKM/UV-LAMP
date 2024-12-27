#ifndef __STM32F0xx_HAL_H
#define __STM32F0xx_HAL_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f0xx_hal_conf.h"
#include "stm32f0xx_hal_def.h"

HAL_StatusTypeDef HAL_Init(void);
HAL_StatusTypeDef HAL_DeInit(void);
void HAL_MspInit(void);
void HAL_MspDeInit(void);
void HAL_Delay(__IO uint32_t Delay);
uint32_t HAL_GetTick(void);

#ifdef __cplusplus
}
#endif

#endif /* __STM32F0xx_HAL_H */ 