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
#include <stdint.h>

//HW_RTC.h must be before shell.h, due to conflict on the definition of CR!!
#include "usart.h"

#include "shell.h"
#include "UsartShell.h"
#include "app_cli.h"
#include "cli_led.h"
#include "internal_flash.h"



#define MAX_ANSWER_SIZE				64

#define OSAL_Const_String( _NAME, _VALUE ) const char _NAME [] = _VALUE


OSAL_Const_String(cmd_error_string, 	"ERR \r\n" 						);
OSAL_Const_String(cmd_ok_string, 		"OK \n\r"						);
OSAL_Const_String(cmd_help, 			"-h"							);
OSAL_Const_String(cmd_help_info, 		"Command parameters : \r\n" 	);
OSAL_Const_String(cmd_help_param_val, 	" [01..]" 						);
OSAL_Const_String(cmd_newline, 			"\n\r" 							); // use: dbg_print(cmd_newline);
OSAL_Const_String(cli_general_str_unsignedval, 	"%u" );

/*!
 * The array of commands registration.
 */
Cmd_registration a_cmd_registration[SHELL_NB_COMMANDS] = {
	{(char *) "!!"        , cli_help     , 0xFFFFFFFF}, // ALWAYS KEEP AS THE FIRST COMMAND IN THE ARRAY.
	{(char *) "help"      , cli_help     , 0xFFFFFFFF},
//	{(char *) "show"      , cli_show     , 0xFFFFFFFF},
	{(char *) "run"       , cli_run      , 0xFFFFFFFF},
	{(char *) "led"       , cli_led      , 0xFFFFFFFF},
//	{(char *) "modbus"    , cli_modbus   , 0xFFFFFFFF},
//	{(char *) "count"     , cli_count    , 0xFFFFFFFF},
//	{(char *) "flash"     , cli_flash    , 0xFFFFFFFF},
//	{(char *) "wakeup"    , cli_wakeup   , 0xFFFFFFFF},
//	{(char *) "rejoin"    , cli_rejoin   , 0xFFFFFFFF},
//	{(char *) "mode"      , cli_mode     , 0xFFFFFFFF},
//	{(char *) "time"      , cli_time     , 0xFFFFFFFF},
	{(char *) "test"      , cli_test     , 0xFFFFFFFF},
//	{(char *) "uplink"    , cli_uplink   , 0xFFFFFFFF},
//	{(char *) "gain"      , cli_gain     , 0xFFFFFFFF},
//	{(char *) "threshold" , cli_threshold, 0xFFFFFFFF},
//	{(char *) "device"    , cli_device   , 0xFFFFFFFF},
//	{(char *) "appeui"    , cli_appeui   , 0xFFFFFFFF},
//	{(char *) "appkey"    , cli_appkey   , 0xFFFFFFFF},
//	{(char *) "channel"   , cli_channel  , 0xFFFFFFFF},
	{(char *) "reboot"    , cli_reboot   , 0xFFFFFFFF},
	
};


#define PRINT_CLI_OK		dbg_print(cmd_ok_string);
#define PRINT_CLI_ERR		dbg_print(cmd_error_string);

const char *const FSCMDS_MSG_HELP            = (char *)"\
"CRLF\
"!! 		- Executes previous command."CRLF"\
help 		- This help."CRLF"\
shell 		- Shell version."CRLF"\
version 	- Firmware version information."CRLF;

eExecStatus cli_help( int argc,   char *argv[],
						    char **ppcStringReply )
{

	dbg_print("\r\n");
	dbg_print("HELP\n\r");
	dbg_print("-\n\r");

	dbg_print("led      : Individually control the on board leds\r\n");
	
	//for generic modbus, show this help
	//if(device.cli_commands & (cmd_modbus))
	{
		dbg_print("modbus   : Set modbus devices and registers to uplink\r\n");

	}

	//for any of the count commands, show this help
	//if(device.cli_commands & (cmd_count1 | cmd_count2 | cmd_count3))
	{
		dbg_print("count    : Re/Set the counters and set debounce interval\r\n");
	}
	
	//if(device.cli_commands & cmd_thresholds)
	{
		dbg_print("threshold: Set device alarm thresholds\r\n");
		await_uart_tx();
	}
	
	dbg_print("flash    : Save/load/erase configurationa nd data\r\n");
	await_uart_tx();
	dbg_print("mode     : Set the device mode\r\n");
	await_uart_tx();
	dbg_print("time     : Set or view the device time\r\n");
	await_uart_tx();
	dbg_print("wakeup   : Set the device wakeup interval\r\n");
	await_uart_tx();
	dbg_print("rejoin   : Set the device rejoin interval\r\n");
	await_uart_tx();
	dbg_print("uplink   : Set the device wakeup interval\r\n");
	await_uart_tx();
	dbg_print("appkey   : Get/Set the Device Appkey\r\n");
	await_uart_tx();
	dbg_print("appeui   : Get/Set the Device Appeui\r\n");
	await_uart_tx();
	dbg_print("channel  : Configure Default channel list for AU915\r\n");
	await_uart_tx();
	dbg_print("show     : Display all configuration information\r\n");
	await_uart_tx();
	dbg_print("help     : Display this message\r\n");
	await_uart_tx();


	return SHELL_EXECSTATUS_OK;
}

eExecStatus cli_run( int argc,   char *argv[], char **ppcStringReply )
{
	dbg_print("Running\r\n");
	//should these be enabled? do we want to save or discard by default?
//	save_config();
//	save_data();
	Debug_disableCli(1);
	return SHELL_EXECSTATUS_OK_NO_FREE;
}

eExecStatus cli_led( int argc, char *argv[], char **ppcStringReply )
{
	cli_led_implementation(argc, argv);
	return SHELL_EXECSTATUS_OK_NO_FREE;
}
/*
eExecStatus cli_modbus( int argc, char *argv[], char **ppcStringReply )
{
	cli_modbus_implementation(argc, argv);
	return SHELL_EXECSTATUS_OK_NO_FREE;
}
*/
/*
eExecStatus cli_flash( int argc, char *argv[], char **ppcStringReply )
{	
	cli_flash_implementation(argc, argv);
	return SHELL_EXECSTATUS_OK_NO_FREE;
}

*/
void cli_uplink_help()
{
	Debug_printf("Usage: uplink data\r\n");
	await_uart_tx();
	Debug_printf("\tGet data from a peripheral and send via LoRa\r\n");
	await_uart_tx();
	
	Debug_printf("Usage: uplink startup\r\n");
	await_uart_tx();
	Debug_printf("\tSend the startup packet via LoRa\r\n");
	await_uart_tx();
}

void cli_gain_help()
{
	Debug_printf("Usage: gain set [gain]\r\n");
	await_uart_tx();
	Debug_printf("\tSets the antenna gain to [gain] dB\r\n");
	await_uart_tx();
	
	Debug_printf("Usage: gain show\r\n");
	await_uart_tx();
	Debug_printf("\tPrints the current Antenna Gain value\r\n");
	await_uart_tx();
}

void cli_rejoin_help()
{
	Debug_printf("Usage: rejoin [interval]\r\n");
	await_uart_tx();
	Debug_printf("\tRejoin the LoRa network every [interval] hours\r\n");
	await_uart_tx();
	
	Debug_printf("Usage: rejoin show\r\n");
	await_uart_tx();
	Debug_printf("\tPrints the current rejoin interval in hours\r\n");
	await_uart_tx();
}


void cli_mode_help()
{
	Debug_printf("Usage: mode [mode_index]\r\n");
	await_uart_tx();
	Debug_printf("Valid options:\r\n");
	await_uart_tx();
	
//	list_device_modes();
	
	Debug_printf("Usage: mode show\r\n");
	await_uart_tx();
	Debug_printf("\tPrints the current device mode\r\n");
	await_uart_tx();
}


void cli_time_help()
{
	Debug_printf("Usage: time hour [value]\r\n");
	Debug_printf("\tSet the hours on the device to [value], 24Hr format (0-23)\r\n");
	await_uart_tx();
	Debug_printf("Usage: time minute [value]\r\n");
	Debug_printf("\tSet the minutes on the device to [value]\r\n");
	await_uart_tx();
	Debug_printf("Usage: time second [value]\r\n");
	Debug_printf("\tSet the seconds on the device to [value]\r\n");
	await_uart_tx();
	Debug_printf("Usage: time show\r\n");
	Debug_printf("\tShows the current time on the device\r\n");
	await_uart_tx();
}

eExecStatus cli_test( int argc, char *argv[], char **ppcStringReply )
{
	uint8_t flash_write_data[64];
	uint8_t flash_page0_backup[64];
	uint8_t flash_read_data[64] = {0};
	int matched = 1;
	int i;
	

	for(i=0;i<64;i++)
	{
		flash_write_data[i] = i;
	}
	
	if(argc >= 1)
	{
		/*
		if(!strcmp(argv[0],"all") || !strcmp(argv[0],"temp"))
		{
			
		}
		*/
		
		//Flash and I2C
		if(!strcmp(argv[0],"all") || !strcmp(argv[0],"flash"))
		{
			Debug_printf("\r\nFLASH & I2C\r\n");
			Debug_printf("Backing up page 0\r\n");
			flash_readblock(0,flash_page0_backup,64);
			
			
			Debug_printf("Writing Array to Flash Page 0\r\n");
			
			flash_writeblock(0, flash_write_data, 64);
			
			Debug_printf("Reading Array from Flash Page 0\r\n");
			
			flash_readblock(0,flash_read_data, 64);
			
			for(i=0; i<64; i++)
			{
				if(flash_read_data[i] != flash_write_data[i])
				{
					matched = 0;
				}
			}
			
			if(matched)
			{
				Debug_printf("Flash Check OK\r\n");
			}
			else
			{
				Debug_printf("Flash Check FAIL\r\n");
			}
			
			//clear the flash
			Debug_printf("Restoring Page 0\r\n");
			flash_writeblock(0,flash_page0_backup,64);
			
		}

		if(!strcmp(argv[0],"all") || !strcmp(argv[0],"led"))
		{
			Debug_printf("\r\nLED\r\n");
			Debug_printf("Toggling RED led pin\r\nPress Any key to contimue\r\n");

		}
		
		if(!strcmp(argv[0],"all") || !strcmp(argv[0],"uart"))
		{
			Debug_printf("\r\nUART\r\n");
			Debug_printf("Sending String on peripheral UART\r\nPress any key to continue\r\n");
		}
		
	}
	
	return SHELL_EXECSTATUS_OK_NO_FREE;
}

static uint8_t axtoi(char input)
{
	//handle simplest case (number) first.
	if(input >= '0' && input <= '9')
	{
		return input - '0';
	}
	
	input &= ~0x20;
	
	if(input >= 'A' && input <='F')
	{
		return  10 + (input - 'A');
	}
	
	return 0;
}


//assume that input is zero-terminated, ascii encoded, hex
void process_hexstring(char* input, char *output, int length)
{
	//notice that we are processing ascii encoded hex, so each character we read
	//is 4 bits
	int i = 0;
	//we also make the assumption that there are no characters outside [0-9,A-F]
	while(*input && i < length*2)
	{
		output[i>>1] = output[i>>1] << 4;
		output[i>>1] += axtoi(*input);
		input++;
		i++;
	}
}

void cli_appeui_help()
{
	Debug_printf("Usage: appeui set <value>\r\n");
	Debug_printf("\tSets the appeui to <value>\r\n");
	Debug_printf("\t<value> should be a 16-Character HEX string (8Bytes)\r\n");
	Debug_printf("Usage: appeui get \r\n");
	Debug_printf("\tPrints the currently configured APPEUI\r\n");
	Debug_printf("Usage: appeui random\r\n");
	Debug_printf("\tSets a random appeui\r\n");
}

void cli_appkey_help()
{
	Debug_printf("Usage: appkey set <value>\r\n");
	Debug_printf("\tSets the appkey to <value>\r\n");
	Debug_printf("\t<value> should be a 32-Character HEX string (16Bytes)\r\n");
	Debug_printf("Usage: appkey get \r\n");
	Debug_printf("\tPrints the currently configured APPKEY\r\n");
	Debug_printf("Usage: appkey default\r\n");
	Debug_printf("\tResets the appkey to defualt\r\n");
	Debug_printf("Usage: appkey random\r\n");
	Debug_printf("\tSets a random appkey\r\n");
}

eExecStatus cli_reboot( int argc, char *argv[], char **ppcStringReply )
{
	while(1);
}

/*
static void cli_channel_help()
{
	Debug_printf("NOTE: CHANNEL CONFIG ONLY FOR AU915\r\n");
	Debug_printf("NOTE: CLI CANNOT HANDLE MORE THAN 8 EXTRA ARGUMENTS\r\n");
	Debug_printf("Usage: channel add <ch 1> ... <ch n>\r\n");
	Debug_printf("\tAdd specified channels to the preconfigured channel list\r\n");
	Debug_printf("\tReplace the Channel arguments with \"All\" to add all channels\r\n");
	await_uart_tx();
	Debug_printf("Usage: channel remove <ch 1> ... <ch n>\r\n");
	Debug_printf("\tRemove specified channels from the preconfigured channel list\r\n");
	Debug_printf("\tReplace the Channel arguments with \"All\" to remove all channels\r\n");
	await_uart_tx();
	Debug_printf("Usage: channel show\r\n");
	Debug_printf("\tShows the currently enabled channels\r\n");
	await_uart_tx();
}
*/
