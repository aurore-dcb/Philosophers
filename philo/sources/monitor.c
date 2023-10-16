/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 09:40:11 by aducobu           #+#    #+#             */
/*   Updated: 2023/10/16 10:19:12 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	check_meals(t_data *philo)
{
	if (philo->meals == 0)
	{
		pthread_mutex_lock(&philo->data->flag);
		philo->data->flag_death = 1;
		pthread_mutex_unlock(&philo->data->flag);
		return (1);
	}
	return (0);
}

int	check_death(t_data *philo)
{
	struct timeval	now;
	int				diff;

	gettimeofday(&now, NULL);
	diff = ((now.tv_sec * 1000000 + now.tv_usec) - (philo->last_meal.tv_sec
				* 1000000 + philo->last_meal.tv_usec)) / 1000;
	if (diff >= philo->data->time_to_die)
	{
		ft_print(philo->data, philo, 5);
		pthread_mutex_lock(&philo->data->flag);
		philo->data->flag_death = 1;
		pthread_mutex_unlock(&philo->data->flag);
		return (1);
	}
	return (0);
}

void	*death_monitor(void *arg)
{
	t_data	*curr;
	t_data	*beg;

	beg = (t_data *)arg;
	curr = beg;
	while (1)
	{
		curr = beg;
		while (curr)
		{
			if (check_meals(curr))
				return (NULL);
			if (check_death(curr))
				return (NULL);
			curr = curr->next;
		}
		my_usleep(5);
	}
	return (NULL);
}

int	create_monitor(t_data **philo, pthread_t *monitor)
{
	if (pthread_create(monitor, NULL, &death_monitor, *philo))
	{
		perror("Failed to create thread");
		return (0);
	}
	return (1);
}
