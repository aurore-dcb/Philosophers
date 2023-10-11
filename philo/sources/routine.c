/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:06:22 by aducobu           #+#    #+#             */
/*   Updated: 2023/10/11 16:31:01 by aducobu          ###   ########.fr       */
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
		printf("tmp - %d - has taken a fork right(%d)\n", philo->num, right); // rajouter le temps
		pthread_mutex_lock(&philo->forks[left]);
		printf("tmp - %d - has taken a fork left(%d)\n", philo->num, left); // rajouter le temps
	}
	else
	{
		pthread_mutex_lock(&philo->forks[left]);
		printf("tmp - %d - has taken a fork left(%d)\n", philo->num, left); // rajouter le temps
		pthread_mutex_lock(&philo->forks[right]);
		printf("tmp - %d - has taken a fork right(%d)\n", philo->num, right); // rajouter le temps
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
	long int		time1;
	long int		time2;
	t_data			*philo;
	struct timeval	init_time;

	philo = (t_data *)arg;
	while (1)
	{
		take_forks(philo);
		gettimeofday(&init_time, NULL);
		time1 = init_time.tv_sec * 1000000 + init_time.tv_sec;
		printf("tmp - %d - is eating\n", philo->num);
		// printf("tmp %ld- %d - is eating\n", time1, philo->num);
		my_usleep(philo->time_to_eat);
		gettimeofday(&init_time, NULL);
		time2 = init_time.tv_sec * 1000000 + init_time.tv_sec;
		// printf("tmp %ld- %d - is sleeping\n", time2, philo->num);
		printf("diff philo %d = %ld\n", philo->num, (time2  - time1) / 1000);
		give_forks(philo);
		printf("tmp - %d - is sleeping\n", philo->num);
		my_usleep(philo->time_to_sleep);
	}
	return (NULL);
}
