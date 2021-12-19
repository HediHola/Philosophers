/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htizi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 12:25:29 by htizi             #+#    #+#             */
/*   Updated: 2021/12/19 00:41:04 by htizi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	distribute_forks(t_philo *philo, pthread_mutex_t *forks, unsigned int n)
{
	unsigned int	i;

	pthread_mutex_init(&forks[0], NULL);
	philo[0].l_fork = &forks[0];
	philo[0].r_fork = &forks[n - 1];
	i = 1;
	while (i < n)
	{
		pthread_mutex_init(&forks[i], NULL);
		philo[i].l_fork = &forks[i];
		philo[i].r_fork = &forks[i - 1];
		i++;
	}
}

unsigned int	char_to_uint(char *str)
{
	int				i;
	unsigned int	ret;

	ret = 0;
	i = 0;
	while (str[i])
	{
		ret = (ret * 10) + (str[i] - '0');
		i++;
	}
	return (ret);
}

int	malloc_threads_and_forks(pthread_t **thread, pthread_mutex_t **forks,
		t_philo *philo)
{
	*thread = malloc(sizeof(pthread_t) * philo[0].n_philos);
	if (!thread)
		free_vars(philo, *thread, *forks, MALLOC);
	*forks = malloc(sizeof(pthread_mutex_t) * philo[0].n_philos);
	if (!forks)
		free_vars(philo, *thread, *forks, MALLOC);
	return (0);
}

t_philo	*init_philo(int argc, char **argv, pthread_t *thread,
		pthread_mutex_t *forks)
{
	t_philo			*philo;
	unsigned int	n_philo;
	unsigned int	i;

	i = 0;
	n_philo = char_to_uint(argv[1]);
	philo = malloc(sizeof(t_philo) * n_philo);
	if (!philo)
		free_vars(philo, thread, forks, MALLOC);
	while (i < n_philo)
	{
		philo[i].n_philos = n_philo;
		philo[i].n_meals_had = 0;
		philo[i].t_die = char_to_uint(argv[2]);
		philo[i].t_eat = char_to_uint(argv[3]);
		philo[i].t_sleep = char_to_uint(argv[4]);
		philo[i].id = i + 1;
		if (argc == 6)
			philo[i].n_meals_to_have = char_to_uint(argv[5]);
		else
			philo[i].n_meals_to_have = 0;
		i++;
	}
	return (philo);
}

void	init_info(t_info *info, t_philo *philo)
{
	unsigned int	i;

	i = 0;
	info->n_philos = philo->n_philos;
	info->n_meals_to_have = philo->n_meals_to_have;
	info->is_dead = 0;
	pthread_mutex_init(&info->m_stop, NULL);
	pthread_mutex_init(&info->m_msg, NULL);
	while (i < philo[0].n_philos)
	{
		philo[i].info = info;
		pthread_mutex_init(&philo[i].m_last_meal, NULL);
		i++;
	}
}
