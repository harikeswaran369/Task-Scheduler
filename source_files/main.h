/*
 * main.h
 *
 *  Created on: Oct 10, 2025
 *      Author: harik
 */

#ifndef MAIN_H_
#define MAIN_H_

#define MAX_TASKS      5

/*Stack memory calculations*/

#define SIZE_TASK_STACK   		   1024U    			// 1Kb
#define SIZE_SCHED_STACK  		   1024U    			// 1kb

#define SRAM_START                 0x20000000U
#define SIZE_SRAM                  ( (128) * (1024) )   // 128kb
#define SRAM_END                   ( (SRAM_START) + (SIZE_SRAM) )

#define T1_STACK_START             SRAM_END
#define T2_STACK_START             ( (SRAM_END) - (1 * SIZE_TASK_STACK) )
#define T3_STACK_START      	   ( (SRAM_END) - (2 * SIZE_TASK_STACK) )
#define T4_STACK_START   	       ( (SRAM_END) - (3 * SIZE_TASK_STACK) )
#define IDLE_STACK_START           ( (SRAM_END) - (4 * SIZE_TASK_STACK) )
#define SCHED_STACK_START          ( (SRAM_END) - (5 * SIZE_TASK_STACK) )

#define TICK_HZ                    1000U 				// 1KHz
#define HSI_CLOCK                  16000000U 		    // 16MHz
#define SYSTICK_TIM_CLK            HSI_CLOCK

#define TASK_READY_STATE     	   0x00
#define TASK_BLOCKED_STATE   	   0xFF


#define DUMMY_XPSR          	   0x01000000U

#define INTERRUPT_DISABLE()  do{__asm volatile ("MOV R0,#0x01");  __asm volatile ("MSR PRIMASK,R0");}while(0)

#define INTERRUPT_ENABLE()  do{__asm volatile ("MOV R0,#0x00");  __asm volatile ("MSR PRIMASK,R0");}while(0)

/*Prototypes for the function used in the application*/
void task1_handler(void);  // This is task-1
void task2_handler(void);  // This is task-2
void task3_handler(void);  // This is task-3
void task4_handler(void);  // This is task-4 of the application
void init_systick_timer(uint32_t tick_hz);
__attribute__((naked))void init_scheduler_stack(uint32_t sched_top_of_stack);
void init_tasks_stack(void);
void enable_processor_faults(void);
__attribute__((naked)) void switch_sp_to_psp(void);
__attribute__((naked)) void PendSV_Handler(void);
uint32_t get_psp_value(void);
void save_psp_value(uint32_t current_psp_value);
void update_next_task(void);
void task_delay(uint32_t tick_count);
void idle_task(void);

/*Task control Block*/
typedef struct
{
	uint32_t psp_value;
	uint32_t block_count;
	uint8_t current_state;
	void (*task_handler)(void);
}TCB_t;

#endif /* MAIN_H_ */
