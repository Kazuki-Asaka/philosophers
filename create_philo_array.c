#include "philosophers.h"

t_input_info	*create_common_input(char **argv)
{
	t_input_info	*input_info;

	input_info = ft_calloc(1, sizeof(t_input_info));
	if (input_info == NULL)
		return (NULL);
	input_info -> philo_size = ft_atoi(argv[1]);
	input_info -> time_to_die = ft_atoi(argv[2]);
	input_info -> time_to_eat = ft_atoi(argv[3]);
	input_info -> time_to_sleep = ft_atoi(argv[4]);
	if (argv[5] != NULL)
		input_info -> must_eat = ft_atoi(argv[5]);
	return (input_info);
}

int init_fork_array(t_fork *fork, int philo_size)
{
	int	i;

	i = 0;
	while (i < philo_size)
	{
		if (pthread_mutex_init(&(fork[i].mutex), NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

t_fork	*create_common_fork(int philo_size)
{
	t_fork	*fork;

	fork = ft_calloc(philo_size, sizeof(t_fork));
	if (fork == NULL)
		free (NULL);
	if (init_fork_array(fork, philo_size) != 0)
		return (free_fork(fork));
	return (fork);
}

int	init_common_data_mutex(t_data *data)
{
	if (pthread_mutex_init(&(data -> count_mutex), NULL) != 0)
		return (1);
	if (pthread_mutex_init(&(data -> check_die_mutex), NULL) != 0)
		return (1);
	return (0);
}

t_data	*create_common_data(char **argv)
{
	t_data   *data;

	data = ft_calloc(1, sizeof(t_data));
	if (data == NULL)
		return (NULL);
	data -> input = create_common_input(argv);
	if (data -> input == NULL)
		return (free_data(data));
	data -> fork = create_common_fork(data -> input -> philo_size);
	if (data -> fork == NULL)
	{
		free_input_info(data -> input);
		return (free_data(data));
	}
	if (init_common_data_mutex(data) != 0)
	{
		free_input_info(data -> input);
		return (free_data(data));
	}
	return (data);
}

void	set_common_data(t_data *common_data, t_philo *philo_array)
{
	int i;

	i = 0;
	while (i < common_data -> input -> philo_size)
	{
		philo_array[i].philo_number = i + 1;
		philo_array[i].data = common_data;
		i++;
	}
}

void	set_fork(t_philo *philo_array)
{
	int i;
	int count;

	i = 0;
	count = philo_array -> data -> input -> philo_size;
	while(i < count)
	{
		philo_array[i].left_hund = &(philo_array -> data -> fork[i]);
		philo_array[i].right_hund = &(philo_array -> data -> fork[i % count - 1]);
		i ++;
	}
}

t_philo *create_philo_array(char **argv)
{
	t_philo *philo_array;
	t_data  *common_data;

	philo_array = ft_calloc(ft_atoi(argv[1]), sizeof(t_philo));
	if (philo_array == NULL)
		return (NULL);
	common_data = create_common_data(argv);
	if (common_data == NULL)
		return (free_philo(philo_array));
	set_common_data(common_data, philo_array);
	set_fork(philo_array);
	return (philo_array);
}