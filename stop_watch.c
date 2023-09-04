#include "philosophers.h"

long int	m_cal_time(struct timeval time)
{
	return (time.tv_sec * (long int)1000 + time.tv_usec / (long int)1000);
}

long int	cal_time_difference(struct timeval time1, struct timeval time2)
{
	return (m_cal_time(time1) - m_cal_time(time2));
}

void    stop_watch(int time)
{
	struct timeval	start;
	struct timeval	tmp_time;	
	int				count;

	count = 0;
	gettimeofday(&start, NULL);
	while(1)
	{
		gettimeofday(&tmp_time, NULL);
		count = cal_time_difference(tmp_time, start);
		if (count >= (long int)time)
			break ;
		// usleep(100);
	}
}