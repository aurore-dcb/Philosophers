/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:05:23 by aducobu           #+#    #+#             */
/*   Updated: 2023/10/12 10:55:41 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

t_data	*lst_new(int num, char **argv, t_init *data)
{
	int		i;
	t_data	*elem;

	i = 0;
	elem = malloc(sizeof(t_data));
	if (!elem)
		return (NULL);
	elem->num = num;
	elem->forks = data->forks;
	elem->time_to_die = ft_atoi(argv[2]);
	elem->time_to_eat = ft_atoi(argv[3]);
	elem->time_to_sleep = ft_atoi(argv[4]);
	elem->init_time = data->init_time;
	elem->printf_mutex = data->printf_mutex;
	elem->nb_philo = ft_atoi(argv[1]);
	if (data->argc == 6)
		elem->meals = ft_atoi(data->argv[5]);
	else
		elem->meals = -2;
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

int	create_list_philo(t_init *data, char **argv)
{
	int i;

	i = 1;
	while (i <= ft_atoi(argv[1]))
	{
		if (!lst_add_back(&data->philo, lst_new(i, argv, data)))
			return (0);
		i++;
	}
	return (1);
}