/*
CST-221 Deadlock Avoidance
Author: Kurt Newcomb
5/17/2020
*/
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

// Create mutex object.
pthread_mutex_t resourceLock;

//Set time delay for process
int interval = 10;

//Set number of "tasks" per thread to complete
int tasksToComplete = 5;

void *process (void *threadName) {
	//Set Thread Identifier
	char *message;
	message = (char *) threadName;

	//Process is to attempt to acquire resource 
	if (pthread_mutex_lock(&resourceLock) == 0) {
		printf("%s has the resource locked\n", message);
		for (int i = 1; i < tasksToComplete + 1; i++) {
			printf("%s is at %d 'task completed'\n", message, i);
			pthread_mutex_unlock(&resourceLock);
			printf("%s has unlocked the resource.\n", message);
			sleep(interval);
			printf("%s has slept for %d.\n", message, interval);
		}
		printf("%s has FINIHSED!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!.\n", message);
	} 
	//if resource is unavailable, wait for a certain period of time for said resource before trying again
	else {
		printf("%s attempted to lock the resource but failed.\n", message);
	}
	return NULL;
}

int main(int argc, char *argv[]){
	// Define threads and variables.
	pthread_t tHandle1;
	pthread_t tHandle2;
	pthread_t tHandle3;
	pthread_t tHandle4;
	pthread_t tHandle5;
	char *firstThreadName = "First Thread";
	char *secondThreadName = "Second Thread";
	char *thirdThreadName = "Third Thread";
	char *fourthThreadName = "Fourth Thread";
	char *fifthThreadName = "Fifth Thread";
	int return1;
	int return2;
	int return3;
	int return4;
	int return5;

	printf("Before pthread_creates have been called:\n");

	// Create the four threads and run a process function.
	return1 = pthread_create(&tHandle1, NULL, process, (void *) firstThreadName);
	printf("%s is created.\n", firstThreadName);
	return2 = pthread_create(&tHandle2, NULL, process, (void *) secondThreadName);
	printf("%s is created.\n", secondThreadName);
	return3 = pthread_create(&tHandle3, NULL, process, (void *) thirdThreadName);
	printf("%s is created.\n", thirdThreadName);
	return4 = pthread_create(&tHandle4, NULL, process, (void *) fourthThreadName);
	printf("%s is created.\n", fourthThreadName);
	return5 = pthread_create(&tHandle5, NULL, process, (void *) fifthThreadName);
	printf("%s is created.\n", fifthThreadName);

	// Thread Cleanup
	pthread_join(tHandle1, NULL);
	pthread_join(tHandle2, NULL);
	pthread_join(tHandle3, NULL);
	pthread_join(tHandle4, NULL);
	pthread_join(tHandle5, NULL);
	printf("First thread returns = %d\n", return1);
	printf("Second thread returns = %d\n", return2);
	printf("Third thread returns = %d\n", return3);
	printf("Fourth thread returns = %d\n", return4);
	printf("Fourth thread returns = %d\n", return5);

	return 0;
}