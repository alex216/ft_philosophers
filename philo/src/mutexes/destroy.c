/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:26:22 by yliu              #+#    #+#             */
/*   Updated: 2024/11/20 10:25:27 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mutexes.h"

void	destroy_mutexes(t_env *e)
{
	size_t			i;
	const size_t	num_of_philo = e->config.num_philo;

	i = 0;
	while (i < num_of_philo)
	{
		pthread_mutex_destroy(&e->mutexes.fork[i].lock);
		i++;
	}
}
