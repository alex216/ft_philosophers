/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:04:22 by yliu              #+#    #+#             */
/*   Updated: 2024/11/23 13:18:28 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation.h"

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

void	*philosopher(void *void_ptr)
{
	t_philo	*philo;

	philo = void_ptr;
	gettimeofday(&philo->start_at, NULL);
	while (true)
	{
		eat(philo);
		if (safe_is_philo_satisfied(philo))
			break ;
		_sleep(philo);
		_think(philo);
	}
	return (NULL);
}
