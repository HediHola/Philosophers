/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htizi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 17:54:58 by htizi             #+#    #+#             */
/*   Updated: 2021/12/17 16:35:12 by htizi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <errno.h>
# include <sys/time.h>

typedef struct s_info
{
	unsigned int	n_meals;
	unsigned int	n_philos;
	unsigned int	t_start;
	int				is_dead;
	pthread_mutex_t	m_stop;
	pthread_mutex_t	m_msg;
}	t_info;

typedef struct s_philo {
	unsigned int			n_philos;
	unsigned int			n_meals;
	unsigned int			t_die;
	unsigned int			t_eat;
	unsigned int			t_sleep;
	unsigned int			last_meal;
	unsigned int			id;
	int				is_full;
	t_info				*info;
	pthread_t			reaper;
	pthread_mutex_t			*r_fork;
	pthread_mutex_t			*l_fork;
	pthread_mutex_t			m_last_meal;
}	t_philo;

int				malloc_threads_and_forks(pthread_t **thread,
					pthread_mutex_t **forks, t_philo *philo);
t_philo			*init_philo(int argc, char **argv, pthread_t *thread,
					pthread_mutex_t *forks);
int				free_vars(t_philo *philo, pthread_t *thread,
					pthread_mutex_t *forks, int flag);
void			distribute_forks(t_philo *philo, pthread_mutex_t *forks,
					unsigned int n);
unsigned int	get_time(void);
void			init_info(t_info *info, t_philo *philo);
void			launch_threading(pthread_t *thread, t_info *info,
					t_philo *philo, pthread_mutex_t *forks);
void			destroy_mutex(t_info *info, t_philo *philo, pthread_mutex_t *forks);

#endif
