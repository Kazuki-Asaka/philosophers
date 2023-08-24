/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akazuki <akazuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:00:01 by akazuki           #+#    #+#             */
/*   Updated: 2023/08/23 18:32:02 by akazuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_data	*philosophers;
	
	if (check_error(argc, argv) == 1)
		return (1);
	philosophers = create_data(argv);
	if (philosophers ==  NULL)
		return (1);
	start_philo_eat(philosophers);
	return (0);
}