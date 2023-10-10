/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:06:22 by aducobu           #+#    #+#             */
/*   Updated: 2023/10/10 12:59:18 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void *routine(void *arg)
{
    int i;
    int k;
    int result;
    t_data *elem = (t_data *)arg;

    int num = elem->num;
    // printf("Je suis le philo %d\n", num);
    if (num % 2 == 0)// philo pair
        i = num - 1;
    else // philo impair
        i = num % elem->nb_philo;
    result = pthread_mutex_lock(&elem->forks[i]);
    if (result == 0) {
        printf("Je suis le philo %d - J'ai pris la fourchette %d\n", num, i);
        pthread_mutex_unlock(&elem->forks[i]);
    } else {
        printf("Impossible de verrouiller le mutex dans le maillon %d\n", num);
    }
    if (num % 2 == 0)// philo pair
        k = num % elem->nb_philo;
    else // philo impair
        k = num - 1;
    if (result == 0) {
        printf("Je suis le philo %d - J'ai pris la fourchette %d\n", num, k);
        pthread_mutex_unlock(&elem->forks[k]);
    } else {
        printf("Impossible de verrouiller le mutex dans le maillon %d\n", num);
    }
    //manger avant de relacher les deux fourchettes
    
    pthread_mutex_unlock(&elem->forks[i]);
    pthread_mutex_unlock(&elem->forks[k]);
    return (NULL);
    
}
