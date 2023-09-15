/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync_barrier.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akazuki <akazuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 20:32:08 by akazuki           #+#    #+#             */
/*   Updated: 2023/09/05 20:32:08 by akazuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	check_mutex_count(t_philo *philosophers)
{
	int				flag;
	int				size;
	struct timeval	time;

	flag = 0;
	size = philosophers -> data -> input -> philo_size;
	while (1)
	{
		pthread_mutex_lock(&(philosophers -> data -> count_mutex));
		if (philosophers -> data -> sync_count == size)
		{
			gettimeofday(&philosophers -> data -> start_time, NULL);
			time = philosophers -> data -> start_time;
			set_init_last_eat_time(philosophers, time);
			philosophers -> data -> sync_count = -1;
			flag = 1;
		}
		pthread_mutex_unlock(&(philosophers -> data -> count_mutex));
		if (flag == 1)
			break ;
	}
}

void	set_init_last_eat_time(t_philo *philosophers, struct timeval time)
{
	int	i;
	int	count;

	i = 0;
	count = philosophers -> data -> input -> philo_size;
	while (i < count)
	{
		philosophers[i].last_eat_time = time;
		i ++;
	}
}

void	thread_counter(t_philo	*philo)
{
	pthread_mutex_lock(&(philo -> data -> count_mutex));
	philo -> data -> sync_count++;
	pthread_mutex_unlock(&(philo -> data -> count_mutex));
}

void	not_start_eat(t_philo *philosophers)
{
	pthread_mutex_lock(&(philosophers -> data -> count_mutex));
		philosophers -> data -> sync_count = -2;
	pthread_mutex_lock(&(philosophers -> data -> count_mutex));
}

int	wait_thread_sync(t_philo *philo)
{
	int	flag;

	flag = 0;
	while (1)
	{
		pthread_mutex_lock(&(philo -> data -> count_mutex));
		if (philo -> data -> sync_count == -1
			|| philo -> data -> sync_count == -2)
			flag = philo -> data -> sync_count;
		pthread_mutex_unlock(&(philo ->data -> count_mutex));
		if (flag == -1 || flag == -2)
			break ;
	}
	return (flag);
}
