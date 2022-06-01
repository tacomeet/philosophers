#include <stdio.h>
#include <signal.h>
#include <errno.h>

#include "include/philo.h"
#include "include/utils.h"

bool	destroy_program(t_info *info, pid_t *philos, int num_of_philo)
{
	int	i;

	i = -1;
	while (++i < num_of_philo)
	{
		if (kill(philos[i], SIGKILL) != 0)
		{
			perror("kill");
			if (errno == ESRCH)
				continue ;
			printf(ERR_KILL);
			return (false);
		}
	}
	if (sem_close(info->forks) != 0 || sem_close(info->sem) != 0)
//	if (sem_close(info->forks) != 0 || sem_close(info->sem) != 0 || sem_close(info->sem_out) != 0)
	{
		printf(ERR_SEM_CLOSE);
		return (false);
	}
	if (sem_unlink(SEM_FORKS_ID) != 0 || sem_unlink(SEM_CHECK_ID) != 0)
	{
		printf(ERR_SEM_UNLINK);
		return (false);
	}
	return (true);
}
