/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:27:41 by yliu              #+#    #+#             */
/*   Updated: 2024/11/15 21:43:39 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTEXES_H
# define MUTEXES_H

# include <pthread.h>
# include <stddef.h>
# include <stdbool.h>
# include <stdio.h>

# include "philo.h"

typedef void *	(*t_unsafe_func)(void *);

t_result	init_mutexes(t_env *e);
void		destroy_mutexes(t_env *e);

void		safe_execute(t_unsafe_func f, pthread_mutex_t *m, void *param);
void		safe_execute_with_two_mutexes(t_unsafe_func f,
				pthread_mutex_t *m1,
				pthread_mutex_t *m2,
				void *param);

void		*unsafe_set_time(void *param);
void		*unsafe_increment(void *void_ptr);
void		*unsafe_eat(void *void_ptr);
void		*unsafe_printf(t_philo *philo, int STATE, size_t idx);

#endif
