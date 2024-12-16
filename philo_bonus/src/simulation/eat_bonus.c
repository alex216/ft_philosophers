/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 01:32:05 by yliu              #+#    #+#             */
/*   Updated: 2024/12/15 10:26:25 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation_bonus.h"

static void	_safe_update_eat_count(t_philo *philo)
{
	size_t			eat_count;
	const size_t	id = philo->id;

	receive_channel(philo->e->semaphores.eat_count[id - 1], &eat_count);
	eat_count++;
	send_channel(philo->e->semaphores.eat_count[id - 1], &eat_count);
}

static t_result	_unsafe_eat(void *void_ptr)
{
	t_philo		*philo;
	t_timeval	tp;
	size_t		time_to_eat;

	philo = (t_philo *)void_ptr;
	time_to_eat = philo->e->config.time_to_eat;
	safe_print_msg(philo->e->semaphores.is_running, philo, EATING);
	gettimeofday(&tp, NULL);
	safe_update_last_meal(philo, &tp);
	_safe_update_eat_count(philo);
	precise_msleep(time_to_eat);
	return (SUCCESS);
}

t_result	eat(t_philo *philo)
{
	t_result	result;
	sem_t		*fork;

	fork = philo->e->semaphores.forks;
	result = FAILURE;
	sem_wait(fork);
	if (safe_is_game_running(philo->e))
	{
		safe_print_msg(philo->e->semaphores.is_running, philo, HAS_FORK);
		sem_wait(fork);
		if (safe_is_game_running(philo->e))
		{
			safe_print_msg(philo->e->semaphores.is_running, philo, HAS_FORK);
			result = _unsafe_eat(philo);
		}
		sem_post(fork);
	}
	sem_post(fork);
	return (result);
}
