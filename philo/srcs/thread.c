/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htizi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 05:36:59 by htizi             #+#    #+#             */
/*   Updated: 2021/12/16 05:45:51 by htizi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutex(t_info *info, pthread_mutex_t *forks)
{
	unsigned int	i;

	i = 0;
	while (i < info->n_philos)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	pthread_mutex_destroy(&info->m_last_eat);
	pthread_mutex_destroy(&info->m_msg);
	pthread_mutex_destroy(&info->m_stop);
}

void	*routine(void *philo_src)
{
	t_philo	*philo_dest;

	philo_dest = (t_philo *) philo_src;
	printf("thread : I'm philo %u\n", philo_dest->id);
	philo_dest->id *= 2;
	return (NULL);
}

void	launch_threading(pthread_t *thread, t_info *info, t_philo *philo,
			pthread_mutex_t *forks)
{
	unsigned int	i;

	i = 0;
	info->t_start = get_time();
	while (i < info->n_philos)
	{
		if (pthread_create(&thread[i], NULL, &routine, &philo[i]))
			free_vars(philo, thread, forks, -2);
		i++;
	}
	i = 0;
	while (i < info->n_philos)
	{
		if (pthread_join(thread[i], NULL))
			free_vars(philo, thread, forks, -3);
		i++;
	}
}
