/* @brief: common defines and structs for both kernel and user 
 * @file: common.h 
 * @author: Yiqing Huang
 * @date: 2016/02/24
 */

#ifndef COMMON_H_
#define COMMON_H_

/* Definitions */

#define BOOL unsigned char

#define TRUE 1
#define FALSE 0
#define NULL 0
#define RTX_ERR -1
#define RTX_OK 0
#define NUM_TEST_PROCS 3
#define NUM_API_PROCS 7
#define NUM_TOTAL_PROCS 10
#define COMMAND_SIZE	3
#define MAX_COMMANDS	10
#define BUFFER_SIZE 15

/* Helper macros */
#define ARRAYSIZE(array) (sizeof(array)/sizeof(array[0]))
#define BLOCK_SIZE 128
#define MAX_BUFFER_SIZE (BLOCK_SIZE - sizeof(msgbuf*))

/* Hotkey macros */
#define HOTKEY1 '!'
#define HOTKEY2 '*'
#define HOTKEY3 '$'

/* Process IDs */
#define PID_NULL 0
#define PID_P1   1
#define PID_P2   2
#define PID_P3   3
#define PID_P4   4
#define PID_P5   5
#define PID_P6   6
#define PID_A    7
#define PID_B    8
#define PID_C    9
#define PID_SET_PRIO     10
#define PID_CLOCK        11
#define PID_KCD          12
#define PID_CRT          13
#define PID_TIMER_IPROC  14
#define PID_UART_IPROC   15


/* Process Priority. The bigger the number is, the lower the priority is*/
#define HIGHEST 1
#define HIGH    2
#define MEDIUM  3
#define LOW     4
#define LOWEST  5
#define NUM_PRIORITIES 5

/* Message Types */
#define DEFAULT 0
#define KCD_REG 1
#define CRT_DISPLAY 2
#define COUNT_REPORT 3
#define wakeup10 4

/* ----- Types ----- */
typedef unsigned char U8;
typedef unsigned int U32;

/* common data structures in both kernel and user spaces */

/* initialization table item */
typedef struct proc_init
{
	int m_pid;	        /* process id */
	int m_priority;         /* initial priority, not used in this example. */
	int m_stack_size;       /* size of stack in words */
	int is_i_process; 			/* flag for checking if i process */
	void (*mpf_start_pc) ();/* entry point of the process */
} PROC_INIT;

typedef struct reg_command {
	int sender_id;
	char cmd_str[COMMAND_SIZE];
} REG_CMD;

/* message buffer */
typedef struct MSGBUF
{
	int mtype;              /* user defined message type */
	 char mtext[(128 - 4*sizeof(int) - sizeof(struct msgbuf*) - sizeof(struct Envelope*))/sizeof(char)];          /* body of the message */
} msgbuf;

typedef struct Envelope{
    int sender_id;
    int destination_id;
    int delay;
    msgbuf* message;
    struct Envelope* next;
} Envelope;

typedef struct Element Element;
struct Element {
    Element* next;
    void* data;
} ;
typedef struct Queue Queue;

struct Queue {
        Element* first;
        Element* last;
};

#endif // COMMON_H_
