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

void	thread_counter(t_philo	*philo)
{
	pthread_mutex_lock(&(philo -> data -> count_mutex));
	philo -> data -> sync_count++;
	pthread_mutex_unlock(&(philo -> data -> count_mutex));
}

void	wait_thread_sync(t_philo *philo)
{
	int	flag;

	flag = 0;
	while (1)
	{
		pthread_mutex_lock(&(philo -> data -> count_mutex));
		if (philo -> data -> sync_count == -1)
			flag = 1;
		pthread_mutex_unlock(&(philo ->data -> count_mutex));
		if (flag == 1)
			break ;
	}
}
