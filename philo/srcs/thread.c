/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htizi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 05:36:59 by htizi             #+#    #+#             */
/*   Updated: 2021/12/19 16:11:37 by htizi            ###   ########.fr       */
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
	int		stop;

	philo = (t_philo *)arg;
	stop = 0;
	while (!stop)
	{
		pthread_mutex_lock(&philo->m_last_meal);
		if (get_time() - philo->last_meal >= philo->t_die)
		{
			pthread_mutex_unlock(&philo->m_last_meal);
			pthread_mutex_lock(&philo->info->m_msg);
			print_status(philo, 0);
			pthread_mutex_unlock(&philo->info->m_msg);
		}
		else
			pthread_mutex_unlock(&philo->m_last_meal);
		pthread_mutex_lock(&philo->info->m_stop);
		stop = philo->info->is_dead + philo->is_full;
		pthread_mutex_unlock(&philo->info->m_stop);
	}
	return (NULL);
}

void	*activity(void *arg)
{
	t_philo	*philo;
	int		stop;

	stop = 0;
	philo = (t_philo *) arg;
	philo->last_meal = philo->info->t_start;
	if (pthread_create(&philo->reaper, NULL, &is_dead, philo))
	{
		free_vars(NULL, NULL, NULL, PTHREAD_CREATE);
		return (NULL);
	}
	pthread_detach(philo->reaper);
	while (!stop)
	{
		routine(philo);
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
		if (pthread_create(&thread[i], NULL, &activity, &philo[i]))
		{
			free_vars(philo, thread, forks, PTHREAD_CREATE);
			return ;
		}
		i++;
	}
	i = 0;
	while (i < info->n_philos)
	{
		if (pthread_join(thread[i], NULL))
		{
			free_vars(philo, thread, forks, PTHREAD_JOIN);
			return ;
		}
		i++;
	}
}
