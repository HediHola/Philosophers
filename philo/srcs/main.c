/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htizi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 17:37:34 by htizi             #+#    #+#             */
/*   Updated: 2021/12/15 22:47:20 by htizi            ###   ########.fr       */
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
	if (flag == -1)
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
	return (1);
}

void	launch_threading(pthread_t *thread, t_info *info, t_philo *philo); 
{
	int				i;
	unsigned int	time;
	
	i = 0;
	info->t_start = get_time();
	while (i < info->n_philo)
	{
		if
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
//	launch_threading(thread, &info, philo); 
	free_vars(philo, thread, forks, 0);
	return (0);
}
