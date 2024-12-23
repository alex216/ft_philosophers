/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphores_bonus.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:27:41 by yliu              #+#    #+#             */
/*   Updated: 2024/12/23 20:49:32 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SEMAPHORES_BONUS_H
# define SEMAPHORES_BONUS_H

# include "philo_bonus.h"
# include "utils_bonus.h"
# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <sys/errno.h>

typedef t_result	(*t_unsafe_func)(void *);

void				destroy_semaphores(t_env *e);

bool				safe_is_philo_satisfied(t_philo *philo);
#endif
