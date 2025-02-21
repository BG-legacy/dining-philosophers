// Please change the following into your name
// #0#BEGIN# DO NOT MODIFIE THIS COMMENT LINE!
// Bernard
// Ginn
// #0#END# DO NOT MODIFIE THIS COMMENT LINE!
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>           /* For O_* constants */
 
#define N 5
// here we use 5 different semaphores, each chopstick use one
// semaphore. Initally, the value for each is 1. After using one
// resource (chopstick), the value -1. 0 means currently not available
sem_t *chopsticks[N];

// We do not use mutex, we set up a new semaphore 
// called m
// #1#BEGIN# DO NOT MODIFIE THIS COMMENT LINE!
sem_t *m;
// #1#END# DO NOT MODIFIE THIS COMMENT LINE!

//The id of 5 philosophers 
int philosophers[N] = {0, 1, 2, 3, 4};
 
void delay (int len) {
    int i = rand() % len;
    int x;
    while (i > 0) {
        x = rand() % len;
        while (x > 0) {
            x--;
        }
        i--;
    }
}

void *philosopher (void* arg) {
    int i = *(int *)arg;
    int right = i;// right hand chopstick indexed as the same id of the philospher
    int left = (i + 1) % N;// left hand chopstick index as the id of the philospher + 1
    while (1) {
        printf("Philosopher %d is thinking\n", i);
        delay(60000);

        printf("Philosopher %d is hungry \n", i);

        // wait for the semaphore m first, make sure no more than 4 philoshpers
        // pick their first chopstick at the same time.
        // #2#BEGIN# DO NOT MODIFIE THIS COMMENT LINE!
        sem_wait(m);
        // #2#END# DO NOT MODIFIE THIS COMMENT LINE!

        // wait for first (right) chopstick to use
        // after using it, the value will decrease 1
        // THAT IS WHY use need to use &, because the semaphore need to be modified
        sem_wait(chopsticks[right]);
        printf("Philosopher %d picked up Chopstick %d, can not eat with one chopstick.\n", i, right);

        // wati to use the left chopstick
        sem_wait(chopsticks[left]);
        printf("Philosopher %d picked up Chopstick %d, now is eating with two chopsticks.\n", i, left);
        delay(60000);

        // release the first chopstick, increase the semaphore 1 by sem_post 
        sem_post(chopsticks[right]);
        printf("Philosopher %d put down Chopstick %d\n", i, right);

        // when any right chopstick been released,
        // increase semaphore m to release one capacity       
        // #3#BEGIN# DO NOT MODIFIE THIS COMMENT LINE!
        sem_post(m);
        // #3#END# DO NOT MODIFIE THIS COMMENT LINE!

        sem_post(chopsticks[left]);
        printf("Philosopher %d put down Chopstick %d\n", i, left);
    }
}
 
int main (int argc, char **argv) {
    srand(time(NULL));
    pthread_t philo[N];

    int i;
    // change your the following id into your banner id
    // #8#BEGIN# DO NOT MODIFIE THIS COMMENT LINE!
    int banner_id = 909478671;
    // #8#END# DO NOT MODIFIE THIS COMMENT LINE!
    printf("Banner id: %d\n", banner_id);

    // initalize the chopstick semphore
    for (i=0; i<N; i++) {
        char name[20];
        sprintf(name, "/chop%d", i);
        chopsticks[i] = sem_open(name, O_CREAT, 0644, 1);
    }
    m = sem_open("/mutex", O_CREAT, 0644, N-1);

    // create threads
    // #6#BEGIN# DO NOT MODIFIE THIS COMMENT LINE!
    for (i=0; i<N; i++) {
        pthread_create(&philo[i], NULL, philosopher, &philosophers[i]);
    }
    // #6#END# DO NOT MODIFIE THIS COMMENT LINE!


    // put threads into the system
    for (i=0; i<N; i++) {
        pthread_join(philo[i], NULL);
    }

    // destroy semaphores
    for (i=0; i<N; i++) {
        char name[20];
        sprintf(name, "/chop%d", i);
        sem_close(chopsticks[i]);
        sem_unlink(name);
    }
    sem_close(m);
    sem_unlink("/mutex");

    return 0;
}

