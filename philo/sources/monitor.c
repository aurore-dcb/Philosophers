/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 09:40:11 by aducobu           #+#    #+#             */
/*   Updated: 2023/10/19 14:15:26 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	check_meals(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_lock(&philo[i].eat_mutex);
		if (philo[i].meals > 0 || data->argc == 5)
		{
			pthread_mutex_unlock(&philo[i].eat_mutex);
			return (0);
		}
		pthread_mutex_unlock(&philo[i].eat_mutex);
		i++;
	}
	pthread_mutex_lock(&data->flag_mutex);
	data->flag_death = 1;
	pthread_mutex_unlock(&data->flag_mutex);
	return (1);
}

int	check_death(t_data *data, t_philo *philo)
{
	struct timeval	now;
	int				diff;

	gettimeofday(&now, NULL);
	pthread_mutex_lock(&philo->eat_mutex);
	diff = ((now.tv_sec * 1000000 + now.tv_usec) - (philo->last_meal.tv_sec
				* 1000000 + philo->last_meal.tv_usec)) / 1000;
	pthread_mutex_unlock(&philo->eat_mutex);
	if (diff >= data->time_to_die)
	{
		ft_print(data, philo, "died");
		pthread_mutex_lock(&data->flag_mutex);
		data->flag_death = 1;
		pthread_mutex_unlock(&data->flag_mutex);
		return (1);
	}
	return (0);
}

void	*monitor(void *arg)
{
	int		i;
	t_data	*data;

	i = 0;
	data = (t_data *)arg;
	while (i < data->nb_philo)
	{
		if (check_meals(data, data->philo))
			return (NULL);
		if (check_death(data, &data->philo[i]))
			return (NULL);
		i++;
		if (i == data->nb_philo)
			i = 0;
		my_usleep(1);
	}
	return (NULL);
}
