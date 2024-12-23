/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 01:32:05 by yliu              #+#    #+#             */
/*   Updated: 2024/12/23 16:44:52 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation_bonus.h"

static void	_safe_update_eat_count(t_philo *philo)
{
	sem_wait(philo->lock);
	philo->eat_count++;
	sem_post(philo->lock);
}

static void	_safe_update_last_meal(t_philo *philo, t_timeval *tp)
{
	sem_wait(philo->lock);
	philo->last_meal = *tp;
	sem_post(philo->lock);
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
