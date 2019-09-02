#include <iostream>
#include <pthread.h> 
#include <unistd.h>
#include <ctime>
using namespace std;


class Timer
{
	typedef int (*MyFunc)(int);
	
	struct TimerArguments {
	    bool isStopped;
	    MyFunc myFunc;
	    int interval;
	    int times;
	    string timeStarted;
	};
	 
	pthread_t m_pthread;
	TimerArguments* m_timerArguments;
	
	public:
	Timer(int (*func)(int), int interval, int times)
	{
		m_timerArguments = (TimerArguments*)malloc(sizeof(struct TimerArguments));
		m_timerArguments->myFunc = func;
		m_timerArguments->interval = interval;
		m_timerArguments->times = times;
	}
	~Timer()
	{
		free(m_timerArguments);
	}
	
	static void* print(void* args)
	{
		TimerArguments* timerArgs = (TimerArguments*)args;
		printf("interval: %d\n", timerArgs->interval);
		printf("times: %d\n", timerArgs->times);
		printf("isStopped: %d\n", timerArgs->isStopped);
		printf("timeStarted: %s\n", timerArgs->timeStarted.c_str());
		
		int counter = 0;
		int x = counter;
		for(;;)
		{
			if(counter != timerArgs->times)
			{
				printf("Counter: %d\n", counter++);
                usleep(10000*timerArgs->interval);
                x = timerArgs->myFunc(x);
			}
			else
			{
				pthread_exit(0);
			}
		}
    	pthread_exit(0);
	}
	
	void start()
	{
		time_t now = time(0);
		
		m_timerArguments->timeStarted = ctime(&now);
		m_timerArguments->isStopped = false;
		
		if(pthread_create(&m_pthread, NULL, print, (void*)(m_timerArguments)))
		{
			throw "Insuffcient Memory";
		}
	}
	
	void wait()
	{
		pthread_join(m_pthread, NULL);
	}
};

int myFunc(int x)
{
	printf("x is %d\n", x);
	return x+1;	
}

int main() {
	
	int interval = 10; //10s
	int times = 4; //stop after 4 times
	
	Timer timer(myFunc, interval, times);
	timer.start();
	timer.wait(); //Wait for timer to complete 
	
	return 0;
}
