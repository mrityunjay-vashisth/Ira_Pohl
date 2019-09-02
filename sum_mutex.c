#include <stdio.h>
#include <pthread.h>

#define MAX 10000000

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
int sum;


void* count_val(void *param) {
	int i;
	pthread_mutex_lock(&m);
	printf("Thread entered in CS: %d\n",(int*)param);
	for (i = 0; i < MAX; i++)
		sum++;
	pthread_mutex_unlock(&m);
	printf("Thread exited from CS: %d\n",(int*)param);
	return NULL;
}


int main(int argc, char const *argv[])
{
	pthread_t p1, p2;

	pthread_create(&p1, NULL, count_val, (void*)1);
	pthread_create(&p2, NULL, count_val, (void*)2);

	pthread_join(p1, NULL);
	pthread_join(p2, NULL);

	printf("Actual sum: %d Expected sum: %d\n", sum, MAX*2);
	return 0;
}