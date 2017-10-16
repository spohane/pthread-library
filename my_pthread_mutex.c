// File:	my_pthread.c
// Author:	Yujie REN
// Date:	09/23/2017

// name: Shruti Pohane
// username of iLab: sp1106
// iLab Server: kill.cs.rutgers.edu

#include "my_pthread_t.h"

/* create a new thread */
int my_pthread_create(my_pthread_t * thread, pthread_attr_t * attr, void *(*function)(void*), void * arg) {
	return 0;
};

/* give CPU pocession to other user level threads voluntarily */
int my_pthread_yield() {
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
	initMutexList();
	my_pthread_mutex_t *newm = (my_pthread_mutex_t*)malloc(sizeof(my_pthread_mutex_t));
	newm = mutex;
	newm->mutex_id = ++currmutex_id;
	newm->init_flag = 1;
	newm->next = NULL;
	newm->locked = 0;
	newm->next = mutexList->head;
	mutexList->head = newm;

	return 0;
};
int check_mut_list(int vmutex) {
  	my_pthread_mutex_t *p = mutexList->head;
  	while (p != NULL) {
    	if (p->mutex_id == vmutex) {
      	return 1;
    }
    p = p->next;
  }
  return 0;
}
/* aquire the mutex lock */
int my_pthread_mutex_lock(my_pthread_mutex_t *mutex) {
	if(mutex->init_flag != 1 && check_mut_list(mutex->mutex_id)){
    	return -1;
	}
    while(__sync_lock_test_and_set(&(mutex->locked), 1));
    mutex->isLocked = 1;
	return 0;
};

/* release the mutex lock */
int my_pthread_mutex_unlock(my_pthread_mutex_t *mutex) {
	__sync_lock_release(&(mutex->locked), 1);
    mutex->locked = 0;
    return 0;
};

/* destroy the mutex */
int my_pthread_mutex_destroy(my_pthread_mutex_t *mutex) {
	my_pthread_mutex_t *mutexlist = removeFromMutexList(mutex->mutex_id);
      if(mutexlist == NULL){
        return -1;
      }
      mutexlist->locked = 0;
      mutexlist->next = NULL;
      mutexlist->mutex_id = -1;
      mutexlist->init_flag = 0;
      mutexlist = NULL;
      mutex = NULL;
      return 0;
    }

void initMutexList(){
    if(mutexList != NULL){
    	return;
    }
};
