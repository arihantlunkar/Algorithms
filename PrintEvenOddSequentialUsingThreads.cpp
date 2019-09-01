#include <iostream>
#include <pthread.h> 
using namespace std;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int i = 0;

void* printEven(void *args)
{
    while(1)
    {
        pthread_mutex_lock(&mutex);
        if(i % 2 == 0)
        {
        	pthread_cond_wait(&cond, &mutex);
        }
        
        ++i;        
        printf("%d\n",i);
        pthread_cond_signal(&cond);
        
        if(i>=10)
        {
        	pthread_mutex_unlock(&mutex);
        	pthread_exit(NULL);
        }
        pthread_mutex_unlock(&mutex);
    }
}

void* printOdd(void *args)
{
    for(;;)
    {
        pthread_mutex_lock(&mutex);
        if(i % 2 != 0)
        {
        	pthread_cond_wait(&cond, &mutex);
        }
        
        ++i;        
        printf("%d\n",i);
        pthread_cond_signal(&cond);
        
        if(i>=10)
        {
        	pthread_mutex_unlock(&mutex);
        	pthread_exit(NULL);
        }
        pthread_mutex_unlock(&mutex);
    }
}



int main() {
	pthread_t t1,t2;
	pthread_create(&t1, NULL, printEven, NULL);
	pthread_create(&t2, NULL, printOdd, NULL);
	
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	return 0;
}
