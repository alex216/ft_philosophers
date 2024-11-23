/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:46:55 by yliu              #+#    #+#             */
/*   Updated: 2024/11/23 15:46:12 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "channel.h"
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

static t_result	_init_channels(t_env *e)
{
	size_t			i;
	const size_t	num_of_philo = e->config.num_philo;
	bool			data;
	size_t			eat_count;

	eat_count = 0;
	e->mutexes.is_running = construct_channel(sizeof(bool));
	if (e->mutexes.is_running == NULL)
		return (FAILURE);
	data = true;
	send_channel(e->mutexes.is_running, &data);
	i = 0;
	while (i < num_of_philo)
	{
		e->mutexes.eat_count[i] = construct_channel(sizeof(size_t));
		if (e->mutexes.eat_count[i] == NULL)
			return (FAILURE);
		send_channel(e->mutexes.eat_count[i], &eat_count);
		e->mutexes.last_meal[i] = construct_channel(sizeof(t_timeval));
		if (e->mutexes.last_meal[i] == NULL)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

static void	_init_manager(t_env *e)
{
	e->manager.e = e;
}

t_result	init(t_env *e)
{
	_init_philo(e);
	_init_manager(e);
	if (init_mutexes(e) == FAILURE)
		return (FAILURE);
	if (_init_channels(e) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
