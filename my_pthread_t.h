// File:	my_pthread_t.h
// Author:	Yujie REN
// Date:	09/23/2017

// name: Joshua B. Kim
// username of iLab: jbk91
// iLab Server: kill.cs.rutgers.edu
#ifndef MY_PTHREAD_T_H
#define MY_PTHREAD_T_H

#define _GNU_SOURCE
#define THREAD_SIZE 65536

/* include lib header files that you need here: */
#include <unistd.h>
#include <ucontext.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/time.h>
#include <stdio.h>
#include <setjmp.h>
#include <stdlib.h>
#include <signal.h>

//ucontext_t Main; 

typedef uint my_pthread_t;

typedef enum State {
	RUN, READY, WAIT, START, DONE
} state;

typedef struct threadControlBlock {
	
	my_pthread_t tid;
	state status;
	struct itimerval *it;
	struct sigaction *act, *oact;
	ucontext_t ucs;
} tcb; 

/* mutex struct definition */
typedef struct my_pthread_mutex_t {
	/* add something here */
} my_pthread_mutex_t;

/* define your data structures here: */

typedef struct threadQueueNode {

	tcb * thread_block;
	struct threadQueueNode *link;
} tqn;

typedef struct threadQueue {
		
	unsigned int numOfThreads;
	struct threadQueueNode *head, *tail; 
} tq;

/* Custom Function Declarations: */

/* initializes the internal structures of the library */
void initThreadLibrary();

/* scheduler */
int scheduler();

/* signal handler for 25ms quanta */
void timeHandler();

/* inserts tcb into the ready queue */
void enqueueThread(tq *queue, tcb *block);

/* removes first tcb in ready queue 
 * returns a tqn if successful,
 * else returns NULL 
 */
tqn* dequeueThread(tq *queue);

/* Function Declarations: */

/* create a new thread */
int my_pthread_create(my_pthread_t * thread, pthread_attr_t * attr, void *(*function)(void*), void * arg);

/* give CPU pocession to other user level threads voluntarily */
int my_pthread_yield();

/* terminate a thread */
void my_pthread_exit(void *value_ptr);

/* wait for thread termination */
int my_pthread_join(my_pthread_t thread, void **value_ptr);

/* initial the mutex lock */
int my_pthread_mutex_init(my_pthread_mutex_t *mutex, const pthread_mutexattr_t *mutexattr);

/* aquire the mutex lock */
int my_pthread_mutex_lock(my_pthread_mutex_t *mutex);

/* release the mutex lock */
int my_pthread_mutex_unlock(my_pthread_mutex_t *mutex);

/* destroy the mutex */
int my_pthread_mutex_destroy(my_pthread_mutex_t *mutex);

#endif
