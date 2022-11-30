#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#define NUM_THREADS 10

long tpoint;
long npoint;
pthread_mutex_t count_mutex;
void* nPoint(void* pthreadid){
	long point=0;
	float d;
	for(long i=(long)pthreadid; i<tpoint; i+=NUM_THREADS) {
		float x = 1.0*(rand()%1001)/1000;
                float y = 1.0*(rand()%1001)/1000;
		d = x*x + y*y;
		
		pthread_mutex_lock(&count_mutex);
		if(d <= 1){//critical
			npoint++;
		}
		pthread_mutex_unlock(&count_mutex);
	}
}

int main(int argc, char* argv[]){
	if(argc != 2) return 0;
	else{
		clock_t tic = clock();
		pthread_mutex_init(&count_mutex, NULL);
		tpoint = atoi(argv[1]);
		pthread_t threads[NUM_THREADS];
		for(long t=0; t<NUM_THREADS; t++){
			pthread_create(&threads[t], NULL, nPoint, (void*)t);
		}
		for(int i=0; i<NUM_THREADS; i++){
			pthread_join(threads[i], NULL);
		}
		float pi = 0;
		pi = 4.0*npoint/tpoint;
		printf("Pi = %.3f", pi);
		clock_t toc = clock();
		printf("\n Semaphore run time: %f seconds\n", (double)(toc - tic) / CLOCKS_PER_SEC);
	}
}

