/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 13:06:10 by aducobu           #+#    #+#             */
/*   Updated: 2023/10/16 15:05:17 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	init_main(t_init *all, char **argv, int argc)
{
	all->argv = argv;
	all->argc = argc;
	all->time_to_die = ft_atoi(argv[2]);
	all->time_to_eat = ft_atoi(argv[3]);
	all->time_to_sleep = ft_atoi(argv[4]);
	gettimeofday(&all->init_time, NULL);
	all->nb_philo = ft_atoi(argv[1]);
	all->forks = create_forks(ft_atoi(argv[1]));
	pthread_mutex_init(&all->printf_mutex, NULL);
	pthread_mutex_init(&all->flag_mutex, NULL);
	pthread_mutex_init(&all->eat_mutex, NULL);
	all->flag_death = 0;
}

void	ft_quit(t_init *all, t_data **philo)
{
	destroy_forks(ft_atoi(all->argv[1]), all->forks);
	pthread_mutex_destroy(&(*philo)->data->flag_mutex);
	pthread_mutex_destroy(&(*philo)->data->printf_mutex);
	pthread_mutex_destroy(&(*philo)->data->eat_mutex);
	if (philo)
		free_lst_philo(philo, ft_atoi(all->argv[1]));
}

int	main(int argc, char **argv, char **env)
{
	t_init		all;
	t_data		*philo;
	pthread_t	monitor;

	(void)env;
	memset(&all, 0, sizeof(t_init));
	philo = NULL;
	if (!parsing(argc, argv))
		return (1);
	init_main(&all, argv, argc);
	if (!create_list_philo(&all, &philo))
		return (printf("Error\n"), ft_quit(&all, &philo), 1);
	if (!create_monitor(&philo, &monitor) || !ft_wait(&philo, monitor))
	{
		ft_quit(&all, &philo);
		return (printf("Error\n"), 1);
	}
	ft_quit(&all, &philo);
	return (0);
}
