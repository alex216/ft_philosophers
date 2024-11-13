/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eam.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:44:12 by yliu              #+#    #+#             */
/*   Updated: 2024/11/15 20:54:36 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mutexes.h"

typedef void *	(*t_unsafe_func)(void *);

void	safe_execute(t_unsafe_func f, pthread_mutex_t *mutex, void *param)
{
	pthread_mutex_lock(mutex);
	f(param);
	pthread_mutex_unlock(mutex);
}

void	safe_execute_with_two_mutexes(t_unsafe_func f,
					pthread_mutex_t *m1,
					pthread_mutex_t *m2,
					void *param)
{
	pthread_mutex_lock(m1);
	pthread_mutex_lock(m2);
	f(param);
	pthread_mutex_unlock(m2);
	pthread_mutex_unlock(m1);
}
