/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akazuki <akazuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 14:44:12 by akazuki           #+#    #+#             */
/*   Updated: 2023/08/23 17:36:07 by akazuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*free_input_info(t_input_info *info)
{
	free (info);
	return (NULL);
}

void	*free_input_philo(t_philo *philo)
{
	free(philo);
	return (NULL);
}

void	*free_data(t_data *philo_data)
{
	free(philo_data);
	return(NULL);
}

void	*free_fork(t_fork *fork)
{
	free (fork);
	return (NULL);
}

void	*free_all(t_data *philo_data)
{
	free_input_info(philo_data -> philo_array ->time_info);
	free_input_philo(philo_data -> philo_array);
	free_fork(philo_data -> fork_arry);
	free_data(philo_data);
	return (NULL);
}