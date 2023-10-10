/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 09:22:55 by aducobu           #+#    #+#             */
/*   Updated: 2023/10/10 11:19:56 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	free_lst_philo(t_data **philo)
{
	t_data	*curr;

	curr = *philo;
	while (*philo)
	{
		curr = *philo;
		*philo = (*philo)->next;
		// destroy_forks(curr->nb_philo, curr->forks);
		free(curr);
	}
}

void destroy_forks(int nb_philo, pthread_mutex_t *forks)
{
	int i;

	i = 0;
	while (i < nb_philo)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	free(forks);
}

