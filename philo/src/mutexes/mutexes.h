/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:27:41 by yliu              #+#    #+#             */
/*   Updated: 2024/11/28 16:52:58 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTEXES_H
# define MUTEXES_H

# include "philo.h"
# include "utils.h"
# include <pthread.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>

typedef t_result	(*t_unsafe_func)(void *);

t_result			init_mutexes(t_env *e);
void				destroy_mutexes(t_env *e);

//// channel operations
bool				safe_is_philo_satisfied(t_philo *philo);
bool				safe_is_game_running(t_env *e);
void				safe_update_last_meal(t_philo *philo, t_timeval *tp);
#endif
