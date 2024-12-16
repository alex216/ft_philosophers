/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:46:55 by yliu              #+#    #+#             */
/*   Updated: 2024/12/15 10:17:22 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init_bonus.h"

// t_timeval can be shallow copied because it is a struct of two longs
static void	_init_philo(t_env *e)
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

static t_result	close_all_channels(t_env *e, size_t i)
{
	while (i > 0)
	{
		close_channel(e->semaphores.eat_count[--i]);
		close_channel(e->semaphores.last_meal[i]);
	}
	return (FAILURE);
}

static t_result	init_semaphore_of_philo(t_env *e)
{
	size_t			i;
	size_t			eat_count;
	const size_t	num_of_philo = e->config.num_philo;

	eat_count = 0;
	i = 0;
	while (i < num_of_philo)
	{
		e->semaphores.eat_count[i] = open_channel("eat_count", sizeof(size_t));
		if (e->semaphores.eat_count[i] == NULL)
			return (close_all_channels(e, i));
		send_channel(e->semaphores.eat_count[i], &eat_count);
		e->semaphores.last_meal[i] = open_channel("last_meal",
				sizeof(t_timeval));
		if (e->semaphores.last_meal[i] == NULL)
		{
			close_channel(e->semaphores.eat_count[i]);
			return (close_all_channels(e, i));
		}
		send_channel(e->semaphores.last_meal[i], &e->start_at);
		i++;
	}
	return (SUCCESS);
}

static t_result	_init_semaphore(t_env *e)
{
	bool	data;

	e->semaphores.is_running = open_channel("is_running", sizeof(bool));
	if (e->semaphores.is_running == NULL)
		return (FAILURE);
	data = true;
	send_channel(e->semaphores.is_running, &data);
	if (init_semaphore_of_philo(e) == FAILURE)
	{
		close_channel(e->semaphores.is_running);
		return (FAILURE);
	}
	return (SUCCESS);
}

t_result	init(t_env *e)
{
	t_timeval	start_at;
	const int	time_to_create_thread = 20;

	gettimeofday(&start_at, NULL);
	e->start_at = timeval_add_ms(start_at, time_to_create_thread);
	_init_philo(e);
	e->manager.e = e;
	return (_init_semaphore(e));
}
