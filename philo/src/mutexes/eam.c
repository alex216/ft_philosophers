/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eam.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:44:12 by yliu              #+#    #+#             */
/*   Updated: 2024/11/28 13:19:34 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mutexes.h"

void	safe_execute(t_unsafe_func f, pthread_mutex_t *mutex, void *param)
{
	pthread_mutex_lock(mutex);
	f(param);
	pthread_mutex_unlock(mutex);
}

t_result	safe_execute_with_two_mutexes(t_unsafe_func f, pthread_mutex_t *m1,
		pthread_mutex_t *m2, void *param)
{
	t_result	result;
	t_philo		*philo;

	philo = (t_philo *)param;
	result = FAILURE;
	pthread_mutex_lock(m1);
	if (safe_is_game_running(philo->e))
	{
		print_msg(philo, HAS_FORK);
		pthread_mutex_lock(m2);
		if (safe_is_game_running(philo->e))
		{
			print_msg(philo, HAS_FORK);
			result = f(philo);
		}
		pthread_mutex_unlock(m2);
	}
	pthread_mutex_unlock(m1);
	return (result);
}
