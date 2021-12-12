/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htizi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 17:37:34 by htizi             #+#    #+#             */
/*   Updated: 2021/12/12 16:06:55 by htizi            ###   ########.fr       */
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
			printf("c = %c\n", argv[i][j]);
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (-1);
			j++;
		}
		i++;
	}
	return (1);
}

int	init_philo(t_philo *philo, int argc, char **argv)
{
	if(check_arg(argc, argv) == -1)
		return (-1);
	
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo	philo;

	if (argc < 5 || argc > 6 || init_philo(&philo, argc, argv) == -1)
	{
		printf("Error\nInvalid arguments\n");
		return (1);
	}
	return (0);
}
