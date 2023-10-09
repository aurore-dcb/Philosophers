/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 13:06:10 by aducobu           #+#    #+#             */
/*   Updated: 2023/10/09 15:02:47 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *routine(void *arg)
{
    t_data *elem = (t_data *)arg;

    int num = elem->num;
    printf("Je suis le philo %d\n", num);
    return (NULL);
    
}

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

int main(int argc, char **argv, char **env)
{
    t_data *philo;

    if (!parsing(argc, argv, env))
        return (1);
    if (!create_list_philo(&philo, ft_atoi(argv[1])))
        return (printf("Error while execution\n"), 1);
    t_data *lst;
    lst = philo;
    
    while (lst)
    {
        if (pthread_join(lst->philo, NULL))
        {
            perror("Failed to create thread");
	        return (1); //error
        }
        lst = lst->next;
    }
    t_data *curr;
    lst = philo;
    while (lst)
    {
        curr = lst;
        lst = lst->next;
        free(curr);
    }
    return (0);
}