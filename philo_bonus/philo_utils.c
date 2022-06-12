#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>

#include "include/philo.h"
#include "include/utils.h"
#include "include/unwrap.h"

void	print_log(const t_philo_info *ph_info, t_philo_status status)
{
	const long long	timestamp = (get_usec() - ph_info->common->start) / 1000;

	 if (status != DIED && get_simulation_finished(ph_info))
		return ;
	sem_wait_unwrap(ph_info->common->sem_out);
	if (status == TAKEN_FORK)
		printf("%lld %d has taken a fork\n", timestamp, ph_info->id);
	else if (status == EATING)
		printf("%lld %d is eating\n", timestamp, ph_info->id);
	else if (status == SLEEPING)
		printf("%lld %d is sleeping\n", timestamp, ph_info->id);
	else if (status == THINKING)
		printf("%lld %d is thinking\n", timestamp, ph_info->id);
	else if (status == DIED)
		printf("%lld %d died\n", timestamp, ph_info->id);
	if (status != DIED)
		sem_post_unwrap(ph_info->common->sem_out);
}

int	calc_interval(const t_philo_info *ph_info)
{
	const int	num_of_philo = ph_info->common->num_of_philo;
	const int	time_to_eat = ph_info->common->time_to_eat;
	const int	time_to_sleep = ph_info->common->time_to_sleep;
	const int	n = num_of_philo / 2;
	const int	time_to_think = time_to_eat * num_of_philo
					- (time_to_eat + time_to_sleep) * n;

	return (time_to_think / n);
}
