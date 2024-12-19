/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 03:52:59 by yliu              #+#    #+#             */
/*   Updated: 2024/12/19 12:48:29 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include "simulation_bonus.h"

#define INTERVAL 1000

static bool	_safe_is_philo_dead(t_philo *philo)
{
	const size_t	id = philo->id;
	const size_t	time_to_die = philo->e->config.time_to_die;
	t_timeval		last_meal;
	t_timeval		now;

	receive_channel(philo->e->semaphores.last_meal[id - 1], &last_meal);
	gettimeofday(&now, NULL);
	return (difftimeval_ms(last_meal, now) >= (int)time_to_die);
}

static t_result	_roll_call(t_manager *manager, bool *false_bool)
{
	size_t	i;
	size_t	satisfied_philo;
	size_t	num_philo;

	num_philo = manager->e->config.num_philo;
	i = 0;
	satisfied_philo = 0;
	while (i < num_philo)
	{
		if (safe_is_philo_satisfied(&manager->e->philo[i]))
			satisfied_philo++;
		else if (_safe_is_philo_dead(&manager->e->philo[i]))
		{
			send_channel(manager->e->semaphores.is_running, false_bool);
			unsafe_print_msg(&manager->e->philo[i], DIED);
			return (FAILURE);
		}
		i++;
	}
	if (satisfied_philo == num_philo)
		send_channel(manager->e->semaphores.is_running, false_bool);
	return (SUCCESS);
}

int	manager(void *void_ptr)
{
	t_manager	*manager;
	bool		false_bool;

	false_bool = false;
	manager = (t_manager *)void_ptr;
	precise_msleep_until(manager->e->start_at);
	while (safe_is_game_running(manager->e))
	{
		if (_roll_call(manager, &false_bool) == FAILURE)
			return (0);
		usleep(INTERVAL);
	}
	return (0);
}
