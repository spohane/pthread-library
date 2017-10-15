// File:	my_pthread.c
// Author:	Yujie REN
// Date:	09/23/2017

// name: Joshua B. Kim
// username of iLab: jbk91
// iLab Server: kill.cs.rutgers.edu

#include "my_pthread_t.h"

static tq *runQueue;
static tq *waitQueue;


/* scheduler signal,function */
int scheduler() {
 
  // thinking processe behind this was if the number of threads in
  // the runQueue is not 0, there are threads that need to start running.

  if (runQueue->numOfThreads != 0) {
	// so we dequeue the first thread from the runQueue
	// and then set the necessary signal actions when the
	// timer expires (set previously in the my_pthread_create() function)
	// BUT, this is where I am confused... I don't know in which order we are supposed
	// to set these timer attributes/values, because I don't know when the timer would start
	// running.
	//
	// Also, I know swapcontext, brings it back to the previous context, but how can we go back 
	// to main when we don't have a reference to it. Maybe, I interpretted the readings incorrectly

	tqn *run = dequeueThread(runQueue);
  	sigaction(SIGPROF, run->thread_block->act, run->thread_block->oact);
	setitimer(ITIMER_PROF, run->thread_block->it, NULL);
	setcontext(run->thread_block->ucs);	
  } 

  return 0;

}

void timeHandler() {
	printf("we are in the time handler\n");
}

/* initializes the internal structure of the thread library
 * should be called before using any other thread functions 
 * from my_pthread_t.h
 */

void initThreadLibrary() {

	runQueue = (tq *)malloc(sizeof(tq));
	waitQueue = (tq *)malloc(sizeof(tq));
	runQueue->head = runQueue->tail = 
	waitQueue->head = waitQueue->tail = NULL;
	waitQueue->numOfThreads = runQueue->numOfThreads = 0;

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

tqn * dequeueThread(tq *queue) {

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

	tcb *thread_block = (tcb *)malloc(sizeof(THREAD_SIZE));
	getcontext(thread_block->ucs);
	thread_block->ucs->uc_link = 0;
	thread_block->ucs->uc_stack.ss_sp = malloc(THREAD_SIZE);
	thread_block->ucs->uc_stack.ss_size = THREAD_SIZE;
	thread_block->ucs->uc_stack.ss_flags = 0;
	if (thread_block->ucs->uc_stack.ss_sp == 0) 
	{
		fprintf(stderr, "error: malloc could not allocate the stack\n");
		return -1;
	}
	else 
	{	

		// makes the context via ucontext_t pointer in tcb struct
		makecontext(thread_block->ucs, (void (*) (void))function, 0);
			
		// so below I tried just set the attributes of the thread
		// but I wasn't sure where to put handlers for time (25 ms quanta)
		// whether these interval and value attributes should be set in this
		// function or by the handler.
		//
		// Essentially, I'm not sure when the timer starts, does it start when these 
		// attributes are initialized or when the actual thread runs(?)
		thread_block->status = READY;
		thread_block->act->sa_handler = timeHandler;
		sigemptyset(&thread_block->act->sa_mask);
		thread_block->it->it_interval.tv_usec = 25000; // set the interval to 25000 us == 25ms
		thread_block->it->it_value.tv_usec = 25000; // set the value to 25000 us (not sure if I am doing this correctly).
		enqueueThread(runQueue, thread_block); // add the thread_block into the runQueue
		
		// calls scheduler to now do determine which thread will run and have priority
		// if it returns -1, something wrong happened and my_pthread_create will return -1
		// look at the scheduler() function up top to debug...
		if (scheduler() == -1) {
			fprintf(stderr, "error: error in scheduler, could not start thread\n");
			return -1;
		}
		//swapcontext(thread_block->ucs, &Main);
	}	


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

