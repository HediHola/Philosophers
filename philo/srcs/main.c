/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htizi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 17:37:34 by htizi             #+#    #+#             */
/*   Updated: 2021/12/14 11:37:51 by htizi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

t_philo	*init_philo(int argc, char **argv)
{
	t_philo			*philo;
	unsigned int	n_philo;
	unsigned int	i;

	i = 0;
	n_philo = char_to_uint(argv[1]);
	philo = malloc(sizeof(t_philo) * n_philo);
	if (!philo)
		return (0);
	while (i < n_philo)
	{
		philo[i].n_philos = n_philo;
		philo[i].t_die = char_to_uint(argv[2]);
		philo[i].t_eat = char_to_uint(argv[3]);
		philo[i].t_sleep = char_to_uint(argv[4]);
		philo[i].id = i + 1;
		if (argc == 6)
			philo[i].n_meals = char_to_uint(argv[5]);
		else
			philo[i].n_meals = -1;
		i++;
	}
	return (philo);
}

int	main(int argc, char **argv)
{
	t_philo			*philo;
	pthread_t		*thread;
	pthread_mutex_t	forks;

	if (argc < 5 || argc > 6 || check_arg(argc, argv) == -1)
	{
		printf("Error\nInvalid arguments\n");
		return (1);
	}
//	if	(!(philo = init_philo(argc, argv)))
//		return (
	free(philo);
	return (0);
}
