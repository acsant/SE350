/**
 * @file:   k_process.h
 * @brief:  process management hearder file
 * @author: Yiqing Huang
 * @author: Thomas Reidemeister
 * @date:   2014/01/17
 * NOTE: Assuming there are only two user processes in the system
 */

#ifndef K_PROCESS_H_
#define K_PROCESS_H_

#include "k_rtx.h"
#include "k_timer.h"
#include "k_memory.h"
#include "common.h"
#include "sysproc.h"
#include "uart.h"

/* ----- Definitions ----- */

#define INITIAL_xPSR 0x01000000        /* user process initial xPSR value */

/* ----- Functions ----- */

void process_init(void);               /* initialize all procs in the system */
PCB *scheduler(void);                  /* pick the pid of the next to run process */
int k_release_process(void);           /* kernel release_process function */
PCB* getProcessByID(int);
void mail_benqueue(PCB*);
PCB* remove_from_mail_blocked(int);
void timer_enqueue(Envelope*);
Envelope* timer_dequeue(void);
void printTimeOutQueue(void);
void printTimerBlockedQueue(void);
void null_process(void);


extern U32 *alloc_stack(U32 size_b);   /* allocate stack for a process */
extern void __rte(void);               /* pop exception stack frame */
extern void set_test_procs(void);      /* test process initial set up */

#endif /* ! K_PROCESS_H_ */
