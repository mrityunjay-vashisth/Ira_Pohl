#include <stdio.h>
#include <pthread.h>

#define N 2
#define TRUE 1
#define FALSE 0

int interested[N];
int turn;
int count = 0;
const int max = 1e9;


void init() {
	interested[0] = interested[1] = FALSE;
	turn = 0;
}


void enter_critical_section(int self) {
	interested[self] = TRUE;
	turn = 1 - self;
	while (interested[1 - self] && turn == 1 - self);
}


void exit_critical_section(int self) {
	interested[self] = FALSE;
}


void* peterson_sol(void *s) {
	int self = (int *)s;
	printf("Thread entered : %d\n", self);

	enter_critical_section(self);

	for(int i = 0; i < max; i++)
		count++;

	exit_critical_section(self);
}


int main(int argc, char const *argv[])
{
	pthread_t p0, p1;
	init();


	pthread_create(&p0, NULL, peterson_sol, (void*)0);
	pthread_create(&p1, NULL, peterson_sol, (void*)1);

	pthread_join(p0, NULL);
	pthread_join(p1, NULL);

	printf("Actual Count: %d | Expected Count: %d\n", 
                                        count, max*2); 
	return 0;
}