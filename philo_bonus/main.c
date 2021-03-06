#include <stdlib.h>
#include <signal.h>

#include "include/philo.h"

static bool	check_philo_status(t_info *info, pid_t *philos);

int	main(int argc, char **argv)
{
	t_info			info;
	pid_t			philos[MAX_NUM_OF_PHILO];

	if (!init_program(argc, argv, &info))
		return (EXIT_FAILURE);
	init_philos(&info, philos);
	if (!check_philo_status(&info, philos))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static bool	check_philo_status(t_info *info, pid_t *philos)
{
	int		status;
	int		i;
	bool	someone_died;
	int		exit_status;

	i = 0;
	someone_died = false;
	while (i++ < info->num_of_philo)
	{
		waitpid(-1, &status, 0);
		exit_status = WEXITSTATUS(status);
		if (!someone_died
			&& exit_status != ES_SATISFIED
			&& exit_status != ES_ERR)
		{
			someone_died = true;
			if (!destroy_program(info, philos, info->num_of_philo))
				return (false);
		}
	}
	if (!someone_died && !destroy_program(info, philos, info->num_of_philo))
		return (false);
	return (true);
}
