/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 10:05:38 by aducobu           #+#    #+#             */
/*   Updated: 2023/10/16 10:15:03 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	take_forks(t_data *philo, t_init *data)
{
	int	left;
	int	right;

	if (ft_check_flag(data))
		return (1);
	right = philo->num - 1;
	left = philo->num % data->nb_philo;
	if (philo->num % 2 == 0)
	{
		pthread_mutex_lock(&data->forks[right]);
		ft_print(data, philo, 1);
		pthread_mutex_lock(&data->forks[left]);
		ft_print(data, philo, 1);
	}
	else
	{
		pthread_mutex_lock(&data->forks[left]);
		ft_print(data, philo, 1);
		pthread_mutex_lock(&data->forks[right]);
		ft_print(data, philo, 1);
	}
	return (0);
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

pthread_mutex_t	*create_forks(int nb_philo)
{
	int				i;
	pthread_mutex_t	*forks;

	i = 0;
	forks = malloc(sizeof(pthread_mutex_t) * nb_philo);
	if (!forks)
		return (NULL);
	while (i < nb_philo)
	{
		if (pthread_mutex_init(&forks[i], NULL))
			return (NULL);
		i++;
	}
	return (forks);
}

void	destroy_forks(int nb_philo, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < nb_philo)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	free(forks);
}
