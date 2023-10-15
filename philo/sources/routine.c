/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:06:22 by aducobu           #+#    #+#             */
/*   Updated: 2023/10/15 16:31:45 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	take_forks(t_data *philo, t_init *data)
{
	int	left;
	int	right;
	struct timeval now;
	int diff;

	right = philo->num - 1;
	left = philo->num % data->nb_philo;
	if (philo->num % 2 == 0) // les philos pairs prennent la fourchette droite en premier
	{
		pthread_mutex_lock(&data->forks[right]);
		pthread_mutex_lock(&data->printf_mutex);
		gettimeofday(&now, NULL);
		diff = ((now.tv_sec * 1000000 + now.tv_usec) - (data->init_time.tv_sec * 1000000 + data->init_time.tv_usec)) / 1000;
		printf("%d %d has taken a fork\n", diff, philo->num);
		pthread_mutex_unlock(&data->printf_mutex);
		pthread_mutex_lock(&data->forks[left]);
		pthread_mutex_lock(&data->printf_mutex);
		gettimeofday(&now, NULL);
		diff = ((now.tv_sec * 1000000 + now.tv_usec) - (data->init_time.tv_sec * 1000000 + data->init_time.tv_usec)) / 1000;
		printf("%d %d has taken a fork\n", diff, philo->num);
		pthread_mutex_unlock(&data->printf_mutex);
	}
	else // les philos impairs prennent la fourchette gauche en premier
	{
		pthread_mutex_lock(&data->forks[left]);
		pthread_mutex_lock(&data->printf_mutex);
		gettimeofday(&now, NULL);
		diff = ((now.tv_sec * 1000000 + now.tv_usec) - (data->init_time.tv_sec * 1000000 + data->init_time.tv_usec)) / 1000;
		printf("%d %d has taken a fork\n", diff, philo->num);
		pthread_mutex_unlock(&data->printf_mutex);
		pthread_mutex_lock(&data->forks[right]);
		pthread_mutex_lock(&data->printf_mutex);
		gettimeofday(&now, NULL);
		diff = ((now.tv_sec * 1000000 + now.tv_usec) - (data->init_time.tv_sec * 1000000 + data->init_time.tv_usec)) / 1000;
		printf("%d %d has taken a fork\n", diff, philo->num);
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

void	*routine(void *arg)
{
	t_data	*philo;
	t_init	*data;
	struct timeval now;
	int diff;

	philo = (t_data *)arg;
	data = philo->data;
	while (1)
	{
		// debut
		pthread_mutex_lock(&data->flag);
		pthread_mutex_lock(&data->printf_mutex);
		pthread_mutex_unlock(&data->printf_mutex);
		if (data->flag_death == 1)
		{
			// printf("----2.1----\n");
			pthread_mutex_unlock(&data->flag);
			return (NULL);
		}
		pthread_mutex_unlock(&data->flag);
		// fin
		take_forks(philo, data);
		pthread_mutex_lock(&data->printf_mutex);
		gettimeofday(&now, NULL);
		diff = ((now.tv_sec * 1000000 + now.tv_usec) - (data->init_time.tv_sec * 1000000 + data->init_time.tv_usec)) / 1000;
		printf("%d %d is eating\n", diff, philo->num);
		philo->last_meal = now;
		pthread_mutex_unlock(&data->printf_mutex);
		philo->meals--;
		my_usleep(data->time_to_eat);
		give_forks(philo, data);
		// debut
		pthread_mutex_lock(&data->flag);
		pthread_mutex_lock(&data->printf_mutex);
		pthread_mutex_unlock(&data->printf_mutex);
		if (data->flag_death == 1)
		{
			// printf("----2.2----\n");
			pthread_mutex_unlock(&data->flag);
			return (NULL);
		}
		pthread_mutex_unlock(&data->flag);
		// fin
		pthread_mutex_lock(&data->printf_mutex);
		gettimeofday(&now, NULL);
		diff = ((now.tv_sec * 1000000 + now.tv_usec) - (data->init_time.tv_sec * 1000000 + data->init_time.tv_usec)) / 1000;
		printf("%d %d is sleeping\n", diff, philo->num);
		pthread_mutex_unlock(&data->printf_mutex);
		my_usleep(data->time_to_sleep);
		// debut
		pthread_mutex_lock(&data->flag);
		pthread_mutex_lock(&data->printf_mutex);
		pthread_mutex_unlock(&data->printf_mutex);
		if (data->flag_death == 1)
		{
			// printf("----2.3----\n");
			pthread_mutex_unlock(&data->flag);
			return (NULL);
		}
		pthread_mutex_unlock(&data->flag);
		// fin
		pthread_mutex_lock(&data->printf_mutex);
		gettimeofday(&now, NULL);
		diff = ((now.tv_sec * 1000000 + now.tv_usec) - (data->init_time.tv_sec * 1000000 + data->init_time.tv_usec)) / 1000;
		printf("%d %d is thinking\n", diff, philo->num);
		pthread_mutex_unlock(&data->printf_mutex);
	}
	printf("trop mange\n");
	return (NULL);
}
