#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <unistd.h>
using namespace std;

#define NUM_THREADS 5

void *wait(void *t){
	long tid = (long)t;
	long i = (long)t;
	sleep(i+1);
	cout << "Sleeping in thread " << endl;
	cout << "Thread with id: " << tid << "... exiting " << endl;
	pthread_exit(NULL);
}

int main(){
	int rc;
	int i;
	pthread_t threads[NUM_THREADS];
	pthread_attr_t attr;
	void *status;
	//Initialize and set thread joinable
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	for(i=0; i<NUM_THREADS; i++){
		cout << "Main(): creating thread " << i << endl;
		rc = pthread_create(&threads[i], &attr, wait, (void*)i);
		if(rc){
			cout << "Error: Unable to create thread," << rc << endl;
			exit(-1);
		}
	}

	// free attribute and wait for the other threads
	pthread_attr_destroy(&attr);
	for(i=0; i<NUM_THREADS; i++){
		rc = pthread_join(threads[i], &status);
		if(rc){
			cout << "Error: Unable to create thread," << rc << endl;
			exit(-1);
		}
		cout << "Main: completed thread id :" << i;
		cout << "exit with status: " << status << endl;
	}

	cout << "Main: program exiting ...." << endl;
	pthread_exit(NULL);
}