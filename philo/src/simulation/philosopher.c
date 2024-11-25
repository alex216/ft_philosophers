/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:04:22 by yliu              #+#    #+#             */
/*   Updated: 2024/11/25 18:39:47 by yliu             ###   ########.fr       */
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

static void	_init_wait(t_philo *philo)
{
	const size_t	num_philo = philo->e->config.num_philo;
	const size_t	id = philo->id;
	const size_t	time_to_eat = philo->e->config.time_to_eat;
	size_t			p;

	if (num_philo % 2 == 1)
	{
		if (id % 2 == 1)
			p = 2 * num_philo - id;
		else
			p = num_philo - id;
		precise_msleep((size_t)(p * time_to_eat / (num_philo - 1)));
	}
	else
	{
		if (id % 2 == 1)
			precise_msleep(0);
		else
			precise_msleep(time_to_eat);
	}
}

void	*philosopher(void *void_ptr)
{
	t_philo	*philo;

	philo = void_ptr;
	gettimeofday(&philo->start_at, NULL);
	safe_update_last_meal(philo, &philo->start_at);
	if (_think(philo) == FAILURE)
		return (NULL);
	_init_wait(philo);
	while (true)
	{
		if (eat(philo) == FAILURE)
			break ;
		if (safe_is_philo_satisfied(philo))
			break ;
		if (_sleep(philo) == FAILURE)
			break ;
		if (_think(philo) == FAILURE)
			break ;
	}
	return (NULL);
}
