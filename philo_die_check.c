/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_die_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akazuki <akazuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 19:48:10 by akazuki           #+#    #+#             */
/*   Updated: 2023/09/05 19:48:10 by akazuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_msg(t_philo *philo, char *msg)
{
	struct timeval	time;

	
	gettimeofday(&time, NULL);
	if (strcmp(msg, EAT) == 0)
	{
		pthread_mutex_lock(&(philo -> eat_mutex));
		philo -> eat_count++;
		pthread_mutex_unlock(&(philo -> eat_mutex));
		pthread_mutex_lock(&(philo -> time_mutex));
		philo -> last_eat_time = time;
		pthread_mutex_unlock(&(philo -> time_mutex));
		printf("%ld %d %s",cal_time_difference(time, philo -> data -> start_time), philo -> philo_number, FORK);
	}
	printf("%ld %d %s",cal_time_difference(time, philo -> data -> start_time), philo -> philo_number, msg);
}

int	check_die_flag_print(t_philo *philo, char *msg)
{
	int	check;

	check = 0;
	pthread_mutex_lock(&(philo -> data -> check_die_mutex));
	if (philo -> data -> check_die == 1)
		check = 1;
	if (check != 1 && msg != NULL)
		print_msg(philo, msg);
	pthread_mutex_unlock(&(philo -> data -> check_die_mutex));
	return (check);
}

int	philo_die_check(t_philo *philo)
{
	struct timeval	time;
	int				flag;
	int				dead_time;

	flag = 0;
	dead_time = philo -> data -> input ->time_to_die;
	pthread_mutex_lock(&(philo -> data -> check_die_mutex));
	gettimeofday(&time, NULL);
	pthread_mutex_lock(&(philo -> time_mutex));
	if (cal_time_difference(time, philo -> last_eat_time) > (long int)dead_time)
		philo -> data -> check_die = 1;
	pthread_mutex_unlock(&(philo -> time_mutex));
	flag = philo -> data -> check_die;
	pthread_mutex_unlock(&(philo -> data -> check_die_mutex));
	return (flag);
}
