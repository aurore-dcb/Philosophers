/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 13:06:10 by aducobu           #+#    #+#             */
/*   Updated: 2023/10/20 13:16:33 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (!parsing(argc, argv, &data))
	{
		printf("Error parsing : wrong argument(s)\n");
		printf("You need to put 5 of 6 positive numbers (integer) as arguments\n");
		return (1);
	}
	init_philo_mutex(&data);
	free_all(&data);
	return (0);
}
