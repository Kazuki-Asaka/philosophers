/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akazuki <akazuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 14:31:34 by akazuki           #+#    #+#             */
/*   Updated: 2023/09/06 14:48:45 by akazuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	set_common_data(t_data *common_data, t_philo *philo_array)
{
	int	i;

	i = 0;
	while (i < common_data -> input -> philo_size)
	{
		philo_array[i].philo_number = i + 1;
		philo_array[i].data = common_data;
		i++;
	}
}

void	set_fork(t_philo *philo_array)
{
	int		i;
	int		count;
	t_philo	*philo;

	i = 0;
	count = philo_array -> data -> input -> philo_size;
	while (i < count)
	{
		philo = &philo_array[i];
		philo -> left_hund = &(philo_array -> data -> fork[i]);
		if (i == 0)
			philo -> right_hund = &(philo_array -> data -> fork[count - 1]);
		else
			philo -> right_hund = &(philo_array -> data -> fork[i - 1]);
		i ++;
	}
}
