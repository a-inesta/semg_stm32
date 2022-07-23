#include "stm32f37x.h"
#include "sdadc.h"
#include "adc.h"
#include "uart.h"
#include "systick.h"
#include "stm32f37x_it.h"
#include <stdio.h>
#include "exit.h"
#include "time.h"
#include "math.h"

//extern void USART_Configuration(void);
/**
  * @brief  Main program.
  * @param  None	��������������11	
  * @retval None
  */

//extern uint8_t start;
uint8_t i = 0;

void send_data(unsigned char *p)
{
    int m, u = 0;
    unsigned char C[127] = {0};
    for(u = 0; u < 10; u++)
    {
        for(m = 0; m < 127; m++)
        {
            C[m] = p[u * 127 + m];
        }
        UART_Send(C, 127);
        Delay_ms(2);
    }
    for(m = 0; m < 126; m++)
    {
        C[m] = p[1270 + m];
    }
    C[126] = battery;
    UART_Send(C, 127);
}





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

		ADC14_Config();//������ʱһ���Ӳ����� 
    /* POT_SDADC channel1P (in Single Ended Zero Reference mode) configuration using
       injected conversion with continuous mode enabled */
		Delay_ms(1000);
    if(SDADC1_Config() != 0)//��ʼ��sdadc
    {		


        /* Forever loop */
        while(1) ;
    }
    else
    {
        TIM3_Int_Init(4000 - 1, 9 - 1);	//��ʱ�����ʱ����㷽��:Tout=((arr+1)*(psc+1))/72M=2000hz us.
        //TIM_Cmd(TIM3, ENABLE); //ʹ�ܶ�ʱ��3
        EXIT_IO_Init();//�ȴ���ʼ�ɼ�ָ��

        /* Infinite loop */
        while (1)
        {
					//WAITING send 

					if(start == 1)
            {
                send_data(B);
                start = 0;
							if (emg_en == 0) {
								//�رն�ʱ��
								TIM_Cmd(TIM3, DISABLE);
							}
						
            }
						
//            if(stamp_cnt == 10)
//            {
//       //regress
//          avr_timestamp=sum1(H_timestamp);
//					avr_timestamp=avr_timestamp / 10;
//					avr_centerstamp=sum(center_timestamp) ;
//					avr_centerstamp=avr_centerstamp/10;
//               for( i = 0;  i < 10; i++)
//							{
//                x1[i] = center_timestamp[i+1]  - avr_centerstamp;
//							  y1[i] = H_timestamp[i+1]  - avr_timestamp;
//							}
//                for( i = 0;  i < 10; i++)
//							{
//                    z [i] = x1[i] * y1[i] ;
//                    x2[i]  =x1[i]  * x1[i] ;
//                }
//                b1 = sum2(z) / sum2(x2)/40000000;
//                //b2 = mean(y) - b1 * mean(x)
////����
//                //TIM3_Int_Init(4000 *b1- 1, 9 - 1);	//��ʱ�����ʱ����㷽��:Tout=((arr+1)*(psc+1))/72M=2000hz us.
//                changeflag = 0;
//								osc_count=0;
//                stamp_cnt = 0;
//                
//								//     unsigned char C[40] = {0};
////                for( i = 0;  i < 10; i++) {
////                    C[4 * i + 3] = H_timestamp[i + 1];
////                    C[4 * i + 2] = H_timestamp[i + 1] >> 8;
////                    C[4 * i + 1] = H_timestamp[i + 1] >> 16;
////                    C[4 * i] = H_timestamp[i + 1] >> 24;
////                }
////                UART_send_byte(0x99);
////                UART_send_byte(0x99);
////                UART_Send(center_timestamp, 10);
////                UART_Send(C, 40);
//            }
        }
    }
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/