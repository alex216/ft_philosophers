/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:04:22 by yliu              #+#    #+#             */
/*   Updated: 2024/11/16 03:48:38 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation.h"

static void	_sleep(t_philo *philo)
{
	unsafe_printf(philo, SLEEPING, 0);
	precise_msleep(philo->e->config.time_to_sleep);
}

static void	think(t_philo *philo)
{
	(void)philo;
	unsafe_printf(philo, THINKING, 0);
}

void	*philosopher(void *void_ptr)
{
	t_philo			*philo;
	size_t			id;

	philo = void_ptr;
	id = philo->id;
	safe_execute(unsafe_set_time,
		&philo->e->mutexes.last_meal[id].lock,
		&philo->e->mutexes.last_meal[id].timestamp);
	while (true)
	{
		eat(philo);
		_sleep(philo);
		think(philo);
	}
	return (NULL);
}
