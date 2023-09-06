/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akazuki <akazuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 14:23:13 by akazuki           #+#    #+#             */
/*   Updated: 2023/09/06 14:27:37 by akazuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_fork_array(t_fork *fork, int philo_size)
{
	int	i;

	i = 0;
	while (i < philo_size)
	{
		if (pthread_mutex_init(&(fork[i].mutex), NULL) != 0)
			return (1);
		if (i % 2 == 0)
			fork[i].prev_philo = i + 2;
		else
			fork[i].prev_philo = i + 1;
		i++;
	}
	return (0);
}

int	init_common_data_mutex(t_data *data)
{
	if (pthread_mutex_init(&(data -> count_mutex), NULL) != 0)
		return (1);
	if (pthread_mutex_init(&(data -> check_die_mutex), NULL) != 0)
		return (1);
	return (0);
}

int	init_philo_mutex(t_philo *philo_array)
{
	int	i;
	int	count;

	i = 0;
	count = philo_array -> data -> input -> philo_size;
	while (i < count)
	{
		if (pthread_mutex_init(&(philo_array[i].eat_mutex), NULL) != 0)
			return (1);
		if (pthread_mutex_init(&(philo_array[i].time_mutex), NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}
