/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsafe_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 22:48:32 by yliu              #+#    #+#             */
/*   Updated: 2024/11/23 16:18:20 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mutexes.h"

static void	safe_update_eat_count(t_philo *philo)
{
	size_t			eat_count;
	const size_t	id = philo->id;

	receive_channel(philo->e->mutexes.eat_count[id - 1], &eat_count);
	eat_count++;
	send_channel(philo->e->mutexes.eat_count[id - 1], &eat_count);
}

t_result	unsafe_eat(void *void_ptr)
{
	t_philo		*philo;
	t_timeval	tp;

	philo = (t_philo *)void_ptr;
	if (print_msg(philo, EATING) == FAILURE)
		return (FAILURE);
	gettimeofday(&tp, NULL);
	safe_update_last_meal(philo, &tp);
	precise_msleep(philo->e->config.time_to_eat);
	safe_update_eat_count(philo);
	return (SUCCESS);
}
