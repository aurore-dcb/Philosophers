/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:06:22 by aducobu           #+#    #+#             */
/*   Updated: 2023/10/16 10:17:18 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_unlock(t_data *philo, t_init *data)
{
	pthread_mutex_unlock(&data->forks[philo->num - 1]);
	pthread_mutex_unlock(&data->forks[philo->num % data->nb_philo]);
}

int	ft_print(t_init *data, t_data *philo, int act)
{
	struct timeval	now;
	int				diff;

	pthread_mutex_lock(&data->printf_mutex);
	if (ft_check_flag(data))
		return (pthread_mutex_unlock(&data->printf_mutex), 1);
	gettimeofday(&now, NULL);
	diff = ((now.tv_sec * 1000000 + now.tv_usec) - (data->init_time.tv_sec
				* 1000000 + data->init_time.tv_usec)) / 1000;
	if (act == 1)
		printf("%d %d has taken a fork\n", diff, philo->num);
	else if (act == 2)
	{
		printf("%d %d is eating\n", diff, philo->num);
		philo->last_meal = now;
		philo->meals--;
	}
	else if (act == 3)
		printf("%d %d is sleeping\n", diff, philo->num);
	else if (act == 4)
		printf("%d %d is thinking\n", diff, philo->num);
	else if (act == 5)
		printf("%d %d died\n", diff, philo->num);
	pthread_mutex_unlock(&data->printf_mutex);
	return (0);
}

long int	get_actual_time(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec * 1000 + now.tv_usec / 1000));
}

int	ft_check_flag(t_init *data)
{
	pthread_mutex_lock(&data->flag);
	if (data->flag_death == 1)
		return (pthread_mutex_unlock(&data->flag), 1);
	pthread_mutex_unlock(&data->flag);
	return (0);
}

void	*routine(void *arg)
{
	t_data	*philo;

	philo = (t_data *)arg;
	while (philo->meals != 0)
	{
		if (ft_check_flag(philo->data))
			return (NULL);
		if (take_forks(philo, philo->data))
			return (NULL);
		if (ft_print(philo->data, philo, 2))
			return (ft_unlock(philo, philo->data), NULL);
		my_usleep(philo->data->time_to_eat);
		philo->meals--;
		give_forks(philo, philo->data);
		if (ft_check_flag(philo->data))
			return (NULL);
		if (ft_print(philo->data, philo, 3))
			return (NULL);
		my_usleep(philo->data->time_to_sleep);
		if (ft_check_flag(philo->data))
			return (NULL);
		if (ft_print(philo->data, philo, 4))
			return (NULL);
	}
	return (NULL);
}
