/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htizi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 17:54:58 by htizi             #+#    #+#             */
/*   Updated: 2021/12/12 15:18:01 by htizi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>

typedef struct s_philo {
	int			n_philos;
	int			n_meals;
	int			t_die;
	int			t_eat;
	int			t_sleep;
}	t_philo;

#endif
