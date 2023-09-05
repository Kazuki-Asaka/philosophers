/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleeping.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akazuki <akazuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 20:34:49 by akazuki           #+#    #+#             */
/*   Updated: 2023/09/05 20:34:49 by akazuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	falling_asleep(t_philo *philo)
{
	if (philo -> philo_number % 2 == 1)
	{
		pthread_mutex_unlock(&(philo -> left_hund -> mutex));
		pthread_mutex_unlock(&(philo -> right_hund -> mutex));
	}
	else
	{
		pthread_mutex_unlock(&(philo -> right_hund -> mutex));
		pthread_mutex_unlock(&(philo -> left_hund -> mutex));
	}
	philo -> right_hund_status = 0;
	philo -> left_hund_status = 0;
	if (check_die_flag_print(philo, SLEEP) != 1)
		stop_watch(philo, philo -> data -> input -> time_to_sleep);
}
