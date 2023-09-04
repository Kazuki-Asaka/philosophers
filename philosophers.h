#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <limits.h>
# include <stdint.h>
# include <sys/time.h>

#define EAT "is eating"
#define SLEEP "is sleepung"
#define THINK "is thinking"
#define FORK "has taken a fork"

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
	int				prev_philo;
	pthread_mutex_t	mutex;
}t_fork;

typedef struct s_data
{
	int				sync_count;
	pthread_mutex_t	count_mutex;
	pthread_mutex_t	print_mutex;
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
	int				right_hund_status;
	int				left_hund_status;
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

long int	m_cal_time(struct timeval time);
long int	cal_time_difference(struct timeval time1, struct timeval time2);
void    	stop_watch(int time);

void	thread_counter(t_philo	*philo);
void	wait_thread_sync(t_philo *philo);

void	take_fork(t_philo *philo);
void	get_fork_odd_number_philo(t_philo *philo);
void	get_fork_even_number_philo(t_philo *philo);

void	thinking(t_philo *philo);

void	falling_asleep(t_philo *philo);

int	check_die_flag(t_philo *philo, char *msg);
int philo_die_check(t_philo *philo);

#endif