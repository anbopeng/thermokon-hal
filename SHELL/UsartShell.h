/* This header file is part of the ATMEL AVR32-SoftwareFramework-AT32UC3-1.5.0 Release */

/*This file has been prepared for Doxygen automatic documentation generation.*/
/*! \file *********************************************************************
 *
 * \brief Control Panel COM1 shell module.
 *
 * This module manages a command shell on COM1.
 *
 * - Compiler:           GNU GCC for AVR32
 * - Supported devices:  All AVR32 devices.
 *
 * \author               Atmel Corporation: http://www.atmel.com \n
 *                       Support and FAQ: http://support.atmel.no/
 *
 *****************************************************************************/

/* Copyright (c) 2009 Atmel Corporation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an Atmel
 * AVR product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE
 *
 */
#ifndef COM1SHELL_H
#define COM1SHELL_H

#include "shell.h"
#include <stdbool.h>


#define dbg_print( _CONST_STRING ) 				Debug_printf( _CONST_STRING )

#define dbg_printf( _CONST_STRING, _A... ) 		Debug_printf(_CONST_STRING, _A)



/*!
 * Start the COM1 shell module.
 */
void cli_init( void  );

/*!
 * \brief Stop the com1shell module resources.
 */ 
void v_com1shell_stopResources( void );

/*!
 * Return the status of the COM1 shell module.
 * \return one of the eStatus enum value.
 */
eStatus xCom1Shell_GetStatus( void );


/*!
 *  \brief Print a string to the COM1 port.
 *
 *  \param pcString Input. The string to print.
 */
void vcom1shell_PrintMsg(const char *pcString);

/*!
 *  \brief Put a char to the COM1 port.
 *
 *????\param cByte Input. The char to print.
 */
void vcom1shell_PutChar( char cByte);

/*!
 *  \brief Get a char from the COM1 port.
 *
 * ??\param pcByte     Output. The char received from the COM1 port.
 */
signed long com1shell_GetChar(char *pcByte);

/*! 
 * \brief Mount default local drive 'a:'
 */ 
void v_com1shell_mount_local_drive( void );

void cli_output_data(char *data, unsigned short length);

bool vComShellTask( void );


#endif
