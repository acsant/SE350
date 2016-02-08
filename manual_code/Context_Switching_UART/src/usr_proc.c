/**
 * @file:   usr_proc.c
 * @brief:  Two user processes: proc1 and proc2
 * @author: Yiqing Huang
 * @date:   2014/02/28
 * NOTE: Each process is in an infinite loop. Processes never terminate.
 */

#include "rtx.h"
#include "uart_polling.h"
#include "usr_proc.h"

#ifdef DEBUG_0
#include "printf.h"
#endif /* DEBUG_0 */

/* initialization table item */
PROC_INIT g_test_procs[NUM_TEST_PROCS];

void set_test_procs() {
	int i;
	for( i = 0; i < NUM_TEST_PROCS; i++ ) {
		g_test_procs[i].m_pid=(U32)(i+1);
		g_test_procs[i].m_stack_size=0x100;
	}
  
	g_test_procs[0].mpf_start_pc = &proc1;
	g_test_procs[0].m_priority=LOW;

	g_test_procs[1].mpf_start_pc = &proc2;
	g_test_procs[1].m_priority=LOW;
	
	g_test_procs[2].mpf_start_pc = &proc3;
	g_test_procs[2].m_priority=LOW;
	
	g_test_procs[3].mpf_start_pc = &proc4;
	g_test_procs[3].m_priority=LOW;
	
	g_test_procs[4].mpf_start_pc = &proc5;
	g_test_procs[4].m_priority=HIGH;
	
	g_test_procs[5].mpf_start_pc = &proc6;
	g_test_procs[5].m_priority=HIGH;
}


/**
 * @brief: a process that prints 2x5 lowercase letters
 */
void proc1(void)
{
	int i = 0;
	int counter = 0;
	int ret_val = 100;
	while ( 1 ) {
		
		if ( i != 0 && i%5 == 0 ) {
			uart0_put_string("\n\r");
			counter++;
			if ( counter == 2 ) {
				//ret_val = set_process_priority(g_test_procs[1].m_pid , HIGH);
				break;
			} else {
				ret_val = release_processor();
			}
#ifdef DEBUG_0
			printf("proc1: ret_val = %d \n", ret_val);
#endif /* DEBUG_0 */
		}
		uart0_put_char('a' + i%10);
		i++;
	}
	uart0_put_string("proc1 end of testing\n\r");
	while ( 1 ) {
		release_processor();
	}
}

/*	
 * @brief: a process that prints 4x5 numbers 
 */
void proc2(void)
{
	int i = 0;
	int ret_val = 20;
	int counter = 0;
	void* mem_blk_t;
	while ( 1) {

		if ( i != 0 && i%5 == 0 ) {
			uart0_put_string("\n\r");
			counter++;
			/*if ( counter == 4 ) {
				//ret_val = set_process_priority(g_test_procs[0].m_pid , HIGH);
				break;
			} else {
				ret_val = release_processor();
			}*/
#ifdef DEBUG_0
			printf("proc2: ret_val=%d\n", ret_val);
#endif /* DEBUG_0 */
		}
		uart0_put_char('0' + i%10);
		i++;
	}
	uart0_put_string("proc2 end of testing\n\r");
	while ( 1 ) {
		release_processor();
	}
}

/**
 * @brief: a process that prints 5x6 `*` character
 *         and then yields the cpu.
 */
void proc3(void)
{
	int i = 0;
	int counter = 0;
	int ret_val = 100;
	while ( 1 ) {
		
		if ( i != 0 && i%5 == 0 ) {
			uart1_put_string("\n\r");
			counter++;
			if ( counter == 2 ) {
				ret_val = set_process_priority(g_test_procs[2].m_pid, LOW);
				break;
			} else {
				ret_val = release_processor();
			}
#ifdef DEBUG_0
			printf("proc3: ret_val = %d \n", ret_val);
#endif /* DEBUG_0 */
		}
		uart1_put_char('a' + i%10);
		i++;
	}
	uart1_put_string("proc3 end of testing\n\r");
	while ( 1 ) {
		release_processor();
	}
}

/**
 * @brief: a process that prints 5x6 even and odd numbers
 *         and then yields the cpu.
 */
void proc4(void)
{
		int i = 0;
	int ret_val = 20;
	int x = 0;
	void* returnedPtr;
	int p_priority;
	int counter = 0;
	while ( 1) {
		if ( i != 0 && i%5 == 0 ) {
			uart1_put_string("\n\r");
			//returnedPtr = request_memory_block();
			p_priority = get_process_priority(g_test_procs[2].m_pid);
			if ( i%30 == 0 ) {
				//set
				uart1_put_string("\n\r");
				counter++;
				if ( counter == 2 ) {
					ret_val = set_process_priority(g_test_procs[0].m_pid, HIGH);
				//	break;
				} else {
					ret_val = release_processor();
				}
#ifdef DEBUG_0
				printf("proc4: ret_val=%d\n", ret_val);
			
#endif /* DEBUG_0 */
			}
 			for ( x = 0; x < 500000; x++); // some artifical delay
		}
		uart1_put_char('x');
		i++;
	}
	while(1) {
		release_processor();
	}
}

/**
 * @brief: a process that prints 5x6 even and odd numbers
 *         and then yields the cpu.
 */
void proc5(void)
{
	int i = 0;
	int ret_val = 20;
	int x = 0;
	while ( 1) {
		if ( i != 0 && i%5 == 0 ) {
			uart1_put_string("\n\r");
			if ( i%30 == 0 ) {
				ret_val = release_memory_block((void*)0x1000041c);
				ret_val = release_processor();
#ifdef DEBUG_0
				printf("proc5: ret_val=%d\n", ret_val);
			
#endif /* DEBUG_0 */
			}
			//for ( x = 0; x < 500000; x++); // some artifical delay
		}
		uart1_put_char('&');
		i++;
	}
}

/**
 * @brief: a process that prints 5x6 even and odd numbers
 *         and then yields the cpu.
 */
void proc6(void)
{
	int i = 0;
	int ret_val = 20;
	int x = 0;
	void* returnedPtr;
	int p_priority;
	int count = 1;
	while ( 1) {
		if ( i != 0 && i%5 == 0 ) {
			uart1_put_string("\n\r");
			while (i < 1000000) {
					returnedPtr = request_memory_block();
			}
			if ( i%30 == 0 ) {
				ret_val = release_processor();
				p_priority = get_process_priority(count++);
				uart1_put_string("received priority:\n");
				uart1_put_char('0' + p_priority%10);
				if(count > NUM_TEST_PROCS) {
					count = 1;
				}
#ifdef DEBUG_0
				printf("proc6: ret_val=%d\n", ret_val);
			
#endif /* DEBUG_0 */
			}
 			for ( x = 0; x < 500000; x++); // some artifical delay
		}
		uart1_put_char('$');
		i++;
	}
}

