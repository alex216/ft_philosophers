/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:04:22 by yliu              #+#    #+#             */
/*   Updated: 2024/12/05 14:55:48 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation.h"

static t_result	_sleep(t_philo *philo)
{
	const size_t	time_to_sleep = philo->e->config.time_to_sleep;

	safe_print_msg(&philo->e->mutexes.is_running->lock, philo, SLEEPING);
	precise_msleep(time_to_sleep);
	return (SUCCESS);
}

static void	_think(t_philo *philo)
{
	safe_print_msg(&philo->e->mutexes.is_running->lock, philo, THINKING);
}

static size_t	_ret_init_wait_time(t_philo *philo)
{
	const size_t	num_philo = philo->e->config.num_philo;
	const size_t	id = philo->id;
	const size_t	time_to_eat = philo->e->config.time_to_eat;
	size_t			p;

	if (num_philo % 2 == 1)
	{
		if (id % 2 == 0)
			p = 2 * num_philo - id;
		else
			p = num_philo - id;
		return ((size_t)(p * time_to_eat / (num_philo - 1)));
	}
	else
	{
		if (id % 2 == 1)
			return (0);
		else
			return (time_to_eat);
	}
}

// check if the philo has died is done,
// after blocking action such as sleep and mutex lock
void	*philosopher(void *void_ptr)
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
		precise_msleep(philo->extra_sleep_time);
	}
	return (NULL);
}
