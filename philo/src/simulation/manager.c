/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 03:52:59 by yliu              #+#    #+#             */
/*   Updated: 2024/11/23 13:18:17 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "simulation.h"

#define INTERVAL 1000

void	*manager(void *void_ptr)
{
	t_manager	*manager;
	size_t		i;
	size_t		num_philo;
	bool		some_one_is_alive;

	manager = (t_manager *)void_ptr;
	num_philo = manager->e->config.num_philo;
	while (safe_is_game_running(manager->e))
	{
		i = 0;
		some_one_is_alive = false;
		while (i < num_philo)
		{
			if (safe_is_philo_dead(&manager->e->philo[i]))
			{
				send_channel(manager->e->mutexes.is_running, false);
				break ;
			}
			else
				some_one_is_alive = true;
			i++;
		}
		if (!some_one_is_alive)
			break ;
		usleep(INTERVAL);
	}
	return (NULL);
}
