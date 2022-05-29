#ifndef PHILO_H
# define PHILO_H

# include <stdbool.h>

# define MAX_NUM_OF_PHILO 200

typedef struct s_info {
	int				num_of_philo;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				num_of_meal;
	long			start;
	pthread_mutex_t	forks[MAX_NUM_OF_PHILO];
	pthread_mutex_t	mutex;
	bool			simulation_finished;
	int				satisfied_philo;
}	t_info;

typedef struct s_philo_info {
	int		id;
	int		left;
	int		right;
	long	last_meal_time;
	int		left_meal_cnt;
	t_info	*common;
}	t_philo_info;

typedef enum e_philo_status {
	TAKEN_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DIED,
}	t_philo_status;

bool	init_program(
			int argc, char **argv, t_info *info, t_philo_info *ph_info);
bool	init_philos(t_info *info, t_philo_info *ph_info, pthread_t *philos);
bool	init_mutexes(pthread_mutex_t *mutexes, int mutex_num);
void	init_philo_info(t_philo_info *ph_info, t_info *info, int id);

void	print_log(const t_philo_info *info, t_philo_status status);

// philo.c
void	*philosopher(void *arg_);
void	ph_wait(long start, long wait_time);

// monitor.c
bool	is_starved(t_info *info, t_philo_info *ph_info);
bool	all_satisfied(t_info *info);
void	increment_satisfied_philo(t_info *info);
int		get_satisfied_philo(t_info *info);
void	set_last_meal_time(t_philo_info *ph_info, long last_meal_time);

// ph_grab_forks.c
bool	ph_grab_forks(const t_philo_info *ph_info, bool *first_forks);

// destroy.c
bool	destroy_program(t_info *info, pthread_t *philos, int num_of_philo);
bool	destroy_mutexes(pthread_mutex_t *mutexes, int mutex_num);

#endif //PHILO_H
