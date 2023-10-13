/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurore <aurore@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:06:22 by aducobu           #+#    #+#             */
/*   Updated: 2023/10/13 10:44:31 by aurore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	take_forks(t_data *philo, t_init *data)
{
	int	left;
	int	right;
	long int diff;

	left = philo->num % philo->data->nb_philo;
	right = philo->num - 1;
	if (philo->num % 2 == 0)
	{
		pthread_mutex_lock(&data->forks[right]);
		pthread_mutex_lock(&data->printf_mutex);
		diff = get_actual_time() - ((data->init_time.tv_sec * 1000)
				+ (data->init_time.tv_usec / 1000));
		printf("%ld %d has taken a fork\n", diff, philo->num);
		pthread_mutex_unlock(&data->printf_mutex);
		pthread_mutex_lock(&data->forks[left]);
		pthread_mutex_lock(&data->printf_mutex);
		diff = get_actual_time() - ((data->init_time.tv_sec * 1000)
				+ (data->init_time.tv_usec / 1000));
		printf("%ld %d has taken a fork\n", diff, philo->num);
		pthread_mutex_unlock(&data->printf_mutex);
	}
	else
	{
		pthread_mutex_lock(&data->forks[left]);
		pthread_mutex_lock(&data->printf_mutex);
		diff = get_actual_time() - ((data->init_time.tv_sec * 1000)
				+ (data->init_time.tv_usec / 1000));
		printf("%ld %d has taken a fork\n", diff, philo->num);
		pthread_mutex_unlock(&data->printf_mutex);
		pthread_mutex_lock(&data->forks[right]);
		pthread_mutex_lock(&data->printf_mutex);
		diff = get_actual_time() - ((data->init_time.tv_sec * 1000)
				+ (data->init_time.tv_usec / 1000));
		printf("%ld %d has taken a fork\n", diff, philo->num);
		pthread_mutex_unlock(&data->printf_mutex);
	}
}

void	give_forks(t_data *philo, t_init *data)
{
	int	left;
	int	right;

	left = philo->num % data->nb_philo;
	right = philo->num - 1;
	if (philo->num % 2 == 0)
	{
		pthread_mutex_unlock(&data->forks[right]);
		pthread_mutex_unlock(&data->forks[left]);
	}
	else
	{
		pthread_mutex_unlock(&data->forks[left]);
		pthread_mutex_unlock(&data->forks[right]);
	}
}

long int	get_actual_time(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec * 1000 + now.tv_usec / 1000)); // milliseconde
}

void	*routine(void *arg)
{
	t_data		*philo;
	t_init		*data;
	long int	diff;

	philo = (t_data *)arg;
	data = philo->data;
	while (philo->meals != 0)
	{
		take_forks(philo, data);
		pthread_mutex_lock(&data->printf_mutex);
		diff = get_actual_time() - ((data->init_time.tv_sec * 1000)
				+ (data->init_time.tv_usec / 1000));
		printf("%ld %d is eating\n", diff, philo->num);
		pthread_mutex_unlock(&data->printf_mutex);
		philo->meals--;
		my_usleep(data->time_to_eat);
		give_forks(philo, data);
		pthread_mutex_lock(&data->printf_mutex);
		diff = get_actual_time() - ((data->init_time.tv_sec * 1000)
				+ (data->init_time.tv_usec / 1000));
		printf("%ld %d is sleeping\n", diff, philo->num);
		pthread_mutex_unlock(&data->printf_mutex);
		my_usleep(data->time_to_sleep);
		pthread_mutex_lock(&data->printf_mutex);
		diff = get_actual_time() - ((data->init_time.tv_sec * 1000)
				+ (data->init_time.tv_usec / 1000));
		printf("%ld %d is thinking\n", diff, philo->num);
		pthread_mutex_unlock(&data->printf_mutex);
	}
	return (NULL);
}
