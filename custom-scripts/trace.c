  #include <stdio.h>
  #include <pthread.h>
  #include <semaphore.h>
  
  #define THREADS		5
  
  void *task(void *arg){
  	int tid;
  
  	tid = (int)(long int)arg;
  
  	while(1){
  		putchar('a' + tid);
  	}
  }
  
  int main(void){
  	long int i;
  	pthread_t threads[THREADS];
  
  	for(i = 0; i < THREADS; i++)
  		pthread_create(&threads[i], NULL, task, (void *)i);
  
  	pthread_exit(NULL);
  
  	return 0;
  }