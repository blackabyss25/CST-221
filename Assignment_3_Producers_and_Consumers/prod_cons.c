/*
    Author of edits after starter: Kurt Newcomb 
    
    Approach:
    Tried to make it work... also, added a random number value generator 
    just because it was easy enough to do and made things a little spicier
    
*/


#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/mman.h>
#include <errno.h>
#include <pthread.h>

// Constants
int MAX = 100;
int WAKEUP = SIGUSR1;
int SLEEP = SIGUSR2;

void sigHandler(int signal){}

// The Child PID if the Parent else the Parent PID if the Child
pid_t otherPid;

// A Signal Set
sigset_t sigSet;

// Shared Circular Buffer
struct CIRCULAR_BUFFER
{
    int count;          // Number of items in the buffer
    int lower;          // Next slot to read in the buffer
    int upper;          // Next slot to write in the buffer
    int buffer[100];
};
struct CIRCULAR_BUFFER *buffer = NULL;

/****************************************************************************************************/

// This method will put the current Process to sleep forever until it is awoken by the WAKEUP signal
void sleepAndWait()
{
    int nSig;

    printf("Sleeping...........\n");
    // TODO: Sleep until notified to wake up using the sigwait() method
    sigwait(&sigSet, &nSig);
    printf("Awoken\n");
}

// This method will signal the Other Process to WAKEUP
void wakeupOther()
{
	// TODO: Signal Other Process to wakeup using the kill() method
    kill(otherPid, WAKEUP);
}

// Gets a value from the shared buffer
// Gets a value from the shared buffer
void getValue()
{
    printf("getValue:Buffer Count = %i\n", buffer->count);
    //
    // TODO: Get a value from the Circular Buffer and adjust where to read from next
    //
    if (buffer->count > 0)
    {
        printf("Consumer: value = %i\n", buffer->buffer[buffer->lower]);
        buffer->lower++;
        if (buffer->lower >= MAX)
            buffer->lower = 0;
        buffer->count--;
    }
}

// Puts a value in the shared buffer
void putValue(struct CIRCULAR_BUFFER* buffer, int value)
{
    //
    // TODO: Write to the next available position in the Circular Buffer and adjust where to write next
    //
    if (buffer->count < MAX)
    {
        buffer->buffer[buffer->upper] = value;
        buffer->upper++;
        if (buffer->upper >= MAX)
            buffer->upper = 0;
        buffer->count++;
    }
    //printf("putValue:Buffer Count = %i, value = %i\n", buffer->count, value);
}

/****************************************************************************************************/

/**
 * Logic to run to the Consumer Process
 **/
void consumer()
{
    sigemptyset(&sigSet);
    sigaddset(&sigSet, WAKEUP);

    // Run the Consumer Logic
    printf("Running Consumer Process.....\n");
    
    // TODO: Implement Consumer Logic (see page 129 in book)
    while(1){
        if(buffer->count == 0){
            sleepAndWait();
        }
        getValue();
        if(buffer->count == MAX-1){
            wakeupOther();
        }
    }
    // Exit cleanly from the Consumer Process
    _exit(1);
}

/**
 * Logic to run to the Producer Process
 **/
void producer()
{
    // Buffer value to write
    int value = 0;

    // Set Signal Set to watch for WAKEUP signal
    sigemptyset(&sigSet);
    sigaddset(&sigSet, WAKEUP);

    // Run the Producer Logic
    printf("Running Producer Process.....\n");
    
    // TODO: Implement Producer Logic (see page 129 in book)
    while(1){ //repeat forever
        //Generate value to insert
        int randomnumber;
        randomnumber = rand() % 10;
        int value = randomnumber;
        //If buffer is full, sleep
        if(buffer->count == MAX){
            sleepAndWait();
        }
        putValue(buffer, value);
        if(buffer->count == 1){
            wakeupOther();
        }

    }
    // Exit cleanly from the Consumer Process
    _exit(1);
}

/**
 * Main application entry point to demonstrate forking off a child process that will run concurrently with this process.
 *
 * @return 1 if error or 0 if OK returned to code the caller.
 */
int main(int argc, char* argv[])
{
    pid_t  pid;

    // Create shared memory for the Circular Buffer to be shared between the Parent and Child  Processes
    buffer = (struct CIRCULAR_BUFFER*)mmap(0,sizeof(buffer), PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS, -1, 0);
    buffer->count = 0;
    buffer->lower = 0;
    buffer->upper = 0;


    signal(WAKEUP, &sigHandler);

    // Use fork()
    pid = fork();
    if (pid == -1)
    {
        // Error: If fork() returns -1 then an error happened (for example, number of processes reached the limit).
        printf("Can't fork, error %d\n", errno);
        exit(EXIT_FAILURE);
    }
    // OK: If fork() returns non zero then the parent process is running else child process is running
    if (pid == 0)
    {
        // Run Producer Process logic as a Child Process
        otherPid = getppid();
        printf("Consumer = %i\n", otherPid);
        producer();
    }
    else
    {
        // Run Consumer Process logic as a Parent Process
        otherPid = pid;
        printf("Producer = %i\n", otherPid);
        consumer();
    }

    // Return OK
    return 0;
}