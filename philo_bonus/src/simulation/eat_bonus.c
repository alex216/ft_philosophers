/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 01:32:05 by yliu              #+#    #+#             */
/*   Updated: 2024/12/21 19:44:56 by yliu             ###   ########.fr       */
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

static void	_safe_update_last_meal(t_philo *philo, t_timeval *tp)
{
	send_channel(philo->e->semaphores.last_meal[philo->id - 1], tp);
}

static t_result	_unsafe_eat(void *void_ptr)
{
	t_philo		*philo;
	t_timeval	tp;
	size_t		time_to_eat;

	philo = (t_philo *)void_ptr;
	time_to_eat = philo->e->config.time_to_eat;
	gettimeofday(&tp, NULL);
	safe_print_msg(philo, EATING);
	_safe_update_last_meal(philo, &tp);
	_safe_update_eat_count(philo);
	precise_msleep(time_to_eat);
	return (SUCCESS);
}

t_result	eat(t_philo *philo)
{
	sem_t	*fork;
	sem_t	*waiter;

	// fork resource deadlock not considered yet
	waiter = philo->e->semaphores.waiter;
	fork = philo->e->semaphores.forks;
	sem_wait(waiter);
	sem_wait(fork);
	safe_print_msg(philo, HAS_FORK);
	sem_wait(fork);
	safe_print_msg(philo, HAS_FORK);
	sem_post(waiter);
	_unsafe_eat(philo);
	sem_post(fork);
	sem_post(fork);
	return (SUCCESS);
}
