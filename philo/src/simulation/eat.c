/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 20:48:31 by yliu              #+#    #+#             */
/*   Updated: 2024/11/28 16:44:37 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation.h"

t_result	eat(t_philo *philo)
{
	t_fork			*fork;
	const size_t	first_fork = philo->first_fork;
	const size_t	second_fork = philo->second_fork;

	fork = philo->e->mutexes.fork;
	return (safe_execute_with_two_mutexes(unsafe_eat, &fork[first_fork].lock,
			&fork[second_fork].lock, philo));
}
