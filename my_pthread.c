// File:	my_pthread.c
// Author:	Yujie REN
// Date:	09/23/2017

// name: Joshua B. Kim
// username of iLab: jbk91
// iLab Server: kill.cs.rutgers.edu

#include "my_pthread_t.h"

static tq *readyQueue;
static tq *waitQueue;
ucontext_t Main;
tcb *cur_thread;
/* function for the scheduler, which is called in initThreadLibrary() */

int scheduler(void) {




  return 0;
}

/* initializes the internal structure of the thread library
 * should be called before using any other thread functions 
 * from my_pthread_t.h
 */

void initThreadLibrary() {

	readyQueue = (tq *)malloc(sizeof(tq));
	waitQueue = (tq *)malloc(sizeof(tq));
	readyQueue->head = readyQueue->tail = 
	waitQueue->head = waitQueue->tail = NULL;
	waitQueue->numOfThreads = readyQueue->numOfThreads = 0;
	scheduler();

}

/* inserts tcb into the queue */
void enqueueThread(tq *queue, tcb *block) {

	tqn *tmp = (tqn *)malloc(sizeof(tqn));
	tmp->thread_block = block;
	tmp->link = NULL;

	if (queue->numOfThreads == 0) {
		queue->head = queue->tail = tmp;
		queue->numOfThreads++;
		return;
	} else {
		queue->tail->link = tmp;
		queue->tail = tmp;
		queue->numOfThreads++;
		return;
	}

}

/* removes the first tcb block from the queue 
 * returns the first tcb block, or NULL if the
 * queue is empty
 */

tqn* dequeueThread(tq *queue) {

	if (queue->numOfThreads == 0) {
		return NULL;
	} else if (queue->numOfThreads == 1) {
		tqn *tmp = queue->head;
		queue->head = queue->tail = NULL;
		queue->numOfThreads--;
		return tmp;
	} else {
		tqn *tmp = queue->head;
		queue->head = queue->head->link;
		queue->numOfThreads--;
		return tmp;
	}
	
}
/* create a new thread */
int my_pthread_create(my_pthread_t * thread, pthread_attr_t * attr, void *(*function)(void*), void * arg) {

	tcb * thread_block = (tcb *)malloc(sizeof(THREAD_SIZE));
	getcontext(&thread_block->ucs);
	//---change this to my_pthread_exit() i think?
	thread_block->ucs.uc_link = &Main;
	thread_block->ucs.uc_stack.ss_sp = malloc(THREAD_SIZE);
	thread_block->ucs.uc_stack.ss_size = THREAD_SIZE;
	thread_block->ucs.uc_stack.ss_flags = 0;
	//added tid
	thread_block->tid=*thread;
	if (thread_block->ucs.uc_stack.ss_sp == 0) 
	{
		fprintf(stderr, "error: malloc could not allocate the stack\n");
		exit(1);
	}
	else 
	{
		makecontext(&thread_block->ucs, (void *) function, 0);
		//need to add to queue here
		
		//---change this later when we have scheduler done
		//if(cur_thread==NULL)
		cur_thread=thread_block;
	}
	//dont need this--testing only
	my_pthread_yield();
	return 0;
};

/* give CPU pocession to other user level threads voluntarily */
int my_pthread_yield(){
  //this should be cur and next scheduled thread---change later
  swapcontext(&Main, &cur_thread->ucs);
}

/* terminate a thread */
 //called from self
void my_pthread_exit(void *value_ptr) {
  //make sure this thread doesn't run anymore/send to back of queue and leave it there
  //cur_thread->status=DONE;
  my_pthread_yield();
};

/* wait for thread termination */
//called from another thread
int my_pthread_join(my_pthread_t thread, void **value_ptr) {
//wait until thread is exited
  //cur_thread->status=WAIT until thread->status==DONE
  //if done, free(thread) and its resources
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

