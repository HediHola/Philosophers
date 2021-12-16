/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htizi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 17:37:34 by htizi             #+#    #+#             */
/*   Updated: 2021/12/16 06:44:29 by htizi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	free_vars(t_philo *philo, pthread_t *thread,
		pthread_mutex_t *forks, int flag)
{
	if (philo)
		free (philo);
	if (thread)
		free(thread);
	if (forks)
		free(forks);
	if (flag < 0)
	{
		if (flag == -1)
			perror("malloc error");
		if (flag == -2)
			perror("pthread_create has failed");
		if (flag == -3)
			perror("pthread_join has failed");
		exit (0);
	}
	return (0);
}

int	check_arg(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] == '+' && j == 0)
				j++;
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (-1);
			j++;
		}
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_philo			*philo;
	t_info			info;
	pthread_t		*thread;
	pthread_mutex_t	*forks;

	thread = NULL;
	forks = NULL;
	if (argc < 5 || argc > 6 || check_arg(argc, argv) == -1)
	{
		printf("Error\nInvalid arguments\n");
		return (1);
	}
	philo = init_philo(argc, argv, thread, forks);
	init_info(&info, *philo);
	malloc_threads_and_forks(&thread, &forks, philo);
	distribute_forks(philo, forks, info.n_philos);
	launch_threading(thread, &info, philo, forks);
	//destroy_mutex(&info, forks);
	free_vars(philo, thread, forks, 0);
	return (0);
}
