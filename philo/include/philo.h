/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:51:44 by aducobu           #+#    #+#             */
/*   Updated: 2023/10/18 15:41:23 by aducobu          ###   ########.fr       */
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

typedef struct s_philo
{
	pthread_t		id;
	int				num;
	int				meals;
	struct timeval	last_meal;
	int				fork_l;
	int				fork_r;
	pthread_mutex_t	eat_mutex;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	int				argc;
	char			**argv;
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	struct timeval	init_time;
	pthread_mutex_t	*forks;
	t_philo			*philo;
	pthread_mutex_t	printf_mutex;
	pthread_mutex_t	flag_mutex;
	pthread_mutex_t	eat_mutex;
	int				flag_death;
}					t_data;

// main
void				init_data(t_data *data, char **argv, int argc);
int					init_philo_mutex(t_data *data);
int					lauch_threads(t_data *data);
void				free_all(t_data *data);
// routine
void				ft_unlock(t_philo *philo, t_data *data);
int					ft_print(t_data *data, t_philo *philo, int act);
long int			get_actual_time(void);
int					ft_check_flag(t_data *data);
void				*routine(void *arg);
// forks
void				give_forks(t_philo *philo, t_data *data);
int					take_forks(t_philo *philo, t_data *data);
// monitor
int					check_meals(t_data *data, t_philo *philo);
int					check_death(t_data *data, t_philo *philo);
void				*monitor(void *arg);
void				my_usleep(unsigned int time_to_wait);
// parsing
int					ft_atoi(const char *str);
int					parsing(int argc, char **argv);

#endif