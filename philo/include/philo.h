/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:51:44 by aducobu           #+#    #+#             */
/*   Updated: 2023/10/16 10:20:24 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_init
{
	int				argc;
	char			**argv;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	struct timeval	init_time;
	int				nb_philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	printf_mutex;
	pthread_mutex_t	flag;
	int				flag_death;
}					t_init;

typedef struct s_data
{
	pthread_t		philo;
	int				num;
	int				meals;
	struct timeval	last_meal;
	t_init			*data;
	struct s_data	*next;
}					t_data;

int					ft_atoi(const char *str);
int					parsing(int argc, char **argv);
int					take_forks(t_data *philo, t_init *data);
void				give_forks(t_data *philo, t_init *data);
pthread_mutex_t		*create_forks(int nb_philo);
void				destroy_forks(int nb_philo, pthread_mutex_t *forks);
int					ft_wait(t_data **philo, pthread_t monitor);
void				my_usleep(unsigned int time_to_wait);
int					ft_print(t_init *data, t_data *philo, int act);
int					ft_check_flag(t_init *data);
void				*routine(void *arg);
int					check_meals(t_data *philo);
int					check_death(t_data *philo);
void				*death_monitor(void *arg);
int					create_monitor(t_data **philo, pthread_t *monitor);
t_data				*lst_new(int num, t_init *data);
int					lst_add_back(t_data **philo, t_data *new);
int					create_list_philo(t_init *data, t_data **philo);
void				free_lst_philo(t_data **philo);

#endif