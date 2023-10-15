/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 13:06:10 by aducobu           #+#    #+#             */
/*   Updated: 2023/10/15 16:42:31 by aducobu          ###   ########.fr       */
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

void	init_main(t_init *all, char **argv, int argc)
{
	all->argv = argv;
	all->argc = argc;
	all->time_to_die = ft_atoi(argv[2]);
	all->time_to_eat = ft_atoi(argv[3]);
	all->time_to_sleep = ft_atoi(argv[4]);
	gettimeofday(&all->init_time, NULL);
	all->nb_philo = ft_atoi(argv[1]);
	// creation du tableau de mutex = les fourchettes
	all->forks = create_forks(ft_atoi(argv[1]));
	// creation du mutex pour printf
	pthread_mutex_init(&all->printf_mutex, NULL);
	all->flag_death = 0;
}

void	*death_monitor(void *arg)
{
	t_data			*curr;
	t_data			*beg;
	struct timeval	now;
	int				diff;

	beg = (t_data *)arg;
	curr = beg;
	while (1)
	{
		// tourner en boucle sur les philos
		curr = beg;
		while (curr)
		{
			gettimeofday(&now, NULL);
			diff = ((now.tv_sec * 1000000 + now.tv_usec)
					- (curr->last_meal.tv_sec * 1000000
						+ curr->last_meal.tv_usec)) / 1000;
			// pthread_mutex_lock(&curr->data->printf_mutex);
			// printf("meals = %d\n", curr->meals);
			// pthread_mutex_unlock(&curr->data->printf_mutex);
			if (curr->meals == 0)
			{
				pthread_mutex_lock(&curr->data->flag);
				curr->data->flag_death = 1;
				pthread_mutex_unlock(&curr->data->flag);
				pthread_mutex_lock(&curr->data->printf_mutex);
				printf("ASSEZ MANGER\n");
				pthread_mutex_unlock(&curr->data->printf_mutex);
				return (NULL);
			}
			if (diff >= curr->data->time_to_die)
			{
				// afficher la mort
				diff = ((now.tv_sec * 1000000 + now.tv_usec) - (curr->data->init_time.tv_sec * 1000000 + curr->data->init_time.tv_usec)) / 1000;
				pthread_mutex_lock(&curr->data->printf_mutex);
				printf("%d %d died\n", diff, curr->num);
				pthread_mutex_unlock(&curr->data->printf_mutex);
				// mettre le flag a 1
				pthread_mutex_lock(&curr->data->flag);
				curr->data->flag_death = 1;
				pthread_mutex_unlock(&curr->data->flag);
				pthread_mutex_lock(&curr->data->printf_mutex);
				printf("MORT\n");
				pthread_mutex_unlock(&curr->data->printf_mutex);
				return (NULL);
			}
			curr = curr->next;
		}
		my_usleep(10);
	}
	return (NULL);
}

int	create_monitor(t_data **philo, pthread_t *monitor)
{
	if (pthread_create(monitor, NULL, &death_monitor, *philo))
	{
		// printf("philo mort");
		// ft_wait(philo, *monitor);
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv, char **env)
{
	t_init		all;
	t_data		*philo;
	pthread_t	monitor;

	memset(&all, 0, sizeof(t_init));
	philo = NULL;
	if (!parsing(argc, argv, env))
		return (1);
	init_main(&all, argv, argc);
	// creation des threads = philos
	if (!create_list_philo(&all, &philo))
		return (printf("Error while execution\n"), 1);
	if (!create_monitor(&philo, &monitor))
		return (0);
	if (!ft_wait(&philo, monitor))
		return (1);
	destroy_forks(ft_atoi(argv[1]), all.forks);
	free_lst_philo(&philo);
	return (0);
}
