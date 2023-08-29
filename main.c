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
	t_philo	*philosophers;
	
	if (check_error(argc, argv) == 1)
		return (1);
	philosophers = create_philo_array(argv);
	if (philosophers == NULL)
		return (1);
	manage_philo(philosophers);
	printf("count %d\n", philosophers -> data -> sync_count);
	// printf("time  %ld\n", philosophers -> data -> start_time.tv_sec);
	// printf("time  %ld\n", philosophers -> data -> start_time.tv_usec);
	return (0);
}

//forkの配列をright_hund, left_hundに格納
//書き込んでるときの読み込みは競合するか