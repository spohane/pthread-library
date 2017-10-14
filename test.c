#include "my_pthread_t.h"

void *f1(void *arg) {

	printf("Hello, World!\n");
}

int main(int argc, char ** argv)
{
  int testSize=10;
  my_pthread_t thread[testSize];
  for(int i=0;i<testSize;i++){
    my_pthread_create(&thread[i], NULL, f1, NULL); 
  }
  return 0;

}
