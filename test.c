#include "my_pthread_t.h"



void* fn() {

  printf("Hello, world! We are in fn().\n");

}

<<<<<<< HEAD

int main(int argc, char ** argv) {

  my_pthread_t tid;
  printf("hello\n");
  tid = my_pthread_create(&tid, NULL, fn, NULL);
=======
int main(int argc, char ** argv)
{
  int testSize=10;
  my_pthread_t thread[testSize];
  for(int i=0;i<testSize;i++){
    my_pthread_create(&thread[i], NULL, f1, NULL); 
  }
  return 0;
>>>>>>> 7dcfd0a1bdea0f39fe04e1a861a5daa24a1dd78b

  return 0;
}
