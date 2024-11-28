/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 13:16:26 by yliu              #+#    #+#             */
/*   Updated: 2024/11/28 13:52:58 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mutexes.h"

bool	safe_is_philo_satisfied(t_philo *philo)
{
	size_t			eat_count;
	const size_t	id = philo->id;
	const size_t	min_eat_count = philo->e->config.min_eat_count;

	receive_channel(philo->e->mutexes.eat_count[id - 1], &eat_count);
	if (min_eat_count == 0)
		return (false);
	else
		return (eat_count >= min_eat_count);
}

bool	safe_is_game_running(t_env *e)
{
	bool	is_running;

	receive_channel(e->mutexes.is_running, &is_running);
	return (is_running);
}

void	safe_update_last_meal(t_philo *philo, t_timeval *tp)
{
	send_channel(philo->e->mutexes.last_meal[philo->id - 1], tp);
}
