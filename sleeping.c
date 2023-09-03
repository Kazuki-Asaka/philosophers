#include "philosophers.h"

void	falling_asleep(t_philo *philo)
{
	struct timeval	time;

	if (philo -> philo_number % 2 == 1)
	{
		pthread_mutex_unlock(&(philo -> left_hund -> mutex));
		pthread_mutex_unlock(&(philo -> right_hund -> mutex));
	}
	else
	{
		pthread_mutex_unlock(&(philo -> right_hund -> mutex));
		pthread_mutex_unlock(&(philo -> left_hund -> mutex));
	}
	philo -> right_hund_status = 0;
	philo -> left_hund_status = 0;
	if (check_die_flag(philo) != 1)
	{
		gettimeofday(&time, NULL);
		printf("%ld %d is sleeping\n", cal_time_difference(time, philo -> data -> start_time), philo -> philo_number);
		stop_watch(philo -> data -> input -> time_to_sleep);
	}
}