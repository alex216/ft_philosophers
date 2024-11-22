/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:04:22 by yliu              #+#    #+#             */
/*   Updated: 2024/11/22 23:46:49 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation.h"

static bool	_is_philo_satisfied(t_philo *philo)
{
	size_t			eat_count;
	const size_t	id = philo->id;
	const size_t	min_eat_count = philo->e->config.minimum_eat_count;

	receive_channel(philo->e->mutexes.eat_count[id - 1], &eat_count);
	return (eat_count >= min_eat_count);
}

static void	_sleep(t_philo *philo)
{
	unsafe_printf(philo, SLEEPING, 0);
	precise_msleep(philo->e->config.time_to_sleep);
}

static void	_think(t_philo *philo)
{
	(void)philo;
	unsafe_printf(philo, THINKING, 0);
}

static void	_set_start_time(t_philo *philo)
{
	t_timeval		now;
	const size_t	id = philo->id;

	gettimeofday(&now, NULL);
	send_channel(philo->e->mutexes.last_meal[id - 1], &now);
}

void	*philosopher(void *void_ptr)
{
	t_philo	*philo;

	philo = void_ptr;
	_set_start_time(philo);
	while (true)
	{
		eat(philo);
		if (_is_philo_satisfied(philo))
			break ;
		_sleep(philo);
		_think(philo);
	}
	return (NULL);
}
