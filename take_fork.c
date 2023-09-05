/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akazuki <akazuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 12:19:06 by akazuki           #+#    #+#             */
/*   Updated: 2023/09/02 12:19:06 by akazuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	precedence_hund(t_philo *philo, char c)
{
	// struct timeval	time;

	if (c == 'l')
	{
		philo -> left_hund_status = 1;
		philo -> left_hund -> prev_philo = philo -> philo_number;
	}
	else
	{
		philo -> right_hund_status = 1;
		philo -> right_hund -> prev_philo = philo -> philo_number;
	}
	// if (check_die_flag(philo) != 1)
	// {
	// 	gettimeofday(&time, NULL);
	// 	printf("%ld %d has taken a fork\n", cal_time_difference(time, philo -> data -> start_time), philo -> philo_number);
	// }
	check_die_flag_print(philo, FORK);
}

void	trailing_hund(t_philo *philo, char c)
{
	// struct timeval	time;

	check_die_flag_print(philo, EAT);
	if (c == 'l')
	{
		// pthread_mutex_lock(&(philo -> left_hund -> mutex));
		philo -> left_hund_status = 1;
		philo -> left_hund -> prev_philo = philo -> philo_number;
	}
	else
	{
		// pthread_mutex_lock(&(philo -> right_hund -> mutex));
		philo -> right_hund_status = 1;
		philo -> right_hund -> prev_philo = philo -> philo_number;
	}
	philo -> eat_count++;
	// if (check_die_flag_print(philo, EAT) != 1)
	// {
		// gettimeofday(&time, NULL);
		// philo -> last_eat_time = time;
		// printf("%ld %d has taken a fork\n", cal_time_difference(time, philo -> data -> start_time), philo -> philo_number);
		// printf("%ld %d is eating\n", cal_time_difference(time, philo -> data -> start_time), philo -> philo_number);
		stop_watch(philo -> data -> input -> time_to_eat);
	// }
}

void	get_fork_odd_number_philo(t_philo *philo)
{
	if (philo -> left_hund_status != 1)
	{
		pthread_mutex_lock(&(philo -> left_hund -> mutex));
		if (philo -> left_hund -> prev_philo == philo -> philo_number)
			pthread_mutex_unlock(&(philo -> left_hund -> mutex));
		else
			precedence_hund(philo, 'l');
	}
	if (philo -> left_hund_status == 1)
	{
		pthread_mutex_lock(&(philo -> right_hund -> mutex));
		if (philo -> right_hund -> prev_philo == philo -> philo_number)
			pthread_mutex_unlock(&(philo -> right_hund -> mutex));
		else
			trailing_hund(philo, 'r');
	}
}

void	get_fork_even_number_philo(t_philo *philo)
{
	if (philo -> right_hund_status != 1)
	{
		pthread_mutex_lock(&(philo -> right_hund -> mutex));
		if (philo -> right_hund -> prev_philo == philo -> philo_number)
			pthread_mutex_unlock(&(philo -> right_hund -> mutex));
		else
			precedence_hund(philo, 'r');
	}
	if (philo -> right_hund_status == 1)
	{
		pthread_mutex_lock(&(philo -> left_hund -> mutex));
		if (philo -> left_hund -> prev_philo == philo -> philo_number)
			pthread_mutex_unlock(&(philo -> left_hund -> mutex));
		else
			trailing_hund(philo, 'l');
	}
}

void	take_fork(t_philo *philo)
{
	if (philo -> philo_number % 2 == 1)
		get_fork_odd_number_philo(philo);
	else
		get_fork_even_number_philo(philo);
}