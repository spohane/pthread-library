// File:	my_pthread.c
// Author:	Yujie REN
// Date:	09/23/2017

// name: Joshua B. Kim
// username of iLab: jbk91
// iLab Server: kill.cs.rutgers.edu

#include "my_pthread_t.h"

trq *tail;
static trq *readyQueue;
static twq *waitQueue;

/* initializes the internal structure of the thread library
 * should be called before using any other thread functions 
 * from my_pthread_t.h
 */

void initThreadLibrary() {

	readyQueue = NULL;
	waitQueue = NULL;
}

/* inserts tcb into the ready queue */
void enqueueThread(my_pthread_t *thread) {

	trq *tmp = (trq *)malloc(sizeof(trq));
	tmp->thread_block = thread;
	tmp->next = NULL;
	if (readyQueue == NULL) {
		readyQueue = tmp;
	}

	readyQueue = (trq *)malloc(sizeof(trq));
	readyQueue->thread_block = thread;
	readyQueue->next = NULL;
			
}

/* removes specified tcb from the queue
 * i'm most likely going to have to fix 
 * this function since it doesn't really
 * perform in the context that we want it
 * to. */
  
my_pthread_t* dequeueThread() {

	my_pthread_t *tmp;
	tmp = head;
	if (tmp == NULL)
	{
		head = tail = NULL;
	}
	else 
	{
		head = head->next;
		free(tmp);
	}	
	
}

/* create a new thread */
int my_pthread_create(my_pthread_t * thread, pthread_attr_t * attr, void *(*function)(void*), void * arg) {
	if(getcontext(&thread->ucs)==-1){
	  fprintf(stderr,"error: couldn't get context");
	  exit(1);
	}
	
	//init thread
	thread->ucs.uc_link = 0;
	thread->ucs.uc_stack.ss_sp = malloc(THREAD_SIZE);
	thread->ucs.uc_stack.ss_size = THREAD_SIZE;
	thread->ucs.uc_stack.ss_flags = 0;
	if (thread->ucs.uc_stack.ss_sp == 0) 
	{
		fprintf(stderr, "error: malloc couldn't allocate the stack\n");
		exit(1);
	}
	else 
	{
	  makecontext(&thread->ucs, (void (*) (void))function, 1, arg);
	  
	  //add thread to queue
	  
	  enqueueThread(thread);
	  
	  //readyQueue=(trq *)malloc(sizeof(trq));
	  //readyQueue->thread_block=thread;
	  //readyQueue->next=NULL;
	  //if(readyQueue==NULL) 
	  //{
	    //readyQueue=readyQueue;
	    //head = tail = readyQueue;
	  //} 
	  //else
	  //{
	    //readyQueue->next=readyQueue;
	    /*while(myQueue->next!=NULL){
	      myQueue=myQueue->next;
	      }*/
	    //myQueue->next=queue;
	    
	    swapcontext(&thread->ucs,&readyQueue->next->thread_block->ucs);
	  //}
	}	
	return 0;
};
/* give CPU pocession to other user level threads voluntarily */
int my_pthread_yield(){
}

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

