// Example program
#include <iostream>
#include <vector>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex; 
pthread_cond_t* cond;
std::vector<int> vec;
volatile int i = 0;

#define PRODUCER_COUNT 15

void* push(void* args)
{
    pthread_mutex_lock(&mutex);
    int ctr = *(int*)args;
    printf("Creating thread %d, but i is %d\n",ctr, i);
    if(i != ctr)
    {
    	printf("Waiting %d\n",ctr);
        pthread_cond_wait(&cond[ctr], &mutex);
    }
    printf("Wait complete %d\n",ctr);
    vec.push_back(ctr);
    ++i;
    if(i < PRODUCER_COUNT)
    {
    	printf("Signaling %d\n",i);
    	pthread_cond_signal(&cond[i]);
    }
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

int main()
{
    pthread_t threadPush[PRODUCER_COUNT];    
    (void)pthread_mutex_init(&mutex, NULL);
    int* arr = (int*)malloc(sizeof(int)*PRODUCER_COUNT);
	cond = (pthread_cond_t*)malloc(sizeof(pthread_cond_t)*PRODUCER_COUNT);
    for(int i=0;i<PRODUCER_COUNT;++i)
    {  
        *(arr+i) = i;
        printf("Passing args %d, address %p\n",arr[i], &arr[i]);        
        (void)pthread_create(&threadPush[i], NULL, &push, (void*)&arr[i]);  
    }
    
    printf("Wating for all threads to complete\n");
    for(int i=0;i<PRODUCER_COUNT;++i)
        pthread_join(threadPush[i], NULL); 
        
    printf("Printing vector\n");
    for(auto b=vec.begin();b!=vec.end();++b)
        printf("%d ",*b);
        
    pthread_mutex_destroy(&mutex);
}
