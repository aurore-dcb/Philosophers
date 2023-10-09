/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 13:06:10 by aducobu           #+#    #+#             */
/*   Updated: 2023/10/09 15:40:32 by aducobu          ###   ########.fr       */
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
		free(curr);
	}
}

int	ft_wait(t_data **philo)
{
	t_data	*lst;

	lst = *philo;
	while (lst)
	{
		if (pthread_join(lst->philo, NULL))
		{
			perror("Failed to create thread");
			return (0);
		}
		lst = lst->next;
	}
	return (1);
}

int	main(int argc, char **argv, char **env)
{
	t_data	*philo;

    philo = NULL;
	if (!parsing(argc, argv, env))
		return (1);
	if (!create_list_philo(&philo, ft_atoi(argv[1])))
		return (printf("Error while execution\n"), 1);
	if (!ft_wait(&philo))
		return (1);
	free_lst_philo(&philo);
	return (0);
}
