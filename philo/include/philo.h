/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:51:44 by aducobu           #+#    #+#             */
/*   Updated: 2023/10/12 10:55:05 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data
{
	pthread_t		philo;
	int				num;
	pthread_mutex_t	*forks;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	struct timeval	init_time;
	pthread_mutex_t	printf_mutex;
	int				nb_philo;
	int				meals;
	struct s_data	*next;
}					t_data;

typedef struct s_init
{
	char			**argv;
	int				argc;
	pthread_mutex_t	*forks;
	t_data			*philo;
	struct timeval	init_time;
	pthread_mutex_t	printf_mutex;
}					t_init;

void				free_lst_philo(t_data **philo);
void				destroy_forks(int nb_philo, pthread_mutex_t *forks);

int					ft_atoi(const char *str);
int					parsing(int argc, char **argv, char **env);

t_data				*lst_new(int num, char **argv, t_init *data);
int					lst_add_back(t_data **philo, t_data *new);
int					create_list_philo(t_init *data, char **argv);

void				*routine(void *arg);

void				my_usleep(unsigned int time_to_wait);
#endif