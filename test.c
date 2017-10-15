#include "my_pthread_t.h"



void* fn() {

  printf("Hello, world! We are in fn().\n");

}


int main(int argc, char ** argv) {

  my_pthread_t tid;
  printf("hello\n");
  tid = my_pthread_create(&tid, NULL, fn, NULL);

  return 0;
}
