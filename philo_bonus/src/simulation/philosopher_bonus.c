/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 01:24:36 by yliu              #+#    #+#             */
/*   Updated: 2024/12/19 00:22:05 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation_bonus.h"

static t_result	_sleep(t_philo *philo)
{
	const size_t	time_to_sleep = philo->e->config.time_to_sleep;

	safe_print_msg(philo->e->semaphores.is_running, philo, SLEEPING);
	precise_msleep(time_to_sleep);
	return (SUCCESS);
}

static void	_think(t_philo *philo)
{
	safe_print_msg(philo->e->semaphores.is_running, philo, THINKING);
}

static size_t	_ret_init_wait_time(t_philo *philo)
{
	const size_t	num_philo = philo->e->config.num_philo;
	const size_t	id = philo->id;
	const size_t	time_to_eat = philo->e->config.time_to_eat;
	const int		k = num_philo / 2;

	if (k == 0)
		return (0);
	return (time_to_eat * (id - 1) / k);
}

int	philosopher(void *void_ptr)
{
	t_philo	*philo;

	philo = void_ptr;
	precise_msleep_until(philo->e->start_at);
	_think(philo);
	precise_msleep(_ret_init_wait_time(philo));
	while (true)
	{
		if (eat(philo) == FAILURE)
			break ;
		if (safe_is_philo_satisfied(philo))
			break ;
		if (_sleep(philo) == FAILURE)
			break ;
		_think(philo);
		// precise_msleep(philo->extra_sleep_time);
	}
	return (0);
}
