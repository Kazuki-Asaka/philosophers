/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_mutex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akazuki <akazuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 17:23:05 by akazuki           #+#    #+#             */
/*   Updated: 2023/09/07 17:56:51 by akazuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	destroy_mutex_fork(t_fork *fork, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		pthread_mutex_destroy(&(fork[i].mutex));
		i++;
	}
}

void	destroy_mutex_eat(t_philo *philo, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		pthread_mutex_destroy(&(philo[i].eat_mutex));
		i++;
	}
}

void	destroy_mutex_time(t_philo *philo, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		pthread_mutex_destroy(&(philo[i].time_mutex));
		i++;
	}
}

void	destroy_all_mutex(t_philo *philo_array)
{
	int	size;

	size = philo_array -> data -> input -> philo_size;
	destroy_mutex_fork(philo_array -> data -> fork, size);
	pthread_mutex_destroy(&(philo_array -> data -> check_die_mutex));
	pthread_mutex_destroy(&(philo_array -> data -> count_mutex));
	destroy_mutex_time(philo_array, size);
	destroy_mutex_eat(philo_array, size);
}
