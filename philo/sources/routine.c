/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:06:22 by aducobu           #+#    #+#             */
/*   Updated: 2023/10/19 13:23:38 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_unlock(t_philo *philo, t_data *data)
{
	pthread_mutex_unlock(&data->forks[philo->fork_r]);
	pthread_mutex_unlock(&data->forks[philo->fork_l]);
}

void	ft_print(t_data *data, t_philo *philo, char *act)
{
	struct timeval	now;
	int				diff;

	pthread_mutex_lock(&data->flag_mutex);
	if (data->flag_death == 1)
	{
		pthread_mutex_unlock(&data->flag_mutex);
		return ;
	}
	gettimeofday(&now, NULL);
	diff = ((now.tv_sec * 1000000 + now.tv_usec) - (data->init_time.tv_sec
				* 1000000 + data->init_time.tv_usec)) / 1000;
	pthread_mutex_lock(&data->printf_mutex);
	printf("%d %d %s\n", diff, philo->num, act);
	pthread_mutex_unlock(&data->printf_mutex);
	pthread_mutex_unlock(&data->flag_mutex);
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

int eating(t_philo *philo)
{
	if (take_forks(philo, philo->data))
		return (0);
	ft_print(philo->data, philo, "is eating");
	pthread_mutex_lock(&philo->eat_mutex);
	gettimeofday(&philo->last_meal, NULL);
	philo->meals--;
	pthread_mutex_unlock(&philo->eat_mutex);
	my_usleep(philo->data->time_to_eat);
	give_forks(philo, philo->data);
	return (1);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	
	philo = (t_philo *)arg;
	while (1)
	{
		if (!eating(philo))
			break;
		ft_print(philo->data, philo, "is sleeping");
		my_usleep(philo->data->time_to_sleep);
		if (ft_check_flag(philo->data))
			return (NULL);
		ft_print(philo->data, philo, "is thinking");
		my_usleep(((philo->data->time_to_die - \
			(philo->data->time_to_eat + philo->data->time_to_sleep)) / 2));
	}
	return (NULL);
}
