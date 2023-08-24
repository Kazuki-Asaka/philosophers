#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <limits.h>

typedef struct s_input_info
{
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	must_eat;
}t_input_info;

typedef struct s_fork
{
	int				fork_status;
	int 			prev_philo_number;
	pthread_mutex_t	mutex;
}t_fork;

typedef struct s_philo
{
	int				philo_number;
	pthread_t		thread;
	t_fork			*left_hund;
	t_fork			*right_hund;
	t_input_info	*time_info;
	int				eat_count;
	int				start_time;
}t_philo;

typedef struct s_data
{
	int		philo_size;
	t_philo	*philo_array;
	t_fork	*fork_arry;
	int		sync_count;
	pthread_mutex_t	count_mutex;
	int		check_die;
}t_data;

int	check_error(int argc, char **argv);

void	*ft_calloc(size_t count, size_t size);
int		ft_atoi(const char *str);
t_data	*create_data(char **argv);

void	*free_input_info(t_input_info *info);
void	*free_input_philo(t_philo *philo);
void	*free_data(t_data *philo_data);
void	*free_fork(t_fork *fork);
void	*free_all(t_data *philo_data);

void	manage_philo(t_data *philo_data)

#endif