/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:51:44 by aducobu           #+#    #+#             */
/*   Updated: 2023/10/15 10:57:15 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <string.h>

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

void				free_lst_philo(t_data **philo);
void				destroy_forks(int nb_philo, pthread_mutex_t *forks);

int					ft_atoi(const char *str);
int					parsing(int argc, char **argv, char **env);

t_data				*lst_new(int num, t_init *data);
int					lst_add_back(t_data **philo, t_data *new);
int					create_list_philo(t_init *data, t_data **philo);

void				*routine(void *arg);

void				my_usleep(unsigned int time_to_wait);
#endif