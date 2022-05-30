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
    Filename:       OSAL_SimpleBLEPeripheral.c
    Revised:
    Revision:

    Description:    This file contains function that allows user setup tasks



**************************************************************************************************/

/**************************************************************************************************
                                              INCLUDES
 **************************************************************************************************/
#if (APP_CFG == 0)
#include "OSAL.h"
#include "OSAL_Tasks.h"
#include "osal_cbTimer.h"

/* LL */
#include "ll.h"

/* HCI */
#include "hci_tl.h"

#if defined ( OSAL_CBTIMER_NUM_TASKS )
    #include "osal_cbTimer.h"
#endif

/* L2CAP */
#include "l2cap.h"

/* gap */
#include "gap.h"
#include "gapgattserver.h"
#include "gapbondmgr.h"

/* GATT */
#include "gatt.h"

#include "gattservapp.h"

/* Profiles */
#include "peripheral.h"

/* Application */
#include "simpleBLEPeripheral.h"

#include "board.h"
#include "clock.h"

/*********************************************************************
    GLOBAL VARIABLES
*/


uint8_t test_TaskID;

uint16 test_task(uint8 task_id, uint16 events)
{
		hal_gpio_write(GPIO_P31, 0);
		hal_gpio_write(GPIO_P32, 0);
		hal_gpio_write(GPIO_P33, 1);
		WaitMs(300);
		hal_gpio_write(GPIO_P31, 0);
		hal_gpio_write(GPIO_P32, 1);
		hal_gpio_write(GPIO_P33, 0);
		WaitMs(300);
		hal_gpio_write(GPIO_P31, 0);
		hal_gpio_write(GPIO_P32, 1);
		hal_gpio_write(GPIO_P33, 1);
		WaitMs(300);
		hal_gpio_write(GPIO_P31, 1);
		hal_gpio_write(GPIO_P32, 0);
		hal_gpio_write(GPIO_P33, 0);
		WaitMs(300);
		hal_gpio_write(GPIO_P31, 1);
		hal_gpio_write(GPIO_P32, 0);
		hal_gpio_write(GPIO_P33, 1);
		WaitMs(300);
		hal_gpio_write(GPIO_P31, 1);
		hal_gpio_write(GPIO_P32, 1);
		hal_gpio_write(GPIO_P33, 0);
		WaitMs(300);
		hal_gpio_write(GPIO_P31, 1);
		hal_gpio_write(GPIO_P32, 1);
		hal_gpio_write(GPIO_P33, 1);
		WaitMs(300);
		hal_gpio_write(GPIO_P31, 0);
		hal_gpio_write(GPIO_P32, 0);
		hal_gpio_write(GPIO_P33, 0);
		WaitMs(300);
	
	
	
		return 1;
}

void test_init(uint8 task_id)
{
		osal_set_event(task_id, 1);

}

// The order in this table must be identical to the task initialization calls below in osalInitTask.
const pTaskEventHandlerFn tasksArr[] =
{
    LL_ProcessEvent,                                                  // task 0
    HCI_ProcessEvent,                                                 // task 1
    #if defined ( OSAL_CBTIMER_NUM_TASKS )
    OSAL_CBTIMER_PROCESS_EVENT( osal_CbTimerProcessEvent ),           // task 3
    #endif
    L2CAP_ProcessEvent,                                               // task 2
    SM_ProcessEvent,                                                  // task 3
    GAP_ProcessEvent,                                                 // task 4
    GATT_ProcessEvent,                                                // task 5
    GAPRole_ProcessEvent,                                             // task 6
    #if (DEF_GAPBOND_MGR_ENABLE==1)
    GAPBondMgr_ProcessEvent,                                          // task , add 2017-11-15
    #endif
    GATTServApp_ProcessEvent,                                         // task 7
    SimpleBLEPeripheral_ProcessEvent,                                 // task 8
    phy_timer_ProcessEvent,                                           // task 9
		test_task,

};

const uint8 tasksCnt = sizeof( tasksArr ) / sizeof( tasksArr[0] );
uint16* tasksEvents;

/*********************************************************************
    FUNCTIONS
 *********************************************************************/

/*********************************************************************
    @fn      osalInitTasks

    @brief   This function invokes the initialization function for each task.

    @param   void

    @return  none
*/
void osalInitTasks( void )
{
    uint8 taskID = 0;
    tasksEvents = (uint16*)osal_mem_alloc( sizeof( uint16 ) * tasksCnt);
    osal_memset( tasksEvents, 0, (sizeof( uint16 ) * tasksCnt));
    /* LL Task */
    LL_Init( taskID++ );
    /* HCI Task */
    HCI_Init( taskID++ );
    #if defined ( OSAL_CBTIMER_NUM_TASKS )
    /* Callback Timer Tasks */
    osal_CbTimerInit( taskID );
    taskID += OSAL_CBTIMER_NUM_TASKS;
    #endif
    /* L2CAP Task */
    L2CAP_Init( taskID++ );
    /* SM Task */
    SM_Init( taskID++ );
    /* GAP Task */
    GAP_Init( taskID++ );
    /* GATT Task */
    GATT_Init( taskID++ );
    /* Profiles */
    GAPRole_Init( taskID++ );
    #if(DEF_GAPBOND_MGR_ENABLE==1)
    GAPBondMgr_Init( taskID++ );          // 2017-11-15
    #endif
    GATTServApp_Init( taskID++ );
    /* Application */
    SimpleBLEPeripheral_Init( taskID++ );
    /* Timer */
    phy_timer_init( taskID++ );
		
		test_init(taskID++);
		
}
#endif
/*********************************************************************
*********************************************************************/
