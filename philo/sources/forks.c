/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 10:05:38 by aducobu           #+#    #+#             */
/*   Updated: 2023/10/20 16:52:45 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	take_forks(t_philo *philo, t_data *data)
{
	if (philo->num % 2 == 0)
		pthread_mutex_lock(&data->forks[philo->fork_r]);
	else
		pthread_mutex_lock(&data->forks[philo->fork_l]);
	ft_print(data, philo, "has taken a fork");
	if (philo->fork_r == philo->fork_l)
		return (pthread_mutex_unlock(&data->forks[philo->fork_r]), 1);
	if (philo->num % 2 == 0)
		pthread_mutex_lock(&data->forks[philo->fork_l]);
	else
		pthread_mutex_lock(&data->forks[philo->fork_r]);
	ft_print(data, philo, "has taken a fork");
	return (0);
}

void	give_forks(t_philo *philo, t_data *data)
{
	if (philo->num % 2 == 0)
	{
		pthread_mutex_unlock(&data->forks[philo->fork_r]);
		pthread_mutex_unlock(&data->forks[philo->fork_l]);
	}
	else
	{
		pthread_mutex_unlock(&data->forks[philo->fork_l]);
		pthread_mutex_unlock(&data->forks[philo->fork_r]);
	}
}

int	eating(t_philo *philo)
{
	if (take_forks(philo, philo->data))
		return (1);
	ft_print(philo->data, philo, "is eating");
	pthread_mutex_lock(&philo->eat_mutex);
	philo->last_meal = get_actual_time();
	philo->meals++;
	pthread_mutex_unlock(&philo->eat_mutex);
	my_usleep(philo->data->time_to_eat);
	give_forks(philo, philo->data);
	return (0);
}
