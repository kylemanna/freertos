/*
    FreeRTOS V7.1.0 - Copyright (C) 2011 Real Time Engineers Ltd.
	

    ***************************************************************************
     *                                                                       *
     *    FreeRTOS tutorial books are available in pdf and paperback.        *
     *    Complete, revised, and edited pdf reference manuals are also       *
     *    available.                                                         *
     *                                                                       *
     *    Purchasing FreeRTOS documentation will not only help you, by       *
     *    ensuring you get running as quickly as possible and with an        *
     *    in-depth knowledge of how to use FreeRTOS, it will also help       *
     *    the FreeRTOS project to continue with its mission of providing     *
     *    professional grade, cross platform, de facto standard solutions    *
     *    for microcontrollers - completely free of charge!                  *
     *                                                                       *
     *    >>> See http://www.FreeRTOS.org/Documentation for details. <<<     *
     *                                                                       *
     *    Thank you for using FreeRTOS, and thank you for your support!      *
     *                                                                       *
    ***************************************************************************


    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation AND MODIFIED BY the FreeRTOS exception.
    >>>NOTE<<< The modification to the GPL is included to allow you to
    distribute a combined work that includes FreeRTOS without being obliged to
    provide the source code for proprietary components outside of the FreeRTOS
    kernel.  FreeRTOS is distributed in the hope that it will be useful, but
    WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
    or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
    more details. You should have received a copy of the GNU General Public
    License and the FreeRTOS license exception along with FreeRTOS; if not it
    can be viewed here: http://www.freertos.org/a00114.html and also obtained
    by writing to Richard Barry, contact details for whom are available on the
    FreeRTOS WEB site.

    1 tab == 4 spaces!

    http://www.FreeRTOS.org - Documentation, latest information, license and
    contact details.

    http://www.SafeRTOS.com - A version that is certified for use in safety
    critical systems.

    http://www.OpenRTOS.com - Commercial support, development, porting,
    licensing and training services.
*/

/*
	Changes from V2.5.2

	+ All LED's are turned off to start.
*/


#include "FreeRTOS.h"
#include "task.h"
#include "partest.h"

#define partstNUM_LEDs	4

#define LED0_POS		0x01
#define LED1_POS		0x04
#define LED2_POS		0x01
#define LED3_POS		0x04

static const unsigned portCHAR ucLEDDefinitions[ partstNUM_LEDs ] = { LED0_POS, LED1_POS, LED2_POS, LED3_POS };

/*-----------------------------------------------------------
 * Simple parallel port IO routines.
 *-----------------------------------------------------------*/

void vParTestInitialise( void )
{
	/* Set the LEDs to outputs. */
	MCF_GPIO_DDRTD |= ( LED0_POS | LED1_POS );
	MCF_GPIO_DDRTC |= ( LED2_POS | LED3_POS );

	/* Turn LEDs off. */
	MCF_GPIO_SETTC |= ( LED0_POS | LED1_POS );
	MCF_GPIO_SETTD |= ( LED2_POS | LED3_POS );
}
/*-----------------------------------------------------------*/

void vParTestSetLED( unsigned portBASE_TYPE uxLED, signed portBASE_TYPE xValue )
{
	if( uxLED < 2 )
	{
		if( xValue != 0 )
		{
			taskENTER_CRITICAL();
				MCF_GPIO_PORTTD |= ucLEDDefinitions[ uxLED ];
			taskEXIT_CRITICAL();
		}
		else
		{
			taskENTER_CRITICAL();
				MCF_GPIO_PORTTD &= ~ucLEDDefinitions[ uxLED ];
			taskEXIT_CRITICAL();
		}
	}
	else if( uxLED < 4 )
	{
		if( xValue != 0 )
		{
			taskENTER_CRITICAL();
				MCF_GPIO_PORTTC |= ucLEDDefinitions[ uxLED ];
			taskEXIT_CRITICAL();
		}
		else
		{
			taskENTER_CRITICAL();
				MCF_GPIO_PORTTC &= ~ucLEDDefinitions[ uxLED ];
			taskEXIT_CRITICAL();
		}
	}
}
/*-----------------------------------------------------------*/

void vParTestToggleLED( unsigned portBASE_TYPE uxLED )
{
	if( uxLED < 2 )
	{
		taskENTER_CRITICAL();
		{
			if( ( MCF_GPIO_PORTTD & ucLEDDefinitions[ uxLED ] ) == ( unsigned portCHAR ) 0 )
			{
				MCF_GPIO_PORTTD |= ucLEDDefinitions[ uxLED ];
			}
			else
			{
				MCF_GPIO_PORTTD &= ~ucLEDDefinitions[ uxLED ];
			}
		}
		taskEXIT_CRITICAL();
	}
	else if( uxLED < 4 )
	{
		taskENTER_CRITICAL();
		{
			if( ( MCF_GPIO_PORTTC & ucLEDDefinitions[ uxLED ] ) == ( unsigned portCHAR ) 0 )
			{
				MCF_GPIO_PORTTC |= ucLEDDefinitions[ uxLED ];
			}
			else
			{
				MCF_GPIO_PORTTC &= ~ucLEDDefinitions[ uxLED ];
			}
		}
		taskEXIT_CRITICAL();
	}
}

