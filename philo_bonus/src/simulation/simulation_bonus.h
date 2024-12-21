/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_bonus.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:01:36 by yliu              #+#    #+#             */
/*   Updated: 2024/12/21 15:12:46 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMULATION_BONUS_H
# define SIMULATION_BONUS_H

# include "philo_bonus.h"
# include "semaphores_bonus.h"
# include "time_bonus.h"
# include "utils_bonus.h"
# include <signal.h>

# define PHILO_DIED SIGUSR1

t_result	start_simulation(t_env *e);
t_result	wait_simulation_end(t_env *e);

void		*manager_func(void *void_ptr);
void		*philosopher_func(void *void_ptr);
t_result	eat(t_philo *philo);

#endif
