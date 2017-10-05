// File:	my_pthread.c
// Author:	Yujie REN
// Date:	09/23/2017

// name: Joshua B. Kim
// username of iLab: jbk91
// iLab Server: kill.cs.rutgers.edu

#include "my_pthread_t.h"

/* create a new thread */
int my_pthread_create(my_pthread_t * thread, pthread_attr_t * attr, void *(*function)(void*), void * arg) {

	tcb * tstruct = (tcb *)malloc(sizeof(THREAD_SIZE));
	ucontext_t *child, parent;
	child = tstruct->ucs;	

	getcontext(child);

	child->uc_stack.ss_sp = malloc(THREAD_SIZE);
	child->uc_stack.ss_size = THREAD_SIZE;
	child->uc_stack.ss_flags = 0;
	if (child->uc_stack.ss_sp == 0) {
		fprintf(stderr, "error: malloc count not allocate the stack\n");
		exit(1);
	}

	makecontext(child, function, arg);
	swapcontext(child, &parent);

	return 0;
};

/* terminate a thread */
void my_pthread_exit(void *value_ptr) {
};

/* wait for thread termination */
int my_pthread_join(my_pthread_t thread, void **value_ptr) {
	return 0;
};

/* initial the mutex lock */
int my_pthread_mutex_init(my_pthread_mutex_t *mutex, const pthread_mutexattr_t *mutexattr) {
	return 0;
};

/* aquire the mutex lock */
int my_pthread_mutex_lock(my_pthread_mutex_t *mutex) {
	return 0;
};

/* release the mutex lock */
int my_pthread_mutex_unlock(my_pthread_mutex_t *mutex) {
	return 0;
};

/* destroy the mutex */
int my_pthread_mutex_destroy(my_pthread_mutex_t *mutex) {
	return 0;
};

