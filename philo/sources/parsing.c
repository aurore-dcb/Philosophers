/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:49:00 by aducobu           #+#    #+#             */
/*   Updated: 2023/10/20 13:16:54 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	init_data(t_data *data, char **argv, int argc)
{
	memset(data, 0, sizeof(t_data));
	data->argv = argv;
	data->argc = argc;
	data->nb_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->meals = -1;
	if (argc == 6)
		data->meals = ft_atoi(argv[5]);
	if (data->meals == 0 || data->nb_philo == 0)
		return (0);
	return (1);
}

int	parsing(int argc, char **argv, t_data *data)
{
	int	i;
	int	num;

	i = 1;
	if (argc >= 5 && argc <= 6)
	{
		while (i < argc)
		{
			num = ft_atoi(argv[i]);
			if (num < 0)
			{
				printf("Error parsing : wrong format of argument\n");
				printf(
					"You need to put positive number (integer) as arguments\n");
				return (0);
			}
			i++;
		}
		return (init_data(data, argv, argc));
	}
	return (0);
}
