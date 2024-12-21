/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 16:18:22 by yliu              #+#    #+#             */
/*   Updated: 2024/12/21 16:39:37 by yliu             ###   ########.fr       */
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

void	*manager_func(void *void_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)void_ptr;
	while (!safe_is_philo_satisfied(philo))
	{
		if (_safe_is_philo_dead(philo))
		{
			safe_print_msg(philo, DIED);
			exit(PHILO_DIED);
		}
		usleep(INTERVAL);
	}
	return (NULL);
}
