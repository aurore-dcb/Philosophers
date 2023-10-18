/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 13:06:10 by aducobu           #+#    #+#             */
/*   Updated: 2023/10/18 15:41:13 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	init_data(t_data *data, char **argv, int argc)
{
	memset(data, 0, sizeof(t_data));
	data->argv = argv;
	data->argc = argc;
	data->nb_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	gettimeofday(&data->init_time, NULL);
	data->flag_death = 0;
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
		data->philo[i].num = i + 1;
		data->philo[i].meals = -2;
		if (data->argc == 6)
			data->philo[i].meals = ft_atoi(data->argv[5]);
		data->philo[i].data = data;
		data->philo[i].fork_l = i;
		data->philo[i].fork_r = (i + 1) % data->nb_philo;
		data->philo[i].last_meal = data->init_time;
		pthread_mutex_init(&data->philo[i].eat_mutex, NULL);
		i++;
	}
	return (1);
}

int	lauch_threads(t_data *data)
{
	int			i;
	pthread_t	monitor_id;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_create(&data->philo[i].id, NULL, &routine, &data->philo[i]))
			return (0);
		i++;
	}
	if (pthread_create(&monitor_id, NULL, &monitor, data))
		return (0);
	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_join(data->philo[i].id, NULL))
			return (0);
		i++;
	}
	pthread_join(monitor_id, NULL);
	return (1);
}

void	free_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philo[i].eat_mutex);
		i++;
	}
	pthread_mutex_destroy(&data->printf_mutex);
	pthread_mutex_destroy(&data->flag_mutex);
	free(data->forks);
	free(data->philo);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (!parsing(argc, argv))
		return (1);
	if ((argc == 6 && ft_atoi(argv[5]) <= 0) || ft_atoi(argv[1]) == 0)
	{
		printf("Error parsing : wrong format of argument\n");
		printf("You need to put positive number (integer) as arguments\n");
		return (1);
	}
	init_data(&data, argv, argc);
	if (!init_philo_mutex(&data))
		return (printf("Error initialization\n"), 1);
	if (!lauch_threads(&data))
		return (printf("Error threads\n"), 1);
	free_all(&data);
	return (0);
}

void	my_usleep(unsigned int time_to_wait)
{
	struct timeval		current_time;
	struct timeval		time;
	unsigned long long	start_time;

	gettimeofday(&time, NULL);
	start_time = time.tv_sec * 1000000 + time.tv_usec;
	while (1)
	{
		gettimeofday(&current_time, NULL);
		if ((current_time.tv_sec * 1000000 + current_time.tv_usec)
			- start_time >= time_to_wait * 1000)
			break ;
	}
}
