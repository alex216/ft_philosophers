/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:01:36 by yliu              #+#    #+#             */
/*   Updated: 2024/11/23 15:05:45 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMULATION_H
# define SIMULATION_H

# include "mutexes.h"
# include "philo.h"
# include "utils.h"

t_result	start_simulation(t_env *e);
t_result	wait_simulation_end(t_env *e);

void		*manager(void *void_ptr);
void		*philosopher(void *void_ptr);
t_result	eat(t_philo *philo);

#endif
