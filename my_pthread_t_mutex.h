// File:	my_pthread_t.h
// Author:	Yujie REN
// Date:	09/23/2017

// name: Shruti Pohane
// username of iLab: sp1106
// iLab Server: kill.cs.rutgers.edu
#ifndef MY_PTHREAD_T_H
#define MY_PTHREAD_T_H

#define _GNU_SOURCE

/* include lib header files that you need here: */
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint my_pthread_t;

typedef struct threadControlBlock {
	/* add something here */
} tcb; 

/* mutex struct definition */
typedef struct my_pthread_mutex_t {
	int mutex_id;
  	int locked; //locked=1 & unlocked 0
  	int init_flag;
  	struct my_pthread_mutex_t_struc *next;
} my_pthread_mutex_t;

/* define your data structures here: */
typedef struct mutex_list_struct {
  	struct my_pthread_mutex_t_struc *head;
}mutex_list;

static mutex_list *mutex_list = NULL;
static int currmutex_id = 0;

// Feel free to add your own auxiliary data structures


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
