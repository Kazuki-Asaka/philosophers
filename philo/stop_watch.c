/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop_watch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akazuki <akazuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 20:34:11 by akazuki           #+#    #+#             */
/*   Updated: 2023/09/05 20:34:11 by akazuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long int	m_cal_time(struct timeval time)
{
	return (time.tv_sec * (long int)1000 + time.tv_usec / (long int)1000);
}

long int	cal_time_difference(struct timeval time1, struct timeval time2)
{
	return (m_cal_time(time1) - m_cal_time(time2));
}

void	stop_watch(t_philo *philo, int time)
{
	struct timeval	start;
	struct timeval	tmp_time;
	int				count;

	count = 0;
	gettimeofday(&start, NULL);
	while (1)
	{
		if (check_die_flag_print(philo, NULL) == 1)
			break ;
		gettimeofday(&tmp_time, NULL);
		count = cal_time_difference(tmp_time, start);
		if (count >= (long int)time)
			break ;
		usleep(100);
	}
}
