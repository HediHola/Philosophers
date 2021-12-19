/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htizi <htizi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 20:56:20 by htizi             #+#    #+#             */
/*   Updated: 2021/12/19 01:25:39 by htizi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	right_handed(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	pthread_mutex_unlock(&philo->info->m_msg);
	printf("%d   %d   has taken a fork\n", get_time() - philo->info->t_start, philo->id);
	pthread_mutex_unlock(&philo->info->m_msg);
/*	if (philo->n == 1)
	{
		pthread_mutex_unlock(philo->r_fork);
		ft_usleep(philo->t_die);
		return ;
	}
*/	pthread_mutex_lock(philo->l_fork);
	pthread_mutex_lock(&philo->info->m_msg);
	printf("%d   %d   has taken a fork\n", get_time() - philo->info->t_start, philo->id);
	pthread_mutex_unlock(&philo->info->m_msg);
	pthread_mutex_lock(&philo->info->m_msg);
	printf("%d   %d   is eating\n", get_time() - philo->info->t_start, philo->id);
	pthread_mutex_unlock(&philo->info->m_msg);
	philo->n_meals_had++;
	pthread_mutex_lock(&philo->m_last_meal);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->m_last_meal);
	ft_usleep(philo->t_eat);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

void	left_handed(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	pthread_mutex_lock(&philo->info->m_msg);
	printf("%d   %d   has taken a fork\n", get_time() - philo->info->t_start, philo->id);
	pthread_mutex_unlock(&philo->info->m_msg);
/*	if (p->n == 1)
	{
		pthread_mutex_unlock(philo->l_fork);
		ft_usleep(philo->t_die);
		return ;
	}
*/	pthread_mutex_lock(philo->r_fork);
	pthread_mutex_lock(&philo->info->m_msg);
	printf("%d   %d   has taken a fork\n", get_time() - philo->info->t_start, philo->id);
	pthread_mutex_unlock(&philo->info->m_msg);
	pthread_mutex_lock(&philo->info->m_msg);
	printf("%d   %d   is eating\n", get_time() - philo->info->t_start, philo->id);
	pthread_mutex_unlock(&philo->info->m_msg);
	philo->n_meals_had++;
	pthread_mutex_lock(&philo->m_last_meal);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->m_last_meal);
	ft_usleep(philo->t_eat);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
		right_handed(philo);
	else
		left_handed(philo);
}

void	routine(t_philo *philo)
{
	eat(philo);
	if (philo->n_meals_to_have != 0 &&
			philo->n_meals_had == philo->n_meals_to_have)
	{
		pthread_mutex_lock(&philo->info->m_stop);
		philo->is_full = 1;
		pthread_mutex_unlock(&philo->info->m_stop);
		return ;
	}
	pthread_mutex_lock(&philo->info->m_stop);
	printf("%d   %d   is sleeping\n", get_time() - philo->info->t_start, philo->id);
	pthread_mutex_unlock(&philo->info->m_stop);
	ft_usleep(philo->t_sleep);
	pthread_mutex_lock(&philo->info->m_stop);
	printf("%d   %d   is thinking\n", get_time() - philo->info->t_start, philo->id);
	pthread_mutex_unlock(&philo->info->m_stop);
	if (philo->n_philos % 2 != 0)
		ft_usleep(100);
}
