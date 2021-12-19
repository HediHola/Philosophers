/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htizi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 17:37:34 by htizi             #+#    #+#             */
/*   Updated: 2021/12/19 00:38:15 by htizi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	free_vars(t_philo *philo, pthread_t *thread,
		pthread_mutex_t *forks, int flag)
{
	if (flag == PTHREAD_CREATE || flag == PTHREAD_JOIN)
	{
		pthread_mutex_lock(&philo->info->m_stop);
		philo->info->is_dead = 1;
		pthread_mutex_unlock(&philo->info->m_stop);
		pthread_mutex_lock(&philo->info->m_msg);
		if (flag == PTHREAD_CREATE)
			perror("pthread_create has failed");
		if (flag == PTHREAD_JOIN)
			perror("pthread_join has failed");	
		pthread_mutex_unlock(&philo->info->m_msg); // p-e à suppr
		return (0);
	}
	if (philo)
		free (philo);
	if (thread)
		free(thread);
	if (forks)
		free(forks);
	if (flag == MALLOC)
	{		
		perror("malloc error");
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
	if (argc == 6 && (char_to_uint(argv[5]) == 0))
		return (-1);
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
	init_info(&info, philo);
	malloc_threads_and_forks(&thread, &forks, philo);
	distribute_forks(philo, forks, info.n_philos);
	launch_threading(thread, &info, philo, forks);
	destroy_mutex(&info, philo, forks);
	free_vars(philo, thread, forks, INDEX);
	return (0);
}
