/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:04:22 by yliu              #+#    #+#             */
/*   Updated: 2024/11/24 21:59:31 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation.h"

static t_result	_sleep(t_philo *philo)
{
	if (print_msg(philo, SLEEPING) == FAILURE)
		return (FAILURE);
	precise_msleep(philo->e->config.time_to_sleep);
	return (SUCCESS);
}

static t_result	_think(t_philo *philo)
{
	return (print_msg(philo, THINKING));
}

void	*philosopher(void *void_ptr)
{
	t_philo	*philo;

	philo = void_ptr;
	gettimeofday(&philo->start_at, NULL);
	safe_update_last_meal(philo, &philo->start_at);
	while (true)
	{
		if (_think(philo) == FAILURE)
			break ;
		if (eat(philo) == FAILURE)
			break ;
		if (safe_is_philo_satisfied(philo))
			break ;
		if (_sleep(philo) == FAILURE)
			break ;
	}
	return (NULL);
}
