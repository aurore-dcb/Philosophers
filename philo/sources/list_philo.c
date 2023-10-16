/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:05:23 by aducobu           #+#    #+#             */
/*   Updated: 2023/10/16 14:55:02 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

t_data	*lst_new(int num, t_init *data)
{
	t_data	*elem;

	elem = malloc(sizeof(t_data));
	if (!elem)
		return (NULL);
	elem->data = data;
	elem->num = num;
	pthread_mutex_lock(&data->eat_mutex);
	if (data->argc == 6)
		elem->meals = ft_atoi(data->argv[5]);
	else
		elem->meals = -2;
	elem->last_meal = data->init_time;
	pthread_mutex_unlock(&data->eat_mutex);
	elem->data = data;
	elem->next = NULL;
	if (pthread_create(&elem->philo, NULL, &routine, elem))
	{
		perror("Failed to create thread");
		return (NULL);
	}
	return (elem);
}

int	lst_add_back(t_data **philo, t_data *new)
{
	t_data	*lst;

	if (!new)
		return (0);
	lst = *philo;
	if (lst)
	{
		while (lst->next)
			lst = lst->next;
		lst->next = new;
	}
	else
		*philo = new;
	return (1);
}

int	create_list_philo(t_init *data, t_data **philo)
{
	int	i;

	i = 1;
	while (i <= data->nb_philo)
	{
		pthread_mutex_lock(&data->printf_mutex);
		printf("THHHREEEEEEEEEADDDD\n");
		pthread_mutex_unlock(&data->printf_mutex);
		if (!lst_add_back(philo, lst_new(i, data)))
			return (free_lst_philo(philo, i), 0);
		i++;
	}
	return (1);
}

void	free_lst_philo(t_data **philo, int i)
{
	t_data	*curr;

	curr = *philo;
	if (!curr)
		return ;
	while (i > 0)
	{
		curr = *philo;
		*philo = (*philo)->next;
		free(curr);
		i--;
	}
}
