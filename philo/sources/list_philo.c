/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:05:23 by aducobu           #+#    #+#             */
/*   Updated: 2023/10/09 15:22:03 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

t_data *lst_new(int num)
{
    t_data *elem;
    elem = malloc(sizeof(t_data));
    if (!elem)
        return (NULL);
    elem->next = NULL;
    elem->num = num;
    if (pthread_create(&elem->philo, NULL, &routine, elem))
    {
        perror("Failed to create thread");
        return (NULL);
    }
    return (elem);
}

int lst_add_back(t_data **philo, t_data *new)
{
    t_data *lst;

    if (!new)
        return (0);
    lst = *philo;
    if (lst)
    {
        while (lst->next)
            lst = lst->next;
        lst->next = new;
    }
    else
        *philo = new;
    return (1);
}

int create_list_philo(t_data **philo, int nb_philo)
{
    int i;

    i = 1;
    while (i <= nb_philo)
    {
        if (!lst_add_back(philo, lst_new(i)))
            return (0);        
        i++;
    }
    return (1);
}