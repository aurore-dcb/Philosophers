/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:51:44 by aducobu           #+#    #+#             */
/*   Updated: 2023/10/12 15:14:26 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_init
{
	char			**argv;
	int				argc;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	struct timeval	init_time;
	pthread_mutex_t	printf_mutex;
	int				nb_philo;
	pthread_mutex_t	*forks;
	// t_data			*philo;
}					t_init;

typedef struct s_data
{
	pthread_t		philo;
	int				num;
	struct timeval	last_meal;
	int				meals;
	pthread_mutex_t	*forks;
	t_init			*data;
	struct s_data	*next;
}					t_data;

void				free_lst_philo(t_data **philo);
void				destroy_forks(int nb_philo, pthread_mutex_t *forks);

int					ft_atoi(const char *str);
int					parsing(int argc, char **argv, char **env);

t_data				*lst_new(int num, t_data *philo);
int					lst_add_back(t_data **philo, t_data *new);
int					create_list_philo(t_init *data, char **argv);

void				*routine(void *arg);

void				my_usleep(unsigned int time_to_wait);

long int			get_actual_time(void);
#endif