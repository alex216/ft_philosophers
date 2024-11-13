/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:28:35 by yliu              #+#    #+#             */
/*   Updated: 2024/11/15 20:53:43 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mutexes.h"

t_result	init_mutexes(t_env *e)
{
	size_t			i;
	const size_t	num_of_philo = e->config.num_philo;

	if (pthread_mutex_init(&e->mutexes.state.lock, NULL) != 0)
		return (FAILURE);
	e->mutexes.state.is_dead = false;
	i = 0;
	while (i < num_of_philo)
	{
		if (pthread_mutex_init(&e->mutexes.fork[i].lock, NULL) != 0)
			return (FAILURE);
		if (pthread_mutex_init(&e->mutexes.eat_count[i].lock, NULL) != 0)
			return (FAILURE);
		e->mutexes.eat_count[i].count = 0;
		if (pthread_mutex_init(&e->mutexes.last_meal[i].lock, NULL) != 0)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}
