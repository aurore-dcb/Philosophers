/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:06:22 by aducobu           #+#    #+#             */
/*   Updated: 2023/10/12 11:02:55 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	take_forks(t_data *philo)
{
	int left;
	int right;
	
	left = philo->num % philo->nb_philo;
	right = philo->num - 1;
	if (philo->num % 2 == 0)
	{
		pthread_mutex_lock(&philo->forks[right]);
		pthread_mutex_lock(&philo->printf_mutex);
		printf("tmp - %d - has taken a fork right(%d)\n", philo->num, right); // rajouter le temps
		pthread_mutex_unlock(&philo->printf_mutex);
		pthread_mutex_lock(&philo->forks[left]);
		pthread_mutex_lock(&philo->printf_mutex);
		printf("tmp - %d - has taken a fork left(%d)\n", philo->num, left); // rajouter le temps
		pthread_mutex_unlock(&philo->printf_mutex);
	}
	else
	{
		pthread_mutex_lock(&philo->forks[left]);
		pthread_mutex_lock(&philo->printf_mutex);
		printf("tmp - %d - has taken a fork left(%d)\n", philo->num, left); // rajouter le temps
		pthread_mutex_unlock(&philo->printf_mutex);
		pthread_mutex_lock(&philo->forks[right]);
		pthread_mutex_lock(&philo->printf_mutex);
		printf("tmp - %d - has taken a fork right(%d)\n", philo->num, right); // rajouter le temps
		pthread_mutex_unlock(&philo->printf_mutex);
	}
}

void	give_forks(t_data *philo)
{
	int left;
	int right;
	
	left = philo->num % philo->nb_philo;
	right = philo->num - 1;
	if (philo->num % 2 == 0)
	{
		pthread_mutex_unlock(&philo->forks[right]);
		pthread_mutex_unlock(&philo->forks[left]);
	}
	else
	{
		pthread_mutex_unlock(&philo->forks[left]);
		pthread_mutex_unlock(&philo->forks[right]);
	}
}

void	*routine(void *arg)
{
	t_data			*philo;

	philo = (t_data *)arg;
	while (philo->meals != 0)
	{
		take_forks(philo);
		pthread_mutex_lock(&philo->printf_mutex);
		printf("tmp - %d - is eating\n", philo->num);
		pthread_mutex_unlock(&philo->printf_mutex);
		philo->meals--;
		my_usleep(philo->time_to_eat);
		give_forks(philo);
		pthread_mutex_lock(&philo->printf_mutex);
		printf("tmp - %d - is sleeping\n", philo->num);
		pthread_mutex_unlock(&philo->printf_mutex);
		my_usleep(philo->time_to_sleep);
	}
	return (NULL);
}
