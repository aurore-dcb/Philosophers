/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:51:44 by aducobu           #+#    #+#             */
/*   Updated: 2023/10/10 09:56:11 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_data
{
	pthread_t		philo;
	int				num;
	struct s_data	*next;
}					t_data;

void				free_lst_philo(t_data **philo);
void				destroy_forks(int nb_philo, pthread_mutex_t *forks);

int					ft_atoi(const char *str);
int					parsing(int argc, char **argv, char **env);

t_data				*lst_new(int num);
int					lst_add_back(t_data **philo, t_data *new);
int					create_list_philo(t_data **philo, int nb_philo);

void				*routine(void *arg);

#endif