/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htizi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 05:36:59 by htizi             #+#    #+#             */
/*   Updated: 2021/12/17 16:51:25 by htizi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (s)
	{
		while (s[i])
		{
			write(fd, &s[i], 1);
			i++;
		}
		write(fd, "\n", 1);
	}
}

void	destroy_mutex(t_info *info, t_philo *philo, pthread_mutex_t *forks)
{
	unsigned int	i;

	i = 0;
	while (i < info->n_philos)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	pthread_mutex_destroy(&philo->m_last_meal);
	pthread_mutex_destroy(&info->m_msg);
	pthread_mutex_destroy(&info->m_stop);
}

void	*is_dead(void *arg)
{
	t_philo	*philo;
	int	stop;

	philo = (t_philo *)arg;
	stop = 0;
	while (!stop)
	{
		pthread_mutex_lock(&philo->m_last_meal);
		if (get_time() - philo->last_meal >= philo->t_die)
		{
			pthread_mutex_unlock(&philo->m_last_meal);
			pthread_mutex_lock(&philo->info->m_msg);
			printf("philo n%d died\n", philo->id);
			pthread_mutex_unlock(&philo->info->m_msg);
			philo->info->is_dead = 1; // added
		}
		else
			pthread_mutex_unlock(&philo->m_last_meal);
		pthread_mutex_lock(&philo->info->m_stop);
		stop = philo->info->is_dead + philo->is_full;
		pthread_mutex_unlock(&philo->info->m_stop);
	}
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	int		stop;

	stop = 0;
	philo = (t_philo *) arg;
	philo->last_meal = philo->info->t_start;
	if (pthread_create(&philo->reaper, NULL, &is_dead, philo))
	{
		stop = 1;
		ft_putendl_fd("pthread_create has failed", 2);
	}
	pthread_join(philo->reaper, NULL);
	while (!stop)
	{
		activity(philo);
		pthread_mutex_lock(&philo->info->m_stop);
		stop = philo->info->is_dead + philo->is_full;
		pthread_mutex_unlock(&philo->info->m_stop);
	}
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
