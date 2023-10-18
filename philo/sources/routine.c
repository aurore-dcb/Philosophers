/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:06:22 by aducobu           #+#    #+#             */
/*   Updated: 2023/10/18 15:32:54 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_unlock(t_philo *philo, t_data *data)
{
	pthread_mutex_unlock(&data->forks[philo->fork_r]);
	pthread_mutex_unlock(&data->forks[philo->fork_l]);
}

int	ft_print(t_data *data, t_philo *philo, int act)
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
		pthread_mutex_lock(&philo->eat_mutex);
		philo->last_meal = now;
		philo->meals--;
		pthread_mutex_unlock(&philo->eat_mutex);
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

int	ft_check_flag(t_data *data)
{
	pthread_mutex_lock(&data->flag_mutex);
	if (data->flag_death == 1)
		return (pthread_mutex_unlock(&data->flag_mutex), 1);
	pthread_mutex_unlock(&data->flag_mutex);
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	
	philo = (t_philo *)arg;
	while (1)
	{
		if (ft_check_flag(philo->data))
			return (NULL);
		if (take_forks(philo, philo->data))
			return (NULL);
		if (ft_print(philo->data, philo, 2))
			return (ft_unlock(philo, philo->data), NULL);
		my_usleep(philo->data->time_to_eat);
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
		my_usleep(((philo->data->time_to_die - \
			(philo->data->time_to_eat + philo->data->time_to_sleep)) / 2));
	}
	return (NULL);
}
