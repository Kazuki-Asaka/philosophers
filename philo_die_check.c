#include "philosophers.h"

// int check_die_flag(t_philo *philo)
// {
//     int check;

//     pthread_mutex_lock(&(philo -> data -> check_die_mutex));
//     check = philo -> data -> check_die;
//     pthread_mutex_unlock(&(philo -> data -> check_die_mutex));
//     return (check);
// }


int	check_die_flag(t_philo *philo)
{
	int	check;

	check = 0;
	pthread_mutex_lock(&(philo -> data -> check_die_mutex));
	if (philo -> data -> check_die == 1)
		check = 1;
	if (philo -> data ->input ->must_eat != 0 && philo-> data -> input -> must_eat == philo -> eat_count)
		check = 1;
	pthread_mutex_unlock(&(philo -> data -> check_die_mutex));
	return (check);
}

int philo_die_check(t_philo *philo)
{
    struct timeval time;

    gettimeofday(&time, NULL);
    if (cal_time_difference(time, philo -> last_eat_time) > philo -> data -> input ->time_to_die)
    {
        pthread_mutex_lock(&(philo -> data -> check_die_mutex));
        philo -> data -> check_die = 1;
		printf("%ld %d is died\n", cal_time_difference(time, philo -> data -> start_time), philo -> philo_number);
        pthread_mutex_unlock(&(philo -> data -> check_die_mutex));
        return (1);
    }
    return (0);
}