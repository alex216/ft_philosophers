/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:27:41 by yliu              #+#    #+#             */
/*   Updated: 2024/11/23 14:19:24 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTEXES_H
# define MUTEXES_H

# include "philo.h"
# include <pthread.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>

typedef t_result	(*t_unsafe_func)(void *);

t_result			init_mutexes(t_env *e);
void				destroy_mutexes(t_env *e);

void				safe_execute(t_unsafe_func f, pthread_mutex_t *m,
						void *param);
t_result			safe_execute_with_two_mutexes(t_unsafe_func f,
						pthread_mutex_t *m1, pthread_mutex_t *m2, void *param);

t_result			unsafe_eat(void *void_ptr);
t_result			unsafe_printf(t_philo *philo, int STATE);

bool				safe_is_philo_satisfied(t_philo *philo);
bool				safe_is_philo_dead(t_philo *philo);
bool				safe_is_game_running(t_env *e);
#endif
