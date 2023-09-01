#include "philosophers.h"

void	get_fork_odd_number_philo(t_philo *philo)
{
	struct timeval time;

	if (philo -> left_hund_status != 1)
	{
		pthread_mutex_lock(&(philo -> left_hund -> mutex));
		if (philo -> left_hund -> prev_philo == philo -> philo_number)
			pthread_mutex_unlock(&(philo -> left_hund -> mutex));
		else
		{
			gettimeofday(&time, NULL);
			printf("%ld %d has taken a fork\n", cal_time_difference(time, philo -> data -> start_time), philo -> philo_number);
			philo -> left_hund_status = 1;
			philo -> left_hund -> prev_philo = philo -> philo_number;
		}
	}
	if (philo -> left_hund_status == 1)
	{
		pthread_mutex_lock(&(philo -> right_hund -> mutex));
		gettimeofday(&time, NULL);
		philo -> right_hund_status = 1;
		philo -> right_hund -> prev_philo = philo -> philo_number;
		printf("%ld %d has taken a fork\n", cal_time_difference(time, philo -> data -> start_time), philo -> philo_number);
		printf("%ld %d is eating\n", cal_time_difference(time, philo -> data -> start_time), philo -> philo_number);
		philo -> last_eat_time = time;
		stop_watch(philo -> data -> input -> time_to_eat);
	}
}

void	get_fork_even_number_philo(t_philo *philo)
{
	struct timeval	time;

	if (philo -> right_hund_status != 1)
	{
		pthread_mutex_lock(&(philo -> right_hund -> mutex));
		if (philo -> right_hund -> prev_philo == philo -> philo_number)
			pthread_mutex_unlock(&(philo -> right_hund -> mutex));
		else
		{
			gettimeofday(&time, NULL);
			printf("%ld %d has taken a fork\n", cal_time_difference(time, philo -> data -> start_time), philo -> philo_number);
			philo -> right_hund_status = 1;
			philo -> right_hund -> prev_philo = philo -> philo_number;
		}
	}
	if (philo -> right_hund_status == 1)
	{
		gettimeofday(&time, NULL);
		pthread_mutex_lock(&(philo -> left_hund -> mutex));
		philo -> left_hund_status = 1;
		philo -> left_hund -> prev_philo = philo -> philo_number;
		printf("%ld %d has taken a fork\n", cal_time_difference(time, philo -> data -> start_time), philo -> philo_number);
		printf("%ld %d is eating\n", cal_time_difference(time, philo -> data -> start_time), philo -> philo_number);
		philo -> last_eat_time = time;
		stop_watch(philo -> data -> input -> time_to_eat);
	}
}

void	take_fork(t_philo *philo)
{
	if (philo -> philo_number % 2 == 1)
		get_fork_odd_number_philo(philo);
	else
		get_fork_even_number_philo(philo);
}