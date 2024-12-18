/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 01:03:50 by yliu              #+#    #+#             */
/*   Updated: 2024/12/18 18:42:32 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation_bonus.h"

static t_result	_create_philo_procs(t_env *e)
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
			while (i > 0)
			{
				kill(e->philo[--i].pid, SIGTERM);
				waitpid(e->philo[i].pid, NULL, 0);
			}
			return (FAILURE);
		}
		else if (pid == 0)
			exit(philosopher(&e->philo[i]));
		else
			e->philo[i].pid = pid;
		i++;
	}
	return (SUCCESS);
}

static t_result	_create_manager_proc(t_env *e)
{
	size_t	i;
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		i = 0;
		while (i > 0)
		{
			kill(e->philo[--i].pid, SIGTERM);
			waitpid(e->philo[i].pid, NULL, 0);
		}
		return (FAILURE);
	}
	else if (pid == 0)
		exit(manager(&e->manager));
	else
		e->manager.pid = pid;
	return (SUCCESS);
}

static t_result	_wait_pocs(t_env *e)
{
	size_t			i;
	const size_t	num_philo = e->config.num_philo;

	i = 0;
	while (i < num_philo)
	{
		if (waitpid(e->philo[i].pid, NULL, 0) < 0)
			return (FAILURE);
		i++;
	}
	if (waitpid(e->manager.pid, NULL, 0) < 0)
		return (FAILURE);
	return (SUCCESS);
}

t_result	start_simulation(t_env *e)
{
	return (_create_philo_procs(e) || _create_manager_proc(e));
}

t_result	wait_simulation_end(t_env *e)
{
	return (_wait_pocs(e));
}
