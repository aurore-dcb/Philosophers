/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:06:22 by aducobu           #+#    #+#             */
/*   Updated: 2023/10/15 10:56:14 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	take_forks(t_data *philo, t_init *data)
{
	int	left;
	int	right;

	right = philo->num - 1;
	left = philo->num % data->nb_philo;
	if (philo->num % 2 == 0) // les philos pairs prennent la fourchette droite en premier
	{
		pthread_mutex_lock(&data->forks[right]);
		pthread_mutex_lock(&data->printf_mutex);
		printf("tmp - %d - has taken a fork right(%d)\n", philo->num, right);
			// rajouter le temps
		pthread_mutex_unlock(&data->printf_mutex);
		pthread_mutex_lock(&data->forks[left]);
		pthread_mutex_lock(&data->printf_mutex);
		printf("tmp - %d - has taken a fork left(%d)\n", philo->num, left);
			// rajouter le temps
		pthread_mutex_unlock(&data->printf_mutex);
	}
	else // les philos impairs prennent la fourchette gauche en premier
	{
		pthread_mutex_lock(&data->forks[left]);
		pthread_mutex_lock(&data->printf_mutex);
		printf("tmp - %d - has taken a fork left(%d)\n", philo->num, left);
			// rajouter le temps
		pthread_mutex_unlock(&data->printf_mutex);
		pthread_mutex_lock(&data->forks[right]);
		pthread_mutex_lock(&data->printf_mutex);
		printf("tmp - %d - has taken a fork right(%d)\n", philo->num, right);
			// rajouter le temps
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

	philo = (t_data *)arg;
	data = philo->data;
	while (philo->meals != 0)
	{
		take_forks(philo, data);
		pthread_mutex_lock(&data->printf_mutex);
		printf("tmp - %d - is eating\n", philo->num);
		pthread_mutex_unlock(&data->printf_mutex);
		philo->meals--;
		my_usleep(data->time_to_eat);
		give_forks(philo, data);
		pthread_mutex_lock(&data->printf_mutex);
		printf("tmp - %d - is sleeping\n", philo->num);
		pthread_mutex_unlock(&data->printf_mutex);
		my_usleep(data->time_to_sleep);
		pthread_mutex_lock(&data->printf_mutex);
		printf("tmp - %d - is thinking\n", philo->num);
		pthread_mutex_unlock(&data->printf_mutex);
	}
	return (NULL);
}
