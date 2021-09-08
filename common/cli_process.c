/**
  ******************************************************************************
  * @file    cli_process.c
  */

/* Includes ------------------------------------------------------------------*/

//#include "timeserver.h"
#include "usart.h"
#include "UsartShell.h"
#include "cli_process.h"
#include "modbus_test.h"

extern uint8_t rx_chr;
extern uint8_t modbus_rx_buffer[MAX_READ_PER_TRANSACTION];
extern uint8_t current_index;


void main_handle_cli(void)
{
	int i = 0;
	//static TimerEvent_t cli_timeout_timer;
	
	//check for changing seconds, to manage the count-down
	//this will be unaffected by timer overflow, as it only returns 0-60 anyway.
	
	//uint8_t previous_second = HW_RTC_GetSecond();
	int previous_second = HAL_GetTick();
	//we need a 1 second timeout, and a 5 minute timeout
	//initialise a timer
	//TimerInit(&cli_timeout_timer, &cli_timeout_timer_event);
	//TimerStop(&cli_timeout_timer);
	//TimerSetValue(&cli_timeout_timer, 300000);
	//TimerStart(&cli_timeout_timer);
	
	Debug_printf("Press any key to enter CLI within the next 30 seconds\r\n");
	await_uart_tx();
	//allocate 30 seconds on boot for a user to activate the cli
	//clear the cliActive flag, without disabling the UART-RX
	Debug_disableCli(0);
	
	for(i=30;i>0;i--)
	{
		Debug_printf("%02d...\r\n",i);
		await_uart_tx();
		//while(previous_second == HW_RTC_GetSecond())
		while(HAL_GetTick()-previous_second <= 1000)
		{
			await_uart_tx();
			while(Debug_cliActive())
			{
				await_uart_tx();
				if(vComShellTask())
				{
					//update timeout to 5 minutes
					//TimerReset(&cli_timeout_timer);
				}
				
				//if the timeout expired, and we haven't just finished processing a command
				//then disable the CLI
				//if(timer_expired(&cli_timeout_timer))
			//	{
				//	Debug_disableCli(1);
			//	}
				
				//if we have entered and exited the cli, then we can resume without
				//completing the timeout
				if(!Debug_cliActive())
				{
					i = 0;
				}
			}
		}
		//previous_second = HW_RTC_GetSecond();
	}
	
	//ensure that the timer is removed from the linked-list before sending it out of scope.
//	TimerStop(&cli_timeout_timer);
	//reload the config and data after the cli, in case there were changes made
//	load_config();
//	device.load_data();
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{

}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{	
	
	if(huart->Instance == LPUART1)
	{ 
		
		modbus_rx_buffer[current_index++] = rx_chr;
		HAL_UART_Receive_IT(&hlpuart1, &rx_chr,1); // save char from uart receive
	}

}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
