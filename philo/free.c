/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akazuki <akazuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 14:44:12 by akazuki           #+#    #+#             */
/*   Updated: 2023/09/06 14:10:43 by akazuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*free_input_info(t_input_info *info)
{
	free (info);
	return (NULL);
}

void	*free_philo(t_philo *philo)
{
	free(philo);
	return (NULL);
}

void	*free_data(t_data *philo_data)
{
	free(philo_data);
	return (NULL);
}

void	*free_fork(t_fork *fork)
{
	free (fork);
	return (NULL);
}

void	*free_all(t_philo *philosophers)
{
	free_input_info(philosophers -> data -> input);
	free_fork(philosophers -> data -> fork);
	free_data(philosophers -> data);
	free_philo(philosophers);
	return (NULL);
}
