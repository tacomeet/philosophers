#include <pthread.h>
#include <string.h>
#include <unistd.h>

#include "include/philo.h"
#include "include/utils.h"

static bool	parse_args(int argc, char **argv, t_info *info);

bool	init_program(int argc, char **argv, t_info *info, t_philo_info *ph_info)
{
	int	i;

	if (!parse_args(argc, argv, info))
		return (false);
	info->time_to_think = calc_time_to_think(info);
	i = -1;
	while (++i < info->num_of_philo)
		init_philo_info(&ph_info[i], info, i + 1);
	info->simulation_finished = false;
	info->satisfied_philo = 0;
	return (init_mutexes(&info->mutex, 1)
		&& init_mutexes(info->forks, info->num_of_philo));
}

bool	parse_args(int argc, char **argv, t_info *info)
{
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;

	info->num_of_meal = -1;
	if (!((argc == 5 || argc == 6)
			&& atoi_strict(argv[1], &info->num_of_philo)
			&& 1 <= info->num_of_philo && info->num_of_philo <= MAX_NUM_OF_PHILO
			&& atoi_strict(argv[2], &time_to_die)
			&& time_to_die >= MIN_MSEC
			&& atoi_strict(argv[3], &time_to_eat)
			&& time_to_eat >= MIN_MSEC
			&& atoi_strict(argv[4], &time_to_sleep)
			&& time_to_sleep >= MIN_MSEC
			&& (argc == 5 || (
					atoi_strict(argv[5], &info->num_of_meal)
					&& info->num_of_meal >= 0))))
	{
		ft_putstr_fd(ERR_INVALID_ARGUMENT, STDERR_FILENO);
		return (false);
	}
	info->time_to_die = (long long)time_to_die * 1000;
	info->time_to_eat = (long long)time_to_eat * 1000;
	info->time_to_sleep = (long long)time_to_sleep * 1000;
	return (true);
}

bool	init_philos(t_info *info, t_philo_info *ph_info, pthread_t *philos)
{
	int	i;

	i = -1;
	info->start = get_usec();
	while (++i < info->num_of_philo)
	{
		ph_info[i].last_meal_time = info->start;
		if (pthread_create(&philos[i], NULL, do_philo, &ph_info[i]) != 0)
		{
			ft_putstr_fd(ERR_PTHREAD_CREATE, STDERR_FILENO);
			destroy_program(info, philos, i);
			return (false);
		}
	}
	return (true);
}

bool	init_mutexes(pthread_mutex_t *mutexes, int mutex_num)
{
	int	i;

	i = -1;
	while (++i < mutex_num)
	{
		if (pthread_mutex_init(&mutexes[i], NULL) != 0)
		{
			ft_putstr_fd(ERR_MUTEX_INIT, STDERR_FILENO);
			destroy_mutexes(mutexes, i);
			return (false);
		}
	}
	return (true);
}

void	init_philo_info(t_philo_info *ph_info, t_info *info, int id)
{
	ph_info->id = id;
	ph_info->left = id - 1;
	ph_info->right = id % info->num_of_philo;
	ph_info->last_meal_time = 0;
	ph_info->left_meal_cnt = info->num_of_meal;
	ph_info->common = info;
}
