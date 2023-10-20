/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intitialization.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 13:11:02 by aducobu           #+#    #+#             */
/*   Updated: 2023/10/20 13:12:46 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	lauch_threads(t_data *data)
{
	int			i;
	pthread_t	monitor_id;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_create(&data->philo[i].id, NULL, routine, &data->philo[i]))
			return (1);
		i++;
	}
	if (pthread_create(&monitor_id, NULL, monitor, data))
		return (1);
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(data->philo[i].id, NULL);
		i++;
	}
	pthread_join(monitor_id, NULL);
	return (0);
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
	data->init_time = get_actual_time();
	while (i < data->nb_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		pthread_mutex_init(&data->philo[i].eat_mutex, NULL);
		data->philo[i].num = i + 1;
		data->philo[i].data = data;
		data->philo[i].fork_l = i;
		data->philo[i].fork_r = (i + 1) % data->nb_philo;
		data->philo[i].last_meal = data->init_time;
		i++;
	}
	return (lauch_threads(data));
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
