/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 01:03:50 by yliu              #+#    #+#             */
/*   Updated: 2024/12/23 16:58:44 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation_bonus.h"
#define ANY_CHILD_PROCESS -1
#define ALL_CHILD_PROCESS 0

static t_result	_philosopher_child_proc(t_philo *philo)
{
	if (pthread_create(&philo->philo_tid, NULL, philosopher_func, philo) != 0)
		return (FAILURE);
	if (pthread_create(&philo->manager_tid, NULL, manager_func, philo) != 0)
		return (FAILURE);
	if (pthread_join(philo->philo_tid, NULL) != 0)
		return (FAILURE);
	if (pthread_join(philo->philo_tid, NULL) != 0)
		return (FAILURE);
	return (SUCCESS);
}

t_result	start_simulation(t_env *e)
{
	size_t			i;
	const size_t	num_philo = e->config.num_philo;
	pid_t			pid;

	i = 0;
	while (i < num_philo)
	{
		pid = fork();
		if (pid < 0)
		{
			kill(ALL_CHILD_PROCESS, SIGTERM);
			return (FAILURE);
		}
		else if (pid == 0)
			exit(_philosopher_child_proc(&e->philo[i]));
		else
			e->philo[i].pid = pid;
		i++;
	}
	return (SUCCESS);
}

// if use kill(ALL_CHILD_PROCESS, SIGTERM)
// msg will appear so kill each proc one by one.
static void	kill_all_child_processes(t_env *e)
{
	size_t	i;

	i = 0;
	while (i < e->config.num_philo)
	{
		kill(e->philo[i].pid, SIGTERM);
		i++;
	}
}

t_result	wait_simulation_end(t_env *e)
{
	pid_t	wpid;
	int		exit_status;

	while (true)
	{
		wpid = waitpid(ANY_CHILD_PROCESS, &exit_status, 0);
		if (wpid == -1)
		{
			if (errno == ECHILD)
				break ;
			return (FAILURE);
		}
		if (WIFEXITED(exit_status) && WEXITSTATUS(exit_status) == PHILO_DIED)
			kill_all_child_processes(e);
	}
	return (SUCCESS);
}
