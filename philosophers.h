#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <limits.h>
# include <stdint.h>
# include <sys/time.h>

typedef struct s_input_info
{
	int	philo_size;
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

typedef struct s_data
{
	int				sync_count;
	pthread_mutex_t	count_mutex;
	int				check_die;
	pthread_mutex_t	check_die_mutex;
	t_input_info	*input;
	t_fork			*fork;
	struct timeval	start_time;
}t_data;

typedef struct s_philo
{
	int				philo_number;
	pthread_t		thread;
	t_fork			*left_hund;
	t_fork			*right_hund;
	int				eat_count;
	struct timeval	last_eat_time;
	t_data			*data;
}t_philo;


int	check_error(int argc, char **argv);

void	*ft_calloc(size_t count, size_t size);
int		ft_atoi(const char *str);
t_data	*create_philo_data(char **argv);

void	*free_input_info(t_input_info *info);
void	*free_philo(t_philo *philo);
void	*free_data(t_data *philo_data);
void	*free_fork(t_fork *fork);
void	*free_all(t_philo *philosophers);

t_philo *create_philo_array(char **argv);

void    manage_philo(t_philo *philoophers);

#endif