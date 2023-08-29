#include "philosophers.h"

void	thread_counter(t_philo	*philo)
{
	pthread_mutex_lock(&(philo ->data -> count_mutex)); 
	philo -> data->sync_count++;
	pthread_mutex_unlock(&(philo ->data -> count_mutex));
}

void	wait_thread_sync(t_philo *philo)
{
	int	flag;

	flag = 0;
	while (1)
	{
		pthread_mutex_lock(&(philo ->data -> count_mutex)); 
		if (philo -> data -> sync_count == -1)
			flag = 1;
		pthread_mutex_unlock(&(philo ->data -> count_mutex));
		if (flag == 1)
			break ;
	}
}

void	take_fork_1(t_philo *philo)
{
	if (philo -> philo_number % 2 == 1)
	{
		pthread_mutex_lock()
	}
	else
	{

	}
}

void	*start_to_eat(void *philo)
{
	t_philo	*new_philo;

	new_philo = philo;
	thread_counter(new_philo);
	wait_thread_sync(new_philo);
	while (1)
	{
		take_fork(philo);
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

void	check_mutex_count(t_philo *philosophers)
{
	while (1)
	{
		pthread_mutex_lock(&(philosophers -> data -> count_mutex));
		if (philosophers -> data -> sync_count == philosophers -> data ->input -> philo_size)
			philosophers -> data -> sync_count = -1;
		pthread_mutex_unlock(&(philosophers -> data -> count_mutex));
		if (philosophers -> data -> sync_count == -1)
		{
			gettimeofday(&philosophers -> data -> start_time, NULL);
			break ;
		}
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

void    manage_philo(t_philo *philosophers)
{
    int create_thread_number;

    create_thread_number = create_thread(philosophers);
	check_mutex_count(philosophers);
    join_loop(philosophers, create_thread_number);
}

//どのタイミングで死ぬのか。死亡のフラグを上げるのはメイン関数か、forkの持ち方