#include "my_pthread_t.h"

void *f1(void *arg) {

	printf("Hello, World!\n");
}
void *f2(void *arg) {

	printf("hey!\n");
}

int main(int argc, char ** argv)
{
  initThreadLibrary();
  int argg=1;

  my_pthread_t thread,thread2;
  trq test;
  my_pthread_create(&thread,NULL, f2, NULL);
  f1((void*)&argg);
  f2((void*)&argg);
  test.thread_block=&thread;
  my_pthread_create(&thread2, NULL, f1, NULL);
  trq temp;
  temp.thread_block=&thread2;
  test.next=&temp;

  f1((void*)&argg);
  f2((void*)&argg);
  return 0;
}
