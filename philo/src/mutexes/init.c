/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:28:35 by yliu              #+#    #+#             */
/*   Updated: 2024/11/28 11:30:40 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mutexes.h"

t_result	init_mutexes(t_env *e)
{
	size_t			i;
	const size_t	num_of_philo = e->config.num_philo;

	i = 0;
	while (i < num_of_philo)
	{
		if (pthread_mutex_init(&e->mutexes.fork[i].lock, NULL) != 0)
		{
			while (i > 0)
			{
				i--;
				pthread_mutex_destroy(&e->mutexes.fork[i].lock);
			}
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}
