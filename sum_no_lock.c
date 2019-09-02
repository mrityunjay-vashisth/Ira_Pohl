#include <stdio.h>
#include <pthread.h>

#define MAX 10000000

int sum = 0;


void *count_val(void *param) {
	int i;
	for(i = 0; i < MAX; i++)
		sum++;

	return NULL;
}


int main(int argc, char const *argv[])
{
	pthread_t p1, p2;

	pthread_create(&p1, NULL, count_val, NULL);
	pthread_create(&p2, NULL, count_val, NULL);


	pthread_join(p1, NULL);
	pthread_join(p2, NULL);

	printf("ARRRRG sum is %d\n", sum);
	return 0;
}