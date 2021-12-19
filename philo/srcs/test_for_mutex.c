#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <sys/time.h>

void	*print(void *arg)
{
	pthread_mutex_t	*msg;

	msg = (pthread_mutex_t *)arg;
	pthread_mutex_lock(msg);
	printf("Passage dans print");
	return (NULL);
}

int	main(void)
{
	pthread_mutex_t	*msg;
	pthread_t		*thread;

	thread = malloc(sizeof(pthread_t));
		pthread_create(&*thread, NULL, &print, &msg);
	pthread_join(*thread, NULL);
	pthread_mutex_lock(msg);
	printf("Passage main\n");
	return (0);
}
