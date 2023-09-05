#include "philosophers.h"


int	check_philo_eat_count(t_philo *philo)
{
	int	flag;

	flag = 0;
	pthread_mutex_lock(&(philo -> eat_mutex));
	if (philo -> eat_count == philo -> data -> input -> must_eat)
		flag = 1;
	pthread_mutex_unlock(&(philo -> eat_mutex));
	if (flag == 1)
	{
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
		return (1);
	}
	else
		return (0);
}

int	philo_eat_check(t_philo *philo)
{
	int	flag;

	flag = 0;
	pthread_mutex_lock(&(philo -> eat_mutex));
	if (philo -> data -> input -> must_eat && philo -> eat_count == philo -> data -> input -> must_eat)
		flag = 1;
	pthread_mutex_unlock(&(philo -> eat_mutex));
	return (flag);
}

void	*start_to_eat(void *philo)
{
	t_philo	*new_philo;

	new_philo = philo;
	thread_counter(new_philo);
	wait_thread_sync(new_philo);
	while (1)
	{
		take_fork(new_philo);
		if (new_philo -> right_hund_status == 1 && new_philo -> left_hund_status == 1)
		{
			if (check_philo_eat_count(new_philo) == 1)
				break;
			falling_asleep(new_philo);
			thinking(new_philo);
		}
		if (check_die_flag_print(new_philo, NULL) == 1)
			break ;
	}
	return (NULL);
}

int	create_thread(t_philo *philosophers)
{
	int	i;
	int	thread_size;

	i = 0;
	thread_size = philosophers -> data -> input -> philo_size;
	while (i < thread_size)
	{
		if(pthread_create(&(philosophers[i].thread), NULL, start_to_eat, &philosophers[i]) != 0)
			return(i);
		i++;
	}
	return (thread_size);
}

void	set_init_last_eat_time(t_philo *philosophers, struct timeval time)
{
	int	i;
	int	count;

	i = 0;
	count = philosophers -> data -> input -> philo_size;
	while (i < count)
	{
		philosophers[i].last_eat_time = time;
		i ++;
	}
}

void	check_mutex_count(t_philo *philosophers)
{
	int	flag;

	flag = 0;
	while (1)
	{
		pthread_mutex_lock(&(philosophers -> data -> count_mutex));
		if (philosophers -> data -> sync_count == philosophers -> data ->input -> philo_size)
		{
			gettimeofday(&philosophers -> data -> start_time, NULL);
			set_init_last_eat_time(philosophers, philosophers -> data -> start_time);
			philosophers -> data -> sync_count = -1;
			flag = 1;
		}
		pthread_mutex_unlock(&(philosophers -> data -> count_mutex));
		if (flag == 1)
			break;
	}
}

void	join_loop(t_philo *philosophers, int create_thread_number)
{
	int	i;
	
	i = 0;
	while(i < create_thread_number)
	{
		pthread_join(philosophers[i].thread, NULL);
		i++;
	}
}

void	check_philo_status(t_philo *philosophers)
{
	int	i;
	int	philo_count;
	int	flag;
	struct timeval	time;

	flag = 0;
	philo_count = philosophers -> data -> input -> philo_size;
	while (1)
	{
		i = 0;
		while (i < philo_count)
		{
			flag = philo_die_check(&philosophers[i]);
			if (flag == 1)
				break ;
			if (philo_eat_check(&philosophers[i]) == 1)
				return ;
			i++;
		}
		if (flag == 1)
			break ;
	}
	if (flag == 1)
	{
		gettimeofday(&time, NULL);
		printf("%ld %d %s", cal_time_difference(time, philosophers[i].data -> start_time), i + 1, DIED);
	}
}

void	manage_philo(t_philo *philosophers)
{
	int create_thread_number;

	create_thread_number = create_thread(philosophers);
	check_mutex_count(philosophers);
	check_philo_status(philosophers);
	join_loop(philosophers, create_thread_number);
}
