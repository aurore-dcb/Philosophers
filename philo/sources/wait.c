/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 10:10:38 by aducobu           #+#    #+#             */
/*   Updated: 2023/10/16 10:15:49 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_wait(t_data **philo, pthread_t monitor)
{
	t_data	*lst;

	lst = *philo;
	while (lst)
	{
		if (pthread_join(lst->philo, NULL))
		{
			perror("Failed to join thread");
			return (0);
		}
		lst = lst->next;
	}
	if (pthread_join(monitor, NULL))
	{
		perror("Failed to join thread");
		return (0);
	}
	pthread_mutex_destroy(&(*philo)->data->flag);
	return (1);
}

void	my_usleep(unsigned int time_to_wait)
{
	struct timeval		current_time;
	struct timeval		time;
	unsigned long long	start_time;

	gettimeofday(&time, NULL);
	start_time = time.tv_sec * 1000000 + time.tv_usec;
	while (1)
	{
		gettimeofday(&current_time, NULL);
		if ((current_time.tv_sec * 1000000 + current_time.tv_usec)
			- start_time >= time_to_wait * 1000)
			break ;
	}
}
