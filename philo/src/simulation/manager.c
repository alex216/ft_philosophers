/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 03:52:59 by yliu              #+#    #+#             */
/*   Updated: 2024/11/23 15:30:17 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "simulation.h"

#define INTERVAL 1000

bool	safe_is_philo_dead(t_philo *philo)
{
	const size_t	id = philo->id;
	const size_t	time_to_die = philo->e->config.time_to_die;
	t_timeval		last_meal;
	t_timeval		now;

	receive_channel(philo->e->mutexes.last_meal[id - 1], &last_meal);
	gettimeofday(&now, NULL);
	return (difftimeval_ms(last_meal, now) >= (int)time_to_die);
}

void	*manager(void *void_ptr)
{
	t_manager	*manager;
	size_t		i;
	size_t		num_philo;

	manager = (t_manager *)void_ptr;
	num_philo = manager->e->config.num_philo;
	while (safe_is_game_running(manager->e))
	{
		i = 0;
		while (i < num_philo)
		{
			if (safe_is_philo_satisfied(&manager->e->philo[i]))
				;
			else if (safe_is_philo_dead(&manager->e->philo[i]))
			{
				send_channel(manager->e->mutexes.is_running, false);
				break ;
			}
			i++;
		}
		usleep(INTERVAL);
	}
	return (NULL);
}
