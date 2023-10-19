/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 13:06:10 by aducobu           #+#    #+#             */
/*   Updated: 2023/10/19 14:19:26 by aducobu          ###   ########.fr       */
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
	if (data->nb_philo == 0)
		return (0);
	gettimeofday(&data->init_time, NULL);
	data->flag_death = 0;
	return (1);
}

int	init_philo_mutex(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	data->philo = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->forks || !data->philo)
		return (0);
	memset(data->philo, 0, sizeof(t_philo) * data->nb_philo);
	pthread_mutex_init(&data->printf_mutex, NULL);
	pthread_mutex_init(&data->flag_mutex, NULL);
	while (i < data->nb_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		pthread_mutex_init(&data->philo[i].eat_mutex, NULL);
		data->philo[i].num = i + 1;
		data->philo[i].data = data;
		data->philo[i].fork_l = (i + 1) % data->nb_philo;
		data->philo[i].fork_r = i;
		data->philo[i].last_meal = data->init_time;
		data->philo[i].meals = -2;
		if (data->argc == 6)
			data->philo[i].meals = ft_atoi(data->argv[5]);
		i++;
	}
	return (lauch_threads(data));
}

int	lauch_threads(t_data *data)
{
	int			i;
	pthread_t	monitor_id;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_create(&data->philo[i].id, NULL, routine, &data->philo[i]))
			return (0);
		i++;
	}
	if (pthread_create(&monitor_id, NULL, monitor, data))
		return (0);
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(data->philo[i].id, NULL);
		i++;
	}
	pthread_join(monitor_id, NULL);
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (!parsing(argc, argv, &data))
		return (1);
	if (!init_philo_mutex(&data))
		return (printf("Error\n"), 1);
	free_all(&data);
	return (0);
}
