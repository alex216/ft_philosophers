/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 01:03:50 by yliu              #+#    #+#             */
/*   Updated: 2024/12/07 01:03:56 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation_bonus.h"

static t_result	_create_philo_threads(t_env *e)
{
	size_t			i;
	const size_t	num_philo = e->config.num_philo;

	i = 0;
	while (i < num_philo)
	{
		if (pthread_create(&e->philo[i].thread, NULL, &philosopher,
				&e->philo[i]) != 0)
		{
			while (i > 0)
			{
				i--;
				pthread_join(e->philo[i].thread, NULL);
			}
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

static t_result	_create_manager_threads(t_env *e)
{
	size_t	i;

	i = 0;
	if (pthread_create(&e->manager.thread, NULL, manager, &e->manager) != 0)
	{
		while (i > 0)
		{
			i--;
			pthread_join(e->philo[i].thread, NULL);
		}
		return (FAILURE);
	}
	return (SUCCESS);
}

static t_result	_join_threads(t_env *e)
{
	size_t			i;
	const size_t	num_philo = e->config.num_philo;

	i = 0;
	while (i < num_philo)
	{
		if (pthread_join(e->philo[i].thread, NULL) != 0)
			return (FAILURE);
		i++;
	}
	pthread_join(e->manager.thread, NULL);
	return (SUCCESS);
}

t_result	start_simulation(t_env *e)
{
	return (_create_philo_threads(e) || _create_manager_threads(e));
}

t_result	wait_simulation_end(t_env *e)
{
	return (_join_threads(e));
}
