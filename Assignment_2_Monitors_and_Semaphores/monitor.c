/*
Assignment: Monitors and Semaphores - monitor.c
Author: Kurt Newcomb
Date: 5/10/2020

Purpose: This is the monitor half of the assignment.

*/


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#define MAX 10
pthread_mutex_t m;
pthread_cond_t condCustomer, condSeller;
int buffer = 0;

void * Seller(void * ptr){
     for(int i = 0; i <= MAX; i++){
        pthread_mutex_lock(&m); 
        while(buffer != 0){
            pthread_cond_wait(&condSeller, &m);
        }
        buffer = i;
        pthread_cond_signal(&condCustomer);
        pthread_mutex_unlock(&m);
	printf("Ticket Number: %i is next for sale.\n", i);
     }
     pthread_exit(0);
}
void * Customer(void * ptr){
     for(int i=1; i<=MAX; i++){
        pthread_mutex_lock(&m);
        while(buffer == 0){
            pthread_cond_wait(&condCustomer,&m);
        }
	printf("Ticket Number: %i was purhcased by a customer.\n", buffer);
        buffer = 0;
        pthread_cond_signal(&condSeller);
        pthread_mutex_unlock(&m);

     }
     pthread_exit(0);
} 

int main (int argc, char **argv){
     pthread_t seller, customer;
     pthread_mutex_init(&m, 0);
     pthread_cond_init(&condCustomer,0);
     pthread_cond_init(&condSeller,0);
     pthread_create(&customer, 0, Customer, 0);
     pthread_create(&seller, 0, Seller, 0);
     pthread_join(seller, 0);
     pthread_join(customer, 0);
     pthread_cond_destroy(&condCustomer);
     pthread_cond_destroy(&condSeller);
     pthread_mutex_destroy(&m);
}