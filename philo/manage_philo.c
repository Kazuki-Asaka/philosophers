/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akazuki <akazuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 13:23:41 by akazuki           #+#    #+#             */
/*   Updated: 2023/09/06 13:23:41 by akazuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*start_to_eat(void *philo)
{
	t_philo	*new_philo;

	new_philo = philo;
	thread_counter(new_philo);
	if (wait_thread_sync(new_philo) == -2)
		return (NULL);
	while (1)
	{
		take_fork(new_philo);
		if (new_philo -> right_hund_status == 1
			&& new_philo -> left_hund_status == 1)
		{
			falling_asleep(new_philo);
			thinking(new_philo);
		}
		if (check_die_flag_print(new_philo, NULL) == 1)
			break ;
		if (check_philo_eat_count(new_philo) == 1)
			break ;
	}
	return (NULL);
}

int	create_thread(t_philo *philosophers)
{
	int		i;
	int		thread_size;
	t_philo	*philo;

	i = 0;
	thread_size = philosophers -> data -> input -> philo_size;
	while (i < thread_size)
	{
		philo = &philosophers[i];
		if (pthread_create(&(philo->thread), NULL, start_to_eat, philo) != 0)
			return (i);
		i++;
	}
	return (thread_size);
}

void	join_loop(t_philo *philosophers, int create_thread_number)
{
	int	i;

	i = 0;
	while (i < create_thread_number)
	{
		pthread_join(philosophers[i].thread, NULL);
		i++;
	}
}

void	check_philo_status(t_philo *philosophers)
{
	int				i;
	int				philo_count;
	int				flag;

	flag = 0;
	philo_count = philosophers -> data -> input -> philo_size;
	while (1)
	{
		i = 0;
		while (i < philo_count)
		{
			flag = philo_die_check(&philosophers[i]);
			if (flag == 1)
				break ;
			i++;
		}
		if (flag == 1)
			break ;
		if (philo_eat_check(philosophers) == 1)
			return ;
	}
	if (flag == 1)
		check_die_flag_print(&philosophers[i], DIED);
}

void	manage_philo(t_philo *philosophers)
{
	int	create_thread_number;
	int	philo_size;

	philo_size = philosophers -> data -> input -> philo_size;
	create_thread_number = create_thread(philosophers);
	if (create_thread_number == philo_size)
	{
		check_mutex_count(philosophers);
		check_philo_status(philosophers);
	}
	else
		not_start_eat(philosophers);
	join_loop(philosophers, create_thread_number);
	destroy_all_mutex(philosophers);
}
