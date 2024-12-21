/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphores_bonus.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:27:41 by yliu              #+#    #+#             */
/*   Updated: 2024/12/21 16:17:19 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SEMAPHORES_BONUS_H
# define SEMAPHORES_BONUS_H

# include "philo_bonus.h"
# include "utils_bonus.h"
# include <pthread.h>
# include <semaphore.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>

typedef t_result	(*t_unsafe_func)(void *);

t_result			init_semaphores(t_env *e);
void				destroy_semaphores(t_env *e);

bool				safe_is_philo_satisfied(t_philo *philo);
#endif
