/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 13:06:10 by aducobu           #+#    #+#             */
/*   Updated: 2023/10/11 15:57:33 by aducobu          ###   ########.fr       */
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

int	main(int argc, char **argv, char **env)
{
	t_data			*philo;
	pthread_mutex_t	*forks;
	int				time =  0;

	philo = NULL;
	forks = NULL;
	if (!parsing(argc, argv, env))
		return (1);
	// creation du tableau de mutex = les fourchettes
	forks = create_forks(ft_atoi(argv[1]));
	// pthread_mutex_lock(&forks[1]);
	// creation des threads = philos
	if (!create_list_philo(&philo, argv, forks, time))
		return (printf("Error while execution\n"), 1);
	if (!ft_wait(&philo))
		return (1);
	// pthread_mutex_unlock(&forks[1]);
	destroy_forks(ft_atoi(argv[1]), forks);
	free_lst_philo(&philo);
	return (0);
}
