/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 13:06:10 by aducobu           #+#    #+#             */
/*   Updated: 2023/10/10 09:51:26 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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


pthread_mutex_t *create_forks(int nb_philo)
{
	int i;
	pthread_mutex_t *forks;

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

int	main(int argc, char **argv, char **env)
{
	t_data	*philo;
	pthread_mutex_t *forks;

    philo = NULL;
	forks = NULL;
	if (!parsing(argc, argv, env))
		return (1);
    // creation du tableau de mutex = les fourchettes
	forks = create_forks(ft_atoi(argv[1]));
	if (!create_list_philo(&philo, ft_atoi(argv[1])))
		return (printf("Error while execution\n"), 1);
	if (!ft_wait(&philo))
		return (1);
	destroy_forks(ft_atoi(argv[1]), forks);
	free_lst_philo(&philo);
	return (0);
}
