/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 01:24:36 by yliu              #+#    #+#             */
/*   Updated: 2024/12/21 20:29:50 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation_bonus.h"

static t_result	_sleep(t_philo *philo)
{
	const size_t	time_to_sleep = philo->e->config.time_to_sleep;

	safe_print_msg(philo, SLEEPING);
	precise_msleep(time_to_sleep);
	return (SUCCESS);
}

static t_result	_think(t_philo *philo)
{
	return (safe_print_msg(philo, THINKING));
}

static int	_ret_init_wait_time(t_philo *philo)
{
	const size_t	num_philo = philo->e->config.num_philo;
	const size_t	id = philo->id;
	const size_t	time_to_eat = philo->e->config.time_to_eat;
	const int		k = num_philo / 2;

	return (time_to_eat * (id - 1) / k);
}

void	*philosopher_func(void *void_ptr)
{
	t_philo	*philo;

	philo = void_ptr;
	precise_msleep_until(philo->e->start_at);
	_think(philo);
	precise_msleep(_ret_init_wait_time(philo));
	while (true)
	{
		eat(philo);
		if (safe_is_philo_satisfied(philo))
			break ;
		_sleep(philo);
		_think(philo);
		precise_msleep(philo->e->extra_sleep_time);
	}
	return (NULL);
}
