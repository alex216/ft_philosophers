/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:46:55 by yliu              #+#    #+#             */
/*   Updated: 2024/11/16 03:38:28 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

void	_init_philo(t_env *e)
{
	size_t	i;

	i = 0;
	while (i < e->config.num_philo)
	{
		e->philo[i].id = i + 1;
		e->philo[i].e = e;
		i++;
	}
}

t_result	init(t_env *e)
{
	_init_philo(e);
	if (init_mutexes(e) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
