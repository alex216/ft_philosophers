/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:26:22 by yliu              #+#    #+#             */
/*   Updated: 2024/11/15 20:54:01 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mutexes.h"

void	destroy_mutexes(t_env *e)
{
	size_t			i;
	const size_t	num_of_philo = e->config.num_philo;

	i = 0;
	pthread_mutex_destroy(&e->mutexes.state.lock);
	while (i < num_of_philo)
	{
		pthread_mutex_destroy(&e->mutexes.fork[i].lock);
		pthread_mutex_destroy(&e->mutexes.eat_count[i].lock);
		pthread_mutex_destroy(&e->mutexes.last_meal[i].lock);
		i++;
	}
}
