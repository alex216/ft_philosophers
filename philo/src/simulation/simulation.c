/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:27:06 by yliu              #+#    #+#             */
/*   Updated: 2024/11/23 16:12:34 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation.h"

static t_result	_create_threads(t_env *e)
{
	size_t			i;
	const size_t	num_philo = e->config.num_philo;

	i = 0;
	while (i < num_philo)
	{
		if (pthread_create(&e->philo[i].thread, NULL, &philosopher,
				&e->philo[i]) != 0)
			return (FAILURE);
		i++;
	}
	if (pthread_create(&e->manager.thread, NULL, manager, &e->manager) != 0)
		return (FAILURE);
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
	return (_create_threads(e));
}

t_result	wait_simulation_end(t_env *e)
{
	return (_join_threads(e));
}
