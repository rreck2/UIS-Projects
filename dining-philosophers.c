//Ryan Reck
//HW04
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#define NUMBER_OF_PHILOSOPHERS 5
#define THINKING 2
#define HUNGRY 1
#define EATING 0
#define LEFT (phnum + 4)%NUMBER_OF_PHILOSOPHERS
#define RIGHT (phnum + 1)%5
int state[NUMBER_OF_PHILOSOPHERS];
int phil[NUMBER_OF_PHILOSOPHERS] = {0, 1, 2, 3,4 };
sem_t mutex;
sem_t S[NUMBER_OF_PHILOSOPHERS];
void test(int phnum) {
	if(state[phnum] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING) {
		state[phnum] = EATING;
		sleep(2);
		printf("Philosopher %d takes fork %d and %d\n", phnum +1, LEFT +1, phnum + 1);
		printf("Philosopher %d is Eating\n", phnum + 1);
		sem_post(&S[phnum]);
	}
}

void PICKUP_FORKS(int phnum) {
	sem_wait(&mutex);
	state[phnum] = HUNGRY;
	printf("Philosopher %d is hungry\n", phnum + 1);
	test(phnum);
	sem_post(&mutex);
	sem_wait(&S[phnum]);
	sleep(1);
}

void RETURN_FORKS(int phnum){
	sem_wait(&mutex);
	state[phnum] = THINKING;
	printf("Philosopher %d putting fork %d and %d down\n" , phnum +1, LEFT +1, phnum + 1);
	printf("Philosopher %d is thinking\n", phnum + 1);
	test(LEFT);
	test(RIGHT);
	sem_post(&mutex);
}

void* philosopher(void* num){
	while(1) {
		int* i = num;
		sleep(1);
		PICKUP_FORKS(*i);
		sleep(0);
		RETURN_FORKS(*i);
	}
}

int main(){
	int i;
	pthread_t thread_id[NUMBER_OF_PHILOSOPHERS];
	sem_init(&mutex, 0 , 1);
	for( i = 0; i < NUMBER_OF_PHILOSOPHERS; i++)
		sem_init(&S[i], 0, 0);
	for(i = 0; i < NUMBER_OF_PHILOSOPHERS; i++){
		pthread_create(&thread_id[i], NULL, philosopher, &phil[i]);
		printf("Philosopher %d is thinking\n", i + 1 );
	}
	for (i = 0; i < NUMBER_OF_PHILOSOPHERS; i++)
		pthread_join(thread_id[i],NULL);
}








