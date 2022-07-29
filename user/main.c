#include "stm32f37x.h"
#include "sdadc.h"
#include "adc.h"
#include "uart.h"
#include "systick.h"
#include "stm32f37x_it.h"
#include <stdio.h>
#include "exit.h"
#include "time.h"

//extern void USART_Configuration(void);
/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
//extern uint8_t battery;
//extern uint8_t start;

int main(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    RCC_ClocksTypeDef RCC_Clocks;
    RCC_GetClocksFreq(&RCC_Clocks);
    SystemInit();
    Systick_Init();
    USART_Configuration();
	
RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOE, &GPIO_InitStruct);
    GPIO_ResetBits(GPIOE, GPIO_Pin_3);

    
/* Infinite loop */
        while (1)
					{
       					
			   	}
      
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
