#include "philosophers.h"

// int check_die_flag(t_philo *philo)
// {
//     int check;

//     pthread_mutex_lock(&(philo -> data -> check_die_mutex));
//     check = philo -> data -> check_die;
//     pthread_mutex_unlock(&(philo -> data -> check_die_mutex));
//     return (check);
// }


void	print_msg(char *msg, time)
{
	printf("%ld %d has taken a fork\n", cal_time_difference(time, philo -> data -> start_time), philo -> philo_number);
}

int	check_die_flag(t_philo *philo, char *msg);
{
	int	check;

	check = 0;
	pthread_mutex_lock(&(philo -> data -> check_die_mutex));
	if (philo -> data -> check_die == 1)
		check = 1;
	if (philo -> data ->input ->must_eat != 0 && philo-> data -> input -> must_eat == philo -> eat_count)
		check = 1;
	if (check == 0)
		print_msg(msg);
	pthread_mutex_unlock(&(philo -> data -> check_die_mutex));
	return (check);
}

int philo_die_check(t_philo *philo)
{
	struct timeval	time;
	int				flag;

	flag = 0;
	pthread_mutex_lock(&(philo -> data -> check_die_mutex));
	gettimeofday(&time, NULL);
	if (cal_time_difference(time, philo -> last_eat_time) > philo -> data -> input ->time_to_die)
		philo -> data -> check_die = 1;
	flag = philo -> data -> check_die;
	pthread_mutex_unlock(&(philo -> data -> check_die_mutex));
	return (flag);
}