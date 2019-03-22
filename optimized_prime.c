#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N_THREAD 5
#define N_PRIME 50000

//Create the array that contain the state of the prime
int primeNum[N_PRIME] = {0};

//Funciton for finding the prime number
void* compute_prime(void* arg){
    //We consider 0 and 1 as non prime number
    primeNum[0] = 1;
    primeNum[1] = 1;
    
    //Set the end point for prime computation
    int end = *((int*)arg) + 1;
    
    /*
     Loop for manipulating the status of the primeNum array
     If the number is prime then it stays 0
     But is is non prime, then it become status = 1
     NOTE: This algorithm is implement from Sieve of Eratosthenes prime computation
    */
    for(int factor = 2; factor*factor <= end; factor++){
        if(primeNum[factor]==0){
            for(int notPrime = factor*2; notPrime <= end; notPrime += factor) {
                primeNum[notPrime] = 1;
            }
        }
    }
    return NULL;
}

int main(){
    //Create an array of threads
    pthread_t thread[N_THREAD];

    //Set the end point of each thread
    int end[5] = {10000,20000,30000,40000,50000};
    
    //Create the thread and set the end point for each thread
    pthread_create(&thread[0],NULL,&compute_prime,&end[0]);
    pthread_create(&thread[1],NULL,&compute_prime,&end[1]);
    pthread_create(&thread[2],NULL,&compute_prime,&end[2]);
    pthread_create(&thread[3],NULL,&compute_prime,&end[3]);
    pthread_create(&thread[4],NULL,&compute_prime,&end[4]);
    
    //Join the thread so that the main thread won't finish first
    pthread_join(thread[0],NULL);
    pthread_join(thread[1],NULL);
    pthread_join(thread[2],NULL);
    pthread_join(thread[3],NULL);
    pthread_join(thread[4],NULL);
    
    //Print all prime number
    for(int i = 0; i < N_PRIME; i++){
        if(primeNum[i] == 0) printf("%6d",i);
    }
    
    return 0;
}
