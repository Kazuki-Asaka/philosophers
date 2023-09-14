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

int	check_philo_eat_count(t_philo *philo)
{
	int	flag;

	flag = 0;
	pthread_mutex_lock(&(philo -> data -> check_die_mutex));
	if (philo -> data -> check_die == 2)
		flag = 2;
	pthread_mutex_unlock(&(philo -> data -> check_die_mutex));
	if (flag == 2)
		return (1);
	else
		return (0);
}

int	philo_eat_check(t_philo *philo)
{
	int	i;
	int	flag;

	i = 0;
	while (i < philo -> data -> input -> philo_size)
	{
		flag = 0;
		pthread_mutex_lock(&(philo[i].eat_mutex));
		if (philo[i].data -> input -> must_eat != 0
			&& philo[i].eat_count >= philo -> data -> input -> must_eat)
			flag = 1;
		pthread_mutex_unlock(&(philo[i].eat_mutex));
		if (flag == 1)
			i ++;
		else
			break ;
	}
	if (flag == 1)
	{
		pthread_mutex_lock(&philo -> data -> check_die_mutex);
		philo -> data -> check_die = 2;
		pthread_mutex_unlock(&philo -> data -> check_die_mutex);
	}
	return (flag);
}

void	print_msg(t_philo *philo, char *msg)
{
	struct timeval	time;
	long int		dif_time;

	gettimeofday(&time, NULL);
	dif_time = cal_time_difference(time, philo -> data -> start_time);
	if (msg == EAT)
	{
		pthread_mutex_lock(&(philo -> eat_mutex));
		philo -> eat_count++;
		pthread_mutex_unlock(&(philo -> eat_mutex));
		pthread_mutex_lock(&(philo -> time_mutex));
		philo -> last_eat_time = time;
		pthread_mutex_unlock(&(philo -> time_mutex));
		printf("%ld %d %s", dif_time, philo -> philo_number, FORK);
	}
	printf("%ld %d %s", dif_time, philo -> philo_number, msg);
}

int	check_die_flag_print(t_philo *philo, char *msg)
{
	int	check;

	check = 0;
	if (philo -> data -> input -> philo_size == 1)
		pthread_mutex_unlock(&(philo -> left_hund -> mutex));
	pthread_mutex_lock(&(philo -> data -> check_die_mutex));
	if (philo -> data -> check_die == 1 || philo -> data -> check_die == 2)
		check = 1;
	if (msg == DIED)
		print_msg(philo, msg);
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
	gettimeofday(&time, NULL);
	pthread_mutex_lock(&(philo -> data -> check_die_mutex));
	pthread_mutex_lock(&(philo -> time_mutex));
	if (cal_time_difference(time, philo -> last_eat_time) > (long int)dead_time)
	{
		philo -> data -> check_die = 1;
		flag = 1;
	}
	pthread_mutex_unlock(&(philo -> time_mutex));
	pthread_mutex_unlock(&(philo -> data -> check_die_mutex));
	return (flag);
}
