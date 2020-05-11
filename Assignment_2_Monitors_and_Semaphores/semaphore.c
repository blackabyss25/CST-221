/*
Assignment: Monitors and Semaphores - semaphore.c
Author: Kurt Newcomb
Date: 5/10/2020

Purpose: This is the semaphore half of the assignment.

*/


#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<sys/types.h>
#include<sys/stat.h>

sem_t sem_id;
int tickets = 20;
int sellers = 4;

void * TicketSeller()
{
	while(1)
	{
		int ret;
		ret = sem_wait(&sem_id);
		if(ret != 0)
			perror("semaphore waiting");
		if(tickets > 0)
		{
			tickets--;
			printf("Seller %lu sold a ticket, %d tickets left.\n", pthread_self(), tickets);
		}
		else 
		{	
			ret = sem_post(&sem_id);
			if(ret != 0)
				perror("semaphore waiting");
			break;
		}	
		ret = sem_post(&sem_id);
		if(ret != 0)
			perror("semaphore waiting");
	}
	pthread_exit(NULL);
}

int main()
{
	int ret;
	pthread_t thread_id[sellers];

// Semaphore initilization
	ret = sem_init(&sem_id, 1 ,1);
	if(ret != 0)
		perror("semaphore initialization");

// Create TicketSeller threads
    for(int i = 0; i < sellers; i++){
        ret = pthread_create(&thread_id[i], NULL, TicketSeller, NULL);
	    if(ret != 0){
            perror("creation of ticket seller thread");
        }
    }    
// Join threads	
	for(int j = 0; j < sellers; j++)
	{
		pthread_join(thread_id[j], NULL);
	}
}