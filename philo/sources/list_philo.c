/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:05:23 by aducobu           #+#    #+#             */
/*   Updated: 2023/10/10 11:31:39 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

t_data	*lst_new(int num, char **argv, pthread_mutex_t *forks)
{
	int		i;
	t_data	*elem;

	i = 0;
	elem = malloc(sizeof(t_data));
	if (!elem)
		return (NULL);
	elem->next = NULL;
	elem->num = num;
	elem->nb_philo = ft_atoi(argv[1]);
	elem->time_to_die = ft_atoi(argv[2]);
	elem->time_to_eat = ft_atoi(argv[3]);
	elem->time_to_sleep = ft_atoi(argv[4]);
	elem->forks = malloc(sizeof(pthread_mutex_t) * elem->nb_philo);
	if (!elem->forks)
		return (NULL);
	elem->forks = forks;
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

int	create_list_philo(t_data **philo, char **argv, pthread_mutex_t *forks)
{
	int i;

	i = 1;
	while (i <= ft_atoi(argv[1]))
	{
		if (!lst_add_back(philo, lst_new(i, argv, forks)))
			return (0);
		i++;
	}
	return (1);
}