/******************************************************************************************************
*									Natcom Electronics (Pty) Ltd.
*									      P.O. Box 138
*										  Umbogintwini
*										 	  4120
*										 KZN South Africa
*
*                                        www.natcom.co.za
*
*                                       (c) Copyright 2011
*
* This document is protected under the Non Disclosure Agreement between Natcom Electronics and
* their customer. Copying of this document, disclosing it to third parties or using the contents
* thereof for any purposes without the express written authorisation from Natcom Electronics
* and their customer is strictly forbidden.  Any offenders are liable to pay all relevant damages.
* The copyright and the foregoing restrictions extended to all media in which the information may
* be embodied.
*
* @file              app_cli.c
*
* Programmer(s) :
*
* Description :     Command Line Interface
*
* Revision History :
* Changed By    Version    Date        Comments
* --------------------------------------------------------------------------------------------------
* RJH           00-00      2004/11/17  Creation
****************************************************************************************************
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "main.h"
//#include "hw.h"

#include "usart.h"

#include "cli_led.h"

//#include "global.h"

void cli_led_help()
{
	Debug_printf("Usage: led [error|txd|rxd|state] [on|off|toggle]\r\n");
	return;
}

void cli_led_implementation(int argc,   char *argv[])
{
			//turn on the LEDs
	int new_state = 0;
	if(argc == 2)
	{
		if(!strcmp(argv[1], "on"))
		{
			new_state = 1;
		}
		else if(!strcmp(argv[1], "off"))
		{
			new_state = 0;
		}
		else if(!strcmp(argv[1], "toggle"))
		{
			new_state = 2;
		}
		else
		{
			cli_led_help();
			return;
		}

		if(!strcmp(argv[0],"all"))
		{
			if(new_state == 1)
			{
				HAL_GPIO_WritePin(LED_ERROR_GPIO_Port, LED_ERROR_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(LED_TXD_GPIO_Port, LED_TXD_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(LED_RXD_GPIO_Port, LED_RXD_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(LED_STATE_GPIO_Port, LED_STATE_Pin,GPIO_PIN_RESET);
			}
			else if (new_state ==2)
			{
				HAL_GPIO_TogglePin(LED_ERROR_GPIO_Port, LED_ERROR_Pin);
				HAL_GPIO_TogglePin(LED_TXD_GPIO_Port, LED_TXD_Pin);
				HAL_GPIO_TogglePin(LED_RXD_GPIO_Port, LED_RXD_Pin);
				HAL_GPIO_TogglePin(LED_STATE_GPIO_Port, LED_STATE_Pin);
			}
			else
			{
				HAL_GPIO_WritePin(LED_ERROR_GPIO_Port, LED_ERROR_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(LED_TXD_GPIO_Port, LED_TXD_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(LED_RXD_GPIO_Port, LED_RXD_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(LED_STATE_GPIO_Port, LED_STATE_Pin,GPIO_PIN_SET);
			}
		}
		//ERROR led
		else if(!strcmp(argv[0], "error"))
		{
			if(new_state == 1)
				HAL_GPIO_WritePin(LED_ERROR_GPIO_Port, LED_ERROR_Pin,GPIO_PIN_RESET);
			else if (new_state ==2)
				HAL_GPIO_TogglePin(LED_ERROR_GPIO_Port, LED_ERROR_Pin);
			else
				HAL_GPIO_WritePin(LED_ERROR_GPIO_Port, LED_ERROR_Pin,GPIO_PIN_SET);;
		}
		//TXD led
		else if(!strcmp(argv[0], "txd"))
		{
			if(new_state == 1)
				HAL_GPIO_WritePin(LED_TXD_GPIO_Port, LED_TXD_Pin,GPIO_PIN_RESET);
			else if (new_state ==2)
				HAL_GPIO_TogglePin(LED_TXD_GPIO_Port, LED_TXD_Pin);
			else
				HAL_GPIO_WritePin(LED_TXD_GPIO_Port, LED_TXD_Pin,GPIO_PIN_SET);;
		}
		//RXD led
		else if(!strcmp(argv[0], "rxd"))
		{
			if(new_state == 1)
				HAL_GPIO_WritePin(LED_RXD_GPIO_Port, LED_RXD_Pin,GPIO_PIN_RESET);
			else if (new_state ==2)
				HAL_GPIO_TogglePin(LED_RXD_GPIO_Port, LED_RXD_Pin);
			else
				HAL_GPIO_WritePin(LED_RXD_GPIO_Port, LED_RXD_Pin,GPIO_PIN_SET);;
		}
		//STATE led
		else if(!strcmp(argv[0], "state"))
		{
			if(new_state == 1)
				HAL_GPIO_WritePin(LED_STATE_GPIO_Port, LED_STATE_Pin,GPIO_PIN_RESET);
			else if (new_state ==2)
				HAL_GPIO_TogglePin(LED_STATE_GPIO_Port, LED_STATE_Pin);
			else
				HAL_GPIO_WritePin(LED_STATE_GPIO_Port, LED_STATE_Pin,GPIO_PIN_SET);;
		}

		else
		{
			cli_led_help();
		}
	}
	else
	{
		cli_led_help();
	}
}


