/* 系统时钟配置函数 */
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
    RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

    /* 配置HSI为48MHz */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL12;
    RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }

    /* 配置系统时钟 */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                                |RCC_CLOCKTYPE_PCLK1;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
    {
        Error_Handler();
    }

    /* 配置外设时钟 */
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
    PeriphClkInit.AdcClockSelection = RCC_ADCCLKSOURCE_PCLK_DIV4;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    {
        Error_Handler();
    }
}

/* GPIO初始化函数 */
static void MX_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* 使能GPIO时钟 */
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    /* 配置LED引脚 */
    GPIO_InitStruct.Pin = LED_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF1_TIM3;
    HAL_GPIO_Init(LED_GPIO_Port, &GPIO_InitStruct);

    /* 配置按键引脚（带中断） */
    GPIO_InitStruct.Pin = KEY_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(KEY_GPIO_Port, &GPIO_InitStruct);

    /* 配置充电检测引脚 */
    GPIO_InitStruct.Pin = CHARGING_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(CHARGING_GPIO_Port, &GPIO_InitStruct);

    /* 配置充电指示LED引脚 */
    GPIO_InitStruct.Pin = CHARGE_LED_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(CHARGE_LED_GPIO_Port, &GPIO_InitStruct);

    /* 使能按键中断 */
    HAL_NVIC_SetPriority(EXTI0_1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(EXTI0_1_IRQn);
}

/* ADC初始化函数 */
static void MX_ADC_Init(void)
{
    ADC_ChannelConfTypeDef sConfig = {0};

    /* ADC基本配置 */
    hadc.Instance = ADC1;
    hadc.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
    hadc.Init.Resolution = ADC_RESOLUTION_12B;
    hadc.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    hadc.Init.ScanConvMode = ADC_SCAN_ENABLE;
    hadc.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
    hadc.Init.LowPowerAutoWait = DISABLE;
    hadc.Init.LowPowerAutoPowerOff = DISABLE;
    hadc.Init.ContinuousConvMode = DISABLE;
    hadc.Init.DiscontinuousConvMode = ENABLE;
    hadc.Init.ExternalTrigConv = ADC_SOFTWARE_START;
    hadc.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
    hadc.Init.DMAContinuousRequests = DISABLE;
    hadc.Init.Overrun = ADC_OVR_DATA_PRESERVED;
    if (HAL_ADC_Init(&hadc) != HAL_OK)
    {
        Error_Handler();
    }

    /* 配置电池电压检测通道 */
    sConfig.Channel = ADC_CHANNEL_4;
    sConfig.Rank = ADC_RANK_CHANNEL_NUMBER;
    sConfig.SamplingTime = ADC_SAMPLETIME_239CYCLES_5;
    if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
    {
        Error_Handler();
    }

    /* 配置温度检测通道 */
    sConfig.Channel = ADC_CHANNEL_5;
    if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
    {
        Error_Handler();
    }
}

/* PWM定时器初始化函数 */
static void MX_TIM3_Init(void)
{
    TIM_ClockConfigTypeDef sClockSourceConfig = {0};
    TIM_MasterConfigTypeDef sMasterConfig = {0};
    TIM_OC_InitTypeDef sConfigOC = {0};

    /* 基本定时器配置 */
    htim3.Instance = TIM3;
    htim3.Init.Prescaler = 48-1;  // 48MHz/48=1MHz
    htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim3.Init.Period = 1000-1;   // 1MHz/1000=1KHz PWM频率
    htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
    {
        Error_Handler();
    }

    /* 时钟源配置 */
    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
    {
        Error_Handler();
    }

    /* PWM模式配置 */
    if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
    {
        Error_Handler();
    }

    /* 主模式配置 */
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
    {
        Error_Handler();
    }

    /* PWM通道配置 */
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = 0;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
    {
        Error_Handler();
    }
}

/* 错误处理函数 */
void Error_Handler(void)
{
    /* 错误处理代码 */
    while(1)
    {
        HAL_GPIO_TogglePin(CHARGE_LED_GPIO_Port, CHARGE_LED_Pin);
        HAL_Delay(100);
    }
} 