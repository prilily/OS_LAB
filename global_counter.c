#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//compile via -lpthread
int count=0;
pthread_mutex_t mutex;
void *routine()
{
  for(int i=0;i<1000;i++)
  {
    pthread_mutex_lock(&mutex);
      count++;
    pthread_mutex_unlock(&mutex);
  }
}


int main()
{
  int n=10;
  pthread_t lp[n];
  pthread_mutex_init(&mutex,NULL);
  for(int i=0;i<n;i++)
  {
    if(pthread_create(lp+i,NULL,routine,NULL)!=0)
    {
      printf("error in creating thread");
      return 1;
    }
        printf("thread %d has started \n",i);
  }
  for(int i=0;i<n;i++)
  {
    if(pthread_join(lp[i],NULL)!=0)
    {
      printf("error in joining thread");
      return 2;
    }
        printf("thread %d has finished \n",i);
  }
  pthread_mutex_destroy(&mutex);
  printf(" last value of global variable : %d",count);
  return 0;
}
