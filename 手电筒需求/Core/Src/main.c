/* 包含必要的头文件 */
#include "main.h"
#include "stm32f0xx_hal.h"

/* 私有变量定义 */
ADC_HandleTypeDef hadc;
TIM_HandleTypeDef htim3;

uint16_t batteryVoltage;    // 电池电压ADC值
uint16_t boostVoltage;      // 升压输出电压ADC值
uint16_t temperature;       // 温度ADC值
uint8_t ledState = 0;       // LED状态
uint8_t brightness = 100;   // LED亮度百分比
uint8_t isCharging = 0;     // 充电状态
uint8_t boostEnabled = 0;   // 升压使能状态

/* 定义阈值 */
#define BATTERY_LOW_THRESHOLD  1000    // 1.7V对应的ADC值
#define BATTERY_HIGH_THRESHOLD 1647    // 2.8V对应的ADC值
#define BOOST_VOLTAGE_TARGET   2185    // 3.7V对应的ADC值
#define TEMP_HIGH_THRESHOLD    2500    // 65℃对应的ADC值

/* 私有函数声明 */
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC_Init(void);
static void MX_TIM3_Init(void);
void Error_Handler(void);
static void EnableBoost(void);
static void DisableBoost(void);
static uint8_t CheckBoostVoltage(void);

/* 主函数 */
int main(void)
{
    /* MCU初始化 */
    HAL_Init();
    SystemClock_Config();
    
    /* 初始化外设 */
    MX_GPIO_Init();
    MX_ADC_Init();
    MX_TIM3_Init();
    
    /* 启动PWM输出 */
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
    
    /* 初始状态关闭升压 */
    DisableBoost();
    
    while (1)
    {
        /* 电池电压检测 */
        HAL_ADC_Start(&hadc);
        HAL_ADC_PollForConversion(&hadc, 100);
        batteryVoltage = HAL_ADC_GetValue(&hadc);
        
        /* 升压电压检测 */
        HAL_ADC_Start(&hadc);
        HAL_ADC_PollForConversion(&hadc, 100);
        boostVoltage = HAL_ADC_GetValue(&hadc);
        
        /* 温度检测 */
        HAL_ADC_Start(&hadc);
        HAL_ADC_PollForConversion(&hadc, 100);
        temperature = HAL_ADC_GetValue(&hadc);
        
        /* 保护功能检查 */
        if(batteryVoltage < BATTERY_LOW_THRESHOLD || 
           temperature > TEMP_HIGH_THRESHOLD ||
           (boostEnabled && !CheckBoostVoltage()))
        {
            ledState = 0;
            DisableBoost();          // 关闭升压
            TIM3->CCR1 = 0;          // 关闭LED
            HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
        }
        
        /* 充电状态检测 */
        if(HAL_GPIO_ReadPin(CHARGING_GPIO_Port, CHARGING_Pin) == GPIO_PIN_SET)
        {
            isCharging = 1;
            DisableBoost();          // 充电时关闭升压
            HAL_GPIO_WritePin(CHARGE_LED_GPIO_Port, CHARGE_LED_Pin, GPIO_PIN_SET);
        }
        else
        {
            isCharging = 0;
            HAL_GPIO_WritePin(CHARGE_LED_GPIO_Port, CHARGE_LED_Pin, GPIO_PIN_RESET);
        }
        
        HAL_Delay(100);  // 延时100ms
    }
}

/* 按键中断处理函数 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    static uint32_t lastPressTime = 0;
    uint32_t currentTime = HAL_GetTick();
    
    if(GPIO_Pin == KEY_Pin)
    {
        if(currentTime - lastPressTime > 50)  // 消抖
        {
            if(currentTime - lastPressTime > 1000)  // 长按
            {
                // 调节亮度
                brightness = (brightness + 25) % 125;
                if(brightness < 25) brightness = 25;
                if(ledState && boostEnabled)
                {
                    TIM3->CCR1 = (brightness * 1000) / 100;
                }
            }
            else  // 短按
            {
                ledState = !ledState;
                if(ledState)
                {
                    if(batteryVoltage >= BATTERY_LOW_THRESHOLD)
                    {
                        EnableBoost();
                        HAL_Delay(10);  // 等待升压稳定
                        if(CheckBoostVoltage())
                        {
                            TIM3->CCR1 = (brightness * 1000) / 100;
                        }
                        else
                        {
                            ledState = 0;
                            DisableBoost();
                        }
                    }
                }
                else
                {
                    TIM3->CCR1 = 0;
                    DisableBoost();
                }
            }
        }
        lastPressTime = currentTime;
    }
}

/* 升压控制函数 */
static void EnableBoost(void)
{
    HAL_GPIO_WritePin(BOOST_EN_GPIO_Port, BOOST_EN_Pin, GPIO_PIN_SET);
    boostEnabled = 1;
}

static void DisableBoost(void)
{
    HAL_GPIO_WritePin(BOOST_EN_GPIO_Port, BOOST_EN_Pin, GPIO_PIN_RESET);
    boostEnabled = 0;
}

static uint8_t CheckBoostVoltage(void)
{
    return (boostVoltage > (BOOST_VOLTAGE_TARGET - 100) && 
            boostVoltage < (BOOST_VOLTAGE_TARGET + 100));
} 