/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akazuki <akazuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:11:02 by akazuki           #+#    #+#             */
/*   Updated: 2023/08/23 19:19:06 by akazuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_input_info	*atoi_input(char **argv)
{
	t_input_info	*info;

	info = ft_calloc(1, sizeof(t_input_info));
	if (info == NULL)
		return (NULL);
	info -> time_to_die = ft_atoi(argv[2]);
	if (info -> time_to_die == -1)
		return (free_input_info(info));
	info -> time_to_eat = ft_atoi(argv[3]);
	if (info -> time_to_eat == -1)
		return (free_input_info(info));
	info -> time_to_sleep = ft_atoi(argv[4]);
	if (info -> time_to_sleep == -1)
		return (free_input_info(info));
	if (argv[5] != NULL)
	{
		info -> must_eat = ft_atoi(argv[5]);
		if (info -> must_eat == -1)
		return (free_input_info(info));
	}
	return (info);
}

static void	set_time_to_philo(int philo_member, t_philo *philosophers,t_input_info *info)
{
	int	i;

	i = 1;
	while(i <= philo_member)
	{
		philosophers[i - 1].philo_number = i;
		philosophers[i - 1].time_info = info;
		i++;
	}
}

static t_philo	*set_input_time_data(t_data *philo_data,char **argv)
{
	t_philo			*philosophers;
	int				philo_member;
	t_input_info	*info;
	
	philo_member = ft_atoi(argv[1]);
	if (philo_member == 0 || philo_member == -1)
		return (NULL);
	philo_data -> philo_size = philo_member;
	philosophers = ft_calloc(philo_member, sizeof(t_philo));
	if (philosophers == NULL)
		return (NULL);
	info = atoi_input(argv);
	if (info == NULL)
		return (free_input_philo(philosophers));
	set_time_to_philo(philo_member, philosophers, info);	
	return (philosophers);
}


static t_fork	*init_mutex(t_fork *fork, int philomember)
{
	int	i;

	i = 0;
	while(i < philomember)
	{
		if (pthread_mutex_init(&(fork[i].mutex), NULL) != 0)
		{
			free(fork);
			return (NULL);
			break ;
		}
		i++;
	}
	return (fork);
}

static t_fork	*set_input_fork_data(t_data *philo_data)
{
	t_fork	*fork;
	int		philo_member;

	philo_member = philo_data -> philo_size;
	fork = ft_calloc(philo_member, sizeof(t_fork));
	if (fork == NULL)
	{
		free_input_info(philo_data -> philo_array -> time_info);
		return (free_input_philo(philo_data -> philo_array));
	}
	return(init_mutex(fork, philo_member));
}

t_data	*create_data(char **argv)
{
	t_data	*philo_data;

	philo_data = ft_calloc(1, sizeof(t_data));
	if (philo_data == NULL)
		return (NULL);
	philo_data -> philo_array = set_input_time_data(philo_data, argv);
	if (philo_data -> philo_array== NULL)
		return (free_data(philo_data));
	philo_data -> fork_arry = set_input_fork_data(philo_data);
	if (philo_data -> fork_arry == NULL)
		return (free_data(philo_data));
	if (pthread_mutex_init(&(philo_data -> count_mutex), NULL) != 0)
		return (free_all(philo_data));
	return (philo_data);
}