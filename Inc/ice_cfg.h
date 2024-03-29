/**
* @file     ice_cfg.h
* @brief
* @note
* @author   lizhongyu
* @date     2022/5/9
* @version  V1.0
* @par Copyright(c):  806277022@qq.com
* @par History:  2022/5/9 第一个版本V1.0
*/

#ifndef _ICE_CFG_H
#define _ICE_CFG_H

/*** 配置芯片的的型号, 目前支持3种, STM32系列, GD32F30X系列, RP2040(树莓派Pico) ***/
#define ICE_GD32F30X
//#define ICE_STM32
//#define ICE_RP2040
#if (defined (ICE_GD32F30X) + defined (ICE_STM32) + defined (ICE_RP2040) > 1)
#error "重复定义芯片"
#elif (defined (ICE_GD32F30X) + defined (ICE_STM32) + defined (ICE_RP2040) == 0)
#error "未定义芯片"
#endif


/************ 使能外设 ************/
#define ICE_IWDG    1  //看门狗
#define ICE_GPIO    1  //GPIO
#define ICE_EXTI    0  //外部中断
#define ICE_UART    0  //串口
#define ICE_PWM     1  //PWM
#define ICE_SPI     1  //SPI
#define ICE_I2C     0  //I2C
#define ICE_ADC     1  //ADC
#define ICE_PIO     0  //PIO

/************ 附加功能 ************/
#define ICE_FREERTOS        1   //启用freeRTOS
#define ICE_UART_DEBUG      0   //启用 printf 重定向至串口
#define ICE_EF_DEBUG        0   //使能 easyflash 打印输出

//添加各个平台的库文件
#ifdef ICE_GD32F30X
#include "gd32f30x.h"
#include "gd32f30x_libopt.h"
//#include "gd32f30x_it.h"
#endif

#ifdef ICE_STM32
#include "main.h"
#endif

#ifdef ICE_RP2040
#include "hardware/irq.h"
#include "hardware/clocks.h"
#include <pico/stdlib.h>
#if ICE_GPIO
#include "hardware/gpio.h"
#endif
#if ICE_SPI
#include "hardware/spi.h"
#endif
#if ICE_PWM
    #include "hardware/pwm.h"
#endif
#if ICE_ADC
    #include "hardware/adc.h"
    #include "hardware/resets.h"
#endif
#if ICE_IWDG
    #include "hardware/watchdog.h"
#endif
#endif
#if ICE_PIO
#include "hardware/pio.h"
#endif

#ifdef ICE_DS18B20
#include "ds18b20.h"
#endif

#ifdef ICE_EASYFLASH
#include "easyflash.h"
#endif

#ifdef ICE_WS2812
#include "ws2812.pio.h"
#endif

#if ICE_UART_DEBUG
#include <stdio.h>
#endif

/*** 配置参数 ***/
//*************** 系统参数配置 ***************************************************************************************//
//-------------------------------------------------
#ifdef ICE_GD32F30X
#define ICE_SYS_CLK     (120 * 1000 * 1000)  //主频120MHz
#endif
//-------------------------------------------------
#ifdef ICE_STM32
#define ICE_SYS_CLK     (72 * 1000 * 1000)  //主频72MHz
#endif
//-------------------------------------------------
#ifdef ICE_RP2040
#define ICE_SYS_CLK     (125 * 1000 * 1000)  //主频125MHz
#define PLL_SYS_KHZ     (ICE_SYS_CLK / 1000)
#endif
//-------------------------------------------------
#if ICE_FREERTOS
#include "FreeRTOS.h"
#include "task.h"
#ifdef ICE_STM32
#include "cmsis_os.h"
#endif
#endif

//************** 看门狗 配置 *****************************************************************************************//
#if ICE_IWDG
#define ICE_IWDG_TIMEOUT  (4000)    //看门狗超时时间 4000 ms
#endif

//************** GPIO 配置 *******************************************************************************************//
#if ICE_GPIO
//-------------------------------------------------
#ifdef ICE_GD32F30X
#define LED0_Pin     GPIO_PIN_8   //
#define LED0_Port    GPIOB
#define LED0(x)      gpio_bit_write(LED0_Port, LED0_Pin, x)
#define LED0_IN      gpio_output_bit_get(LED0_Port, LED0_Pin)
#endif
//-------------------------------------------------
#ifdef ICE_STM32
#include "gpio.h"
#define LED_Port    GPIOA
#define LED_Pin     GPIO_PIN_2
#define LED(x)      HAL_GPIO_WritePin(LED_Port, LED_Pin, x)
#endif
//-------------------------------------------------
#ifdef ICE_RP2040
    #define LED_PIN    (29)    //LED_PIN ---> GP29
    #define LED(x)     gpio_put(LED_PIN, x)
    #define LED_IN     gpio_get(LED_PIN)
#endif

#endif
//************** 外部中断 配置 *****************************************************************************************//
#if ICE_EXTI
//-------------------------------------------------
#ifdef ICE_GD32F30X
    #define PWR_EN_Pin      GPIO_PIN_12   //外部输入使能引脚
    #define PWR_EN_Port     GPIOB
    #define PWR_EN_IN       gpio_input_bit_get(PWR_EN_Port, PWR_EN_Pin)
#endif
//-------------------------------------------------
#ifdef ICE_STM32
#endif
//-------------------------------------------------
#ifdef ICE_RP2040
#endif
#endif
//************** 串口 配置 ********************************************************************************************//
#if ICE_UART
#define ICE_UART_BAUD           (115200U) //uart baud
#define ICE_UART_DMA_SIZE       (256)     //uart dma rx size DMA接收区缓冲大小
#define ICE_UART_PACKET_SIZE    (6)       //packet size 一帧数据大小
//-------------------------------------------------
#ifdef  ICE_GD32F30X
#define ICE_UARTx               (USART1)    //USARTx,   //USART0, TX:PA9,  RX:PA10, RX_DMA: DMA0_CH4
#define ICE_UARTx_RCU1          (RCU_USART1)            //USART1, TX:PA2,  RX:PA3,  RX_DMA: DMA0_CH5
#define ICE_UARTx_IRQn          (USART1_IRQn)           //USART2, TX:PB10, RX:PB11, RX_DMA: DMA0_CH2
#define ICE_UARTx_RCU2          (RCU_GPIOA)
#define ICE_UARTx_Port          (GPIOA)
#define ICE_UARTx_Tx_Pin        (GPIO_PIN_2)
#define ICE_UARTx_Rx_Pin        (GPIO_PIN_3)
#define ICE_UARTx_DMAx          (DMA0)
#define ICE_UARTx_DMAx_RCU      (RCU_DMA0)
#define ICE_UARTx_DMAx_Rx_CH    (DMA_CH5)
#endif

#ifdef ICE_STM32
#include "dma.h"
#include "usart.h"

#define ICE_UARTx huart1
#endif

#endif
//************** SPI 配置 ********************************************************************************************//
#if ICE_SPI
#define ICE_SPI_MASTER  (0)
#define ICE_SPI_SLAVE   (1)
#define ICE_SPI_MODE    ICE_SPI_SLAVE //选择spi主/从?
//-------------------------------------------------
#ifdef ICE_GD32F30X
#define ICE_SPIx                (SPI1)
#define ICE_SPIx_RCU1           (RCU_SPI1)
#define ICE_SPIx_RCU2           (RCU_GPIOB)
#define ICE_SPIx_Port           (GPIOB)
#define ICE_SPIx_CS_Pin         (GPIO_PIN_12)
#define ICE_SPIx_SCK_Pin        (GPIO_PIN_13)
#define ICE_SPIx_MISO_Pin       (GPIO_PIN_14)
#define ICE_SPIx_MOSi_Pin       (GPIO_PIN_15)
__STATIC_INLINE void spi_write(__IO uint32_t spi_periph, uint16_t data) {
    while(!(SPI_STAT(spi_periph) & SPI_FLAG_TBE));
    SPI_DATA(spi_periph) = data;
}
#if (ICE_SPI_MODE == ICE_SPI_SLAVE) //spi从机采用dma接收
#define ICE_SPIx_DMAx           (DMA0)
#define ICE_SPIx_DMAx_RCU       (RCU_DMA0)
#define ICE_SPIx_DMAx_SIZE      (2)     //DMA size
#define ICE_SPIx_DMAx_Rx_CH     (DMA_CH3)
#define ICE_SPIx_DMAx_Rx_IRQn   (DMA0_Channel3_IRQn)
#else

#endif
#endif
#ifdef ICE_STM32
#endif
#ifdef ICE_RP2040
#define ICE_SPI_ID          spi0
#define ICE_SPI_CLK         (2 * 1000 * 1000) //2MHz //spi 时钟频率
#define ICE_SPI_MISO_Pin    (0)  //MISO Pin ---> GP0
#define ICE_SPI_SCK_Pin     (2)  //SCK Pin ---> GP2
#define ICE_SPI_MOSI_Pin    (3)  //MOSI Pin ---> GP3
#define ICE_SPI_CS_Pin      (1)  //CS Pin ---> GP1
#define ICE_SPI_CS(x)       gpio_put(ICE_SPI_CS_Pin, x)
#define ICE_SPI_CPOL        (0)  //时钟极性, 0:低, 1:高
#define ICE_SPI_CPHA        (0)  //时钟相位, 0:1边沿采样, 1:2边沿采样
#define ICE_SPI_MSB_FIRST   (1)  //MSB在前
#define ICE_SPI_HARD_CS     (0)  //硬件CS, 0:失能, 1:使能
#endif
//-------------------------------------------------
//-------------------------------------------------
#endif
//-------------------------------------------------
//************** ADC 配置 ********************************************************************************************//
#if ICE_ADC /* adc defines */
#define ICE_ADC_TEMP_SENSOR     (0)  //内部温度传感器使能
//-------------------------------------------------
#ifdef ICE_GD32F30X
#define ADC_BIT_NUM         (12U)           //GD32F30X 为 12bit adc
#define ICE_ADCx            (ADC0)          //ADC0, DMA0_CH0
#define ICE_ADCx_RCU        (RCU_ADC0)      //ADC1, 无DMA通道
#define ICE_ADCx_DMAx       (DMA0)
#define ICE_ADCx_DMAx_RCU   (RCU_DMA0)
#define ICE_ADCx_DMAx_CH    (DMA_CH0)
#define ICE_ADCx_DMAx_IRQn  (DMA0_Channel0_IRQn)
#define ICE_ADCx_MAX_NUMS   (18)            //ADC最大通道数
#define ICE_ADCx_CH_NUMS    (3)             //ADC通道数

#define ADC_VOLT_Port       GPIOA           //PB0: ADC01_IN8, PA2: ADC012_IN2
#define ADC_VOLT_Pin        GPIO_PIN_2      //PB1: ADC01_IN9, PA3: ADC012_IN3
#define ADC_VOLT_CH         ADC_CHANNEL_2
#define ADC_VOLT_RANK       (0)

#define ADC_CURT_Port       GPIOA
#define ADC_CURT_Pin        GPIO_PIN_3
#define ADC_CURT_CH         ADC_CHANNEL_3
#define ADC_CURT_RANK       (1)
#endif
//-------------------------------------------------
#ifdef ICE_STM32
#endif
//-------------------------------------------------
#ifdef ICE_RP2040
#define ADC_BIT_NUM     (12U)  //RP2040 为 12bit adc
#define ADC_VOLT_Pin    (27)   //GP27 -> ADC1
#define ADC_VOLT_CH     (1)
#endif
//-------------------------------------------------
#ifndef ADC_BIT_NUM
#define ADC_BIT_NUM     (12U) //adc 位数
#endif
#define ICE_ADC_VALUE_MAX       (1 << ADC_BIT_NUM) // adc最大值
#define ICE_ADC_VOLT_MAX        (3.3f)      // adc最大值对应的实际电压3.3V
#define ICE_ADC_VOLT_MV_MAX     (3300.0f)   // adc最大值对应的实际电压3300mV
#endif
//************** PWM 配置 ********************************************************************************************//
#if ICE_PWM /* PWM defines */
//-------------------------------------------------
#ifdef ICE_GD32F30X
    #define ICE_PWM_PCLK    RCU_GPIOB   //PB0 -> TIMER2_CH2, 不需要重映射IO
    #define ICE_PWM_TCLK    RCU_TIMER2
    #define ICE_PWM_Port    GPIOB
    #define ICE_PWM_Pin     GPIO_PIN_0
    #define ICE_PWM_TIMER   TIMER2
    #define ICE_PWM_CH      TIMER_CH_2
#endif
//-------------------------------------------------
#ifdef ICE_STM32
#endif
//-------------------------------------------------
#ifdef ICE_RP2040
    #define ICE_PWM_Pin     (20)    //GP20->PWM
#endif
//-------------------------------------------------
#define ICE_PWM_FREQ    (12 * 1000)  // 配置 PWM 频率为: 12kHz, 默认占空比为50%,
                                     // 默认输出极性为高, 即计数器小于比较值输出为高电平
#define ICE_PWM_PERIOD  (ICE_SYS_CLK / ICE_PWM_FREQ)

#if (ICE_PWM_PERIOD > (UINT16_MAX + 1) || ICE_PWM_PERIOD == 0)
#error "PWM 频率设置出现错误, 可能溢出了"
#endif
#endif
//************** PIO 配置 ********************************************************************************************//
#if ICE_PIO
#ifdef ICE_RP2040
#define ICE_PIO0    pio0    //PIO 0
#define ICE_SM0     0       //状态机0
#endif
#endif
//************** ds18b20 配置 ****************************************************************************************//
#ifdef ICE_DS18B20 /* ds18b20 defines */
//-------------------------------------------------
#ifdef ICE_GD32F30X
    #define      DS18B20_DQ_SCK_ENABLE()    rcu_periph_clock_enable(RCU_GPIOB)
    #define      DS18B20_DQ_GPIO_PORT       GPIOB
    #define      DS18B20_DQ_GPIO_PIN        GPIO_PIN_15
    #define      DS18B20_DQ(x)              gpio_bit_write(DS18B20_DQ_GPIO_PORT, DS18B20_DQ_GPIO_PIN, x)
#endif
//-------------------------------------------------
#ifdef ICE_STM32
#endif
//-------------------------------------------------
#ifdef ICE_RP2040
#endif
#endif
//************** easyflash 配置 **************************************************************************************//
#ifdef ICE_EASYFLASH /* easyflash defines */
//-------------------------------------------------
#ifdef ICE_GD32F30X
    #define ICE_FLASH_PAGE_SIZE     (2048)  //2KB, GD32F30X 页大小
    #define ICE_EF_WRITE_GRAN       (32)    //only support 1(nor flash)/ 8(stm32f4)/ 32(stm32f1)
    #define ICE_EF_START_ADDR       (FLASH_BASE + 200 * ICE_FLASH_PAGE_SIZE)  //easyflash 起始地址
    #define ICE_ENV_AREA_SIZE       (20 * ICE_FLASH_PAGE_SIZE)  //easyflash环境变量存储空间大小为 20 * 2 = 40KB
#endif
//-------------------------------------------------
#ifdef ICE_STM32
#endif
//-------------------------------------------------
#ifdef ICE_RP2040
#endif
//-------------------------------------------------
#define ICE_EF_ENV_VER_NUM      (0)  //添加新的环境变量后需要+1
#endif
//************** WS2812 配置 *****************************************************************************************//
#ifdef ICE_WS2812
#define RED     (0xFF0000) //红
#define ORANGE  (0xFF7F00) //橙
#define YELLOW  (0xFFFF00) //黄
#define GREEN   (0x00FF00) //绿
#define INDIGO  (0x007FFF) //青
#define BLUE    (0x0000FF) //蓝
#define PURPLE  (0x8B00FF) //紫

#ifdef ICE_RP2040
#define WS2812_Pin    (28)  //ws2812 pin
#endif
#endif

#endif //_ICE_CFG_H
