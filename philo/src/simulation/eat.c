/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 20:48:31 by yliu              #+#    #+#             */
/*   Updated: 2024/11/23 13:35:59 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation.h"

static size_t	get_right_fork(t_philo *philo)
{
	return (philo->id - 1);
}

static size_t	get_left_fork(t_philo *philo)
{
	return ((philo->id) % philo->e->config.num_philo);
}

t_result	eat(t_philo *philo)
{
	t_fork	*fork;
	size_t	first_fork;
	size_t	second_fork;

	fork = philo->e->mutexes.fork;
	if (philo->id % 2 == 0)
	{
		first_fork = get_right_fork(philo);
		second_fork = get_left_fork(philo);
	}
	else
	{
		first_fork = get_left_fork(philo);
		second_fork = get_right_fork(philo);
	}
	return (safe_execute_with_two_mutexes(unsafe_eat, &fork[first_fork].lock,
			&fork[second_fork].lock, philo));
}
