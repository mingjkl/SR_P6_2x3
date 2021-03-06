/**************************************************************************************************

    Phyplus Microelectronics Limited confidential and proprietary.
    All rights reserved.

    IMPORTANT: All rights of this software belong to Phyplus Microelectronics
    Limited ("Phyplus"). Your use of this Software is limited to those
    specific rights granted under  the terms of the business contract, the
    confidential agreement, the non-disclosure agreement and any other forms
    of agreements as a customer or a partner of Phyplus. You may not use this
    Software unless you agree to abide by the terms of these agreements.
    You acknowledge that the Software may not be modified, copied,
    distributed or disclosed unless embedded on a Phyplus Bluetooth Low Energy
    (BLE) integrated circuit, either as a product or is integrated into your
    products.  Other than for the aforementioned purposes, you may not use,
    reproduce, copy, prepare derivative works of, modify, distribute, perform,
    display or sell this Software and/or its documentation for any purposes.

    YOU FURTHER ACKNOWLEDGE AND AGREE THAT THE SOFTWARE AND DOCUMENTATION ARE
    PROVIDED AS IS WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED,
    INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY, TITLE,
    NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT SHALL
    PHYPLUS OR ITS SUBSIDIARIES BE LIABLE OR OBLIGATED UNDER CONTRACT,
    NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR OTHER
    LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
    INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE
    OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT
    OF SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
    (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

**************************************************************************************************/

/**************************************************************************************************
    Filename:       SimpleBLEPeripheral_Main.c
    Revised:
    Revision:

    Description:    This file contains the main and callback functions for
                  the Simple BLE Peripheral sample application.

 **************************************************************************************************/
#if (APP_CFG == 0)
/**************************************************************************************************
                                             Includes
 **************************************************************************************************/
/* Hal Drivers */

/* OSAL */
#include "OSAL.h"
#include "OSAL_Tasks.h"
#include "OSAL_PwrMgr.h"
#include "osal_snv.h"
//#include "OnBoard.h"

#include "board.h"

#include "gpio.h"
#include "clock.h"

#include "ty_adc.h"



/**************************************************************************************************
    FUNCTIONS
 **************************************************************************************************/


/**************************************************************************************************
    @fn          main

    @brief       Start of application.

    @param       none

    @return      none
 **************************************************************************************************
*/




int app_main(void)
{

    /* Initialize the operating system */
    osal_init_system();

	  osal_pwrmgr_device( PWRMGR_BATTERY );
	
		hal_gpio_pin_init(GPIO_P31, GPIO_OUTPUT);
		hal_gpio_pin_init(GPIO_P32, GPIO_OUTPUT);
		hal_gpio_pin_init(GPIO_P33, GPIO_OUTPUT);
	
		hal_gpio_write(GPIO_P31, true);
		hal_gpio_write(GPIO_P32, false);
		hal_gpio_write(GPIO_P33, true);
	
//		hal_gpio_pin_init(GPIO_P11, GPIO_OUTPUT);
//	
//		hal_gpio_write(GPIO_P11, false);

		hal_gpio_pin_init(GPIO_P25, GPIO_INPUT);
	
		hal_gpio_pull_set(GPIO_P25, GPIO_FLOATING);
	
		// for(uint8_t i = 0; i < 5; i++)
		// {
		// 	hal_gpio_write(GPIO_P32, false);
		// 	WaitMs(200);
		// 	hal_gpio_write(GPIO_P32, true); 
		// 	WaitMs(200);
		// }
	



    /* Start OSAL */
    osal_start_system(); // No Return from here
		
    return 0;
}
#endif
/**************************************************************************************************
                                           CALL-BACKS
**************************************************************************************************/


/*************************************************************************************************
**************************************************************************************************/
