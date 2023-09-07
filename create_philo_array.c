/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philo_array.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akazuki <akazuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 20:24:30 by akazuki           #+#    #+#             */
/*   Updated: 2023/09/05 20:24:30 by akazuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_input_info	*create_common_input(char **argv)
{
	t_input_info	*input_info;

	input_info = ft_calloc(1, sizeof(t_input_info));
	if (input_info == NULL)
		return (NULL);
	input_info -> philo_size = ft_atoi(argv[1]);
	if (input_info -> philo_size == 0)
		return (free_input_info(input_info));
	input_info -> time_to_die = ft_atoi(argv[2]);
	if (input_info -> time_to_die == 0)
		return (free_input_info(input_info));
	input_info -> time_to_eat = ft_atoi(argv[3]);
	input_info -> time_to_sleep = ft_atoi(argv[4]);
	if (argv[5] != NULL)
	{
		input_info -> must_eat = ft_atoi(argv[5]);
		if (input_info -> must_eat == 0)
			return (free_input_info(input_info));
	}
	return (input_info);
}

t_fork	*create_common_fork(int philo_size)
{
	t_fork	*fork;
	int		check;

	fork = ft_calloc(philo_size, sizeof(t_fork));
	if (fork == NULL)
		free (NULL);
	check = init_fork_array(fork, philo_size);
	if (check != philo_size)
	{
		destroy_mutex_fork(fork, check);
		return (free_fork(fork));
	}
	return (fork);
}

t_data	*create_common_data(char **argv)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	if (data == NULL)
		return (NULL);
	data -> input = create_common_input(argv);
	if (data -> input == NULL)
		return (free_data(data));
	data -> fork = create_common_fork(data -> input -> philo_size);
	if (data -> fork == NULL)
	{
		free_input_info(data -> input);
		return (free_data(data));
	}
	if (init_common_data_mutex(data) != 0)
	{
		destroy_mutex_fork(data -> fork, data -> input -> philo_size);
		free_input_info(data -> input);
		return (free_data(data));
	}
	return (data);
}

t_philo	*create_philo_array(char **argv)
{
	t_philo	*philo_array;
	t_data	*common_data;
	int		check;

	philo_array = ft_calloc(ft_atoi(argv[1]), sizeof(t_philo));
	if (philo_array == NULL)
		return (NULL);
	common_data = create_common_data(argv);
	if (common_data == NULL)
		return (free_philo(philo_array));
	set_common_data(common_data, philo_array);
	set_fork(philo_array);
	if (init_philo_mutex(philo_array) != 0)
	{
		check = common_data -> input -> philo_size;
		destroy_mutex_fork(common_data -> fork, check);
		pthread_mutex_destroy(&(philo_array -> data -> check_die_mutex));
		pthread_mutex_destroy(&(philo_array -> data -> count_mutex));
		free_all(philo_array);
	}
	return (philo_array);
}
