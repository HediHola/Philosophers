/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htizi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 17:54:58 by htizi             #+#    #+#             */
/*   Updated: 2021/12/14 17:13:27 by htizi            ###   ########.fr       */
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

typedef struct s_philo {
	unsigned int			n_philos;
	unsigned int			n_meals;
	unsigned int			t_die;
	unsigned int			t_eat;
	unsigned int			t_sleep;
	unsigned int			id;
	pthread_t				faucheuse;
	pthread_mutex_t			*r_fork;
	pthread_mutex_t			*l_fork;
}	t_philo;

#endif
