/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:49:00 by aducobu           #+#    #+#             */
/*   Updated: 2023/10/09 13:08:07 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int		i;
	long	n;

	i = 0;
	n = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			return (-1);
		i++;
	}
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (-1);
		while (str[i] >= '0' && str[i] <= '9')
			n = n * 10 + (str[i++] - 48);
		if (n > 2147483647)
			return (-1);
	}
	return (n);
}

int	parsing(int argc, char **argv, char **env)
{
	int	i;
	int	num;

	(void)env;
	i = 1;
	if (!(argc == 5 || argc == 6))
		return (printf("Error parsing : wrong number of arguments\n"), 0);
	while (i < argc)
	{
		if (!argv[i])
			num = -1;
		num = ft_atoi(argv[i]);
		if (num < 0)
		{
			printf("Error parsing : wrong format of argument\n");
			printf("You need to put positive number (integer) as arguments\n");
			return (0);
		}
		i++;
	}
	if (ft_atoi(argv[1]) > 200)
		return (printf("Error parsing : The number of philosophers is too high"),
			0);
	return (1);
}
