/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akazuki <akazuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:00:01 by akazuki           #+#    #+#             */
/*   Updated: 2023/09/06 14:29:36 by akazuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_philo	*philosophers;

	if (check_error(argc, argv) == 1)
		return (1);
	philosophers = create_philo_array(argv);
	if (philosophers == NULL)
		return (1);
	manage_philo(philosophers);
	return (0);
}
