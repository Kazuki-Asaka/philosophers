/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akazuki <akazuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 20:36:51 by akazuki           #+#    #+#             */
/*   Updated: 2023/09/15 09:37:15 by akazuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <limits.h>
# include <stdint.h>
# include <sys/time.h>
# include <string.h>
# include <string.h>

# define EAT "is eating\n"
# define SLEEP "is sleeping\n"
# define THINK "is thinking\n"
# define FORK "have taken a fork\n"
# define DIED "is died\n"

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
	pthread_mutex_t	eat_mutex;
	int				right_hund_status;
	int				left_hund_status;
	struct timeval	last_eat_time;
	pthread_mutex_t	time_mutex;
	t_data			*data;
}t_philo;

int			check_error(int argc, char **argv);
void		*ft_calloc(size_t count, size_t size);
int			ft_atoi(const char *str);
t_data		*create_philo_data(char **argv);
void		*free_input_info(t_input_info *info);
void		*free_philo(t_philo *philo);
void		*free_data(t_data *philo_data);
void		*free_fork(t_fork *fork);
void		*free_all(t_philo *philosophers);
t_philo		*create_philo_array(char **argv);
void		manage_philo(t_philo *philoophers);
long int	m_cal_time(struct timeval time);
long int	cal_time_difference(struct timeval time1, struct timeval time2);
void		check_mutex_count(t_philo *philosophers);
void		stop_watch(t_philo *philo, int time);
void		thread_counter(t_philo	*philo);
void		not_start_eat(t_philo *philosophers);
void		set_init_last_eat_time(t_philo *philosophers, struct timeval time);
int			wait_thread_sync(t_philo *philo);
void		take_fork(t_philo *philo);
void		get_fork_odd_number_philo(t_philo *philo);
void		get_fork_even_number_philo(t_philo *philo);
void		thinking(t_philo *philo);
void		falling_asleep(t_philo *philo);
int			check_philo_eat_count(t_philo *philo);
int			philo_eat_check(t_philo *philo);
int			check_die_flag_print(t_philo *philo, char *msg);
int			philo_die_check(t_philo *philo);
int			init_fork_array(t_fork *fork, int philo_size);
int			init_common_data_mutex(t_data *data);
int			init_philo_mutex(t_philo *philo_array);
void		set_common_data(t_data *common_data, t_philo *philo_array);
void		set_fork(t_philo *philo_array);
void		destroy_mutex_fork(t_fork *fork, int size);
void		destroy_mutex_eat(t_philo *philo, int size);
void		destroy_mutex_time(t_philo *philo, int size);
void		destroy_all_mutex(t_philo *philo_array);

#endif