/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_start_eat.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akazuki <akazuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 14:47:16 by akazuki           #+#    #+#             */
/*   Updated: 2023/08/24 20:32:52 by akazuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*kannsuu(void *philo)
{
	t_philo	*cast_philo;

	cast_philo = philo;
	if (cast_philo ->philo_number % 2 == 0)
	{
		cas
	}
	else
	{
		
	}
	return (NULL);
}

int	create_philo_thread(t_data *philo_data)
{
	int	i;
	t_philo	*philo;

	i = 1;
	while(i <= philo_data -> philo_size)
	{
	// printf("philo size = %d\n", philo_data -> philo_size);
		philo = &philo_data->philo_array[i - 1];
		if (pthread_create(&philo->thread, NULL, kannsuu, philo))
			return (i);
		i++;
	}
	return (philo_data -> philo_size);
}

void	join_loop(t_data *philo_data, int create_thread_number)
{
	int	i;
	
	i = 0;
	while(i < create_thread_number)
	{
		pthread_join(philo_data -> philo_array[i].thread, NULL);
		i++;
	}
}

void	manage_philo(t_data *philo_data)
{
	int	create_thread_number;

	create_thread_number = create_philo_thread(philo_data);
	join_loop(philo_data, create_thread_number);
}