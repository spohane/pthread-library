#include "my_pthread_t.h"

void *f1(void *arg) {

	printf("Hello, World!\n");
}

int main(int argc, char ** argv)
{

  my_pthread_t thread;
  my_pthread_create(&thread, NULL, f1, NULL); 

  return 0;

}
