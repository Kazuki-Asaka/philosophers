#include "philosophers.h"

void	thinking(t_philo *philo)
{
	struct timeval	time;

	if (check_die_flag(philo) != 1)
	{
		if (philo_die_check(philo) != 1)
		{
			gettimeofday(&time, NULL);
			printf("%ld %d is thinking\n", cal_time_difference(time, philo -> data -> start_time), philo -> philo_number);
		}
	}
}