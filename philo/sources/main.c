/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 13:06:10 by aducobu           #+#    #+#             */
/*   Updated: 2023/10/19 13:33:08 by aducobu          ###   ########.fr       */
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
	data->nb_meals = -2;
	if (argc == 6)
		data->nb_meals = ft_atoi(argv[5]);
	if (data->nb_philo == 0 || data->nb_meals == 0)
		return (0);
	// gettimeofday(&data->init_time, NULL);
	// data->flag_death = 0;
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
	gettimeofday(&data->init_time, NULL);
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
	return(lauch_threads(data));
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

	if (!parsing(argc, argv, &data))
		return (1);
	// init_data(&data, argv, argc);
	init_philo_mutex(&data);
	// if (!init_philo_mutex(&data))
	// 	return (printf("Error initialization\n"), 1);
	// if (!lauch_threads(&data))
	// 	return (printf("Error threads\n"), 1);
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
		usleep(100);
	}
}
