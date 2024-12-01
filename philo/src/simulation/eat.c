/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 20:48:31 by yliu              #+#    #+#             */
/*   Updated: 2024/12/01 11:41:39 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation.h"

static void	safe_update_eat_count(t_philo *philo)
{
	size_t			eat_count;
	const size_t	id = philo->id;

	receive_channel(philo->e->mutexes.eat_count[id - 1], &eat_count);
	eat_count++;
	send_channel(philo->e->mutexes.eat_count[id - 1], &eat_count);
}

static t_result	unsafe_eat(void *void_ptr)
{
	t_philo		*philo;
	t_timeval	tp;
	size_t		time_to_eat;

	philo = (t_philo *)void_ptr;
	time_to_eat = philo->e->config.time_to_eat;
	safe_print_msg(&philo->e->mutexes.is_running->lock, philo, EATING);
	gettimeofday(&tp, NULL);
	safe_update_last_meal(philo, &tp);
	safe_update_eat_count(philo);
	precise_msleep(time_to_eat);
	return (SUCCESS);
}

static t_result	safe_execute_with_two_mutexes(t_unsafe_func f, t_mutex *m1,
		t_mutex *m2, void *param)
{
	t_result	result;
	t_philo		*philo;

	philo = (t_philo *)param;
	result = FAILURE;
	pthread_mutex_lock(m1);
	if (safe_is_game_running(philo->e))
	{
		safe_print_msg(&philo->e->mutexes.is_running->lock, philo, HAS_FORK);
		pthread_mutex_lock(m2);
		if (safe_is_game_running(philo->e))
		{
			safe_print_msg(&philo->e->mutexes.is_running->lock, philo,
				HAS_FORK);
			result = f(philo);
		}
		pthread_mutex_unlock(m2);
	}
	pthread_mutex_unlock(m1);
	return (result);
}

t_result	eat(t_philo *philo)
{
	t_fork			*fork;
	const size_t	first_fork = philo->first_fork;
	const size_t	second_fork = philo->second_fork;

	fork = philo->e->mutexes.fork;
	return (safe_execute_with_two_mutexes(unsafe_eat, &fork[first_fork].lock,
			&fork[second_fork].lock, philo));
}
