/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:04:22 by yliu              #+#    #+#             */
/*   Updated: 2024/11/30 17:48:46 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation.h"

static t_result	_sleep(t_philo *philo)
{
	const size_t	time_to_sleep = philo->e->config.time_to_sleep;

	print_msg(philo, SLEEPING);
	return (sleep_with_check(philo, time_to_sleep));
}

static void	_think(t_philo *philo)
{
	print_msg(philo, THINKING);
}

static size_t	_ret_init_wait_time(t_philo *philo)
{
	const size_t	num_philo = philo->e->config.num_philo;
	const size_t	id = philo->id;
	const size_t	time_to_eat = philo->e->config.time_to_eat;
	size_t			p;
	size_t			ans;

	if (num_philo % 2 == 1)
	{
		if (id % 2 == 0)
			p = 2 * num_philo - id;
		else
			p = num_philo - id;
		ans = (size_t)(p * time_to_eat / (num_philo - 1));
		return (ans);
	}
	else
	{
		if (id % 2 == 1)
			return (0);
		else
			return (time_to_eat);
	}
}

static size_t	get_right_fork(t_philo *philo)
{
	return (philo->id - 1);
}

static size_t	get_left_fork(t_philo *philo)
{
	return ((philo->id) % philo->e->config.num_philo);
}

void	set_fork(t_philo *philo)
{
	if (philo->id == 1)
	{
		philo->first_fork = get_right_fork(philo);
		philo->second_fork = get_left_fork(philo);
	}
	else
	{
		philo->first_fork = get_left_fork(philo);
		philo->second_fork = get_right_fork(philo);
	}
}

// check if the philo has died is done,
// after blocking action such as sleep and mutex lock
void	*philosopher(void *void_ptr)
{
	t_philo	*philo;

	philo = void_ptr;
	set_fork(philo);
	precise_msleep_until(philo->e->start_at);
	_think(philo);
	if (sleep_with_check(philo, _ret_init_wait_time(philo)) == FAILURE)
		return (NULL);
	while (true)
	{
		if (eat(philo) == FAILURE)
			break ;
		if (safe_is_philo_satisfied(philo))
			break ;
		if (_sleep(philo) == FAILURE)
			break ;
		_think(philo);
	}
	return (NULL);
}
