/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:06:22 by aducobu           #+#    #+#             */
/*   Updated: 2023/10/20 13:30:09 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_print(t_data *data, t_philo *philo, char *act)
{
	int			diff;
	long long	now;

	pthread_mutex_lock(&data->flag_mutex);
	if (data->flag_death == 1)
	{
		pthread_mutex_unlock(&data->flag_mutex);
		return ;
	}
	now = get_actual_time();
	diff = now - data->init_time;
	pthread_mutex_lock(&data->printf_mutex);
	printf("%d %d %s\n", diff, philo->num, act);
	pthread_mutex_unlock(&data->printf_mutex);
	pthread_mutex_unlock(&data->flag_mutex);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (!eating(philo))
			break ;
		ft_print(philo->data, philo, "is sleeping");
		my_usleep(philo->data->time_to_sleep);
		ft_print(philo->data, philo, "is thinking");
		pthread_mutex_lock(&philo->data->flag_mutex);
		if (philo->data->flag_death == 1)
		{
			pthread_mutex_unlock(&philo->data->flag_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->data->flag_mutex);
		my_usleep(((philo->data->time_to_die - (philo->data->time_to_eat
							+ philo->data->time_to_sleep)) / 2));
	}
	return (NULL);
}

int	check_death(t_data *data, int i)
{
	long long	time;

	pthread_mutex_lock(&data->philo[i].eat_mutex);
	time = get_actual_time() - data->philo[i].last_meal;
	if (time >= data->time_to_die)
	{
		pthread_mutex_unlock(&data->philo[i].eat_mutex);
		pthread_mutex_lock(&data->flag_mutex);
		data->flag_death = 1;
		pthread_mutex_unlock(&data->flag_mutex);
		ft_print(data, &data->philo[i], "died");
		return (1);
	}
	pthread_mutex_unlock(&data->philo[i].eat_mutex);
	return (0);
}

int	check_meals(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_lock(&data->philo[i].eat_mutex);
		if (data->philo[i].meals < data->meals)
		{
			pthread_mutex_unlock(&data->philo[i].eat_mutex);
			return (0);
		}
		pthread_mutex_unlock(&data->philo[i].eat_mutex);
		i++;
	}
	pthread_mutex_lock(&data->flag_mutex);
	data->flag_death = 1;
	pthread_mutex_unlock(&data->flag_mutex);
	return (1);
}

void	*monitor(void *arg)
{
	int		i;
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		if (data->meals != -1 && check_meals(data))
			break ;
		i = 0;
		while (i < data->nb_philo)
		{
			if (check_death(data, i))
				return (NULL);
			i++;
		}
		my_usleep(1);
	}
	return (NULL);
}

