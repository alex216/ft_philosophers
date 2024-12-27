/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:03:46 by yliu              #+#    #+#             */
/*   Updated: 2024/12/27 21:16:04 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_BONUS_H
# define UTILS_BONUS_H

# include "philo_bonus.h"
# include "semaphores_bonus.h"
# include "time_bonus.h"
# include <stdio.h>

t_result		unsafe_print_msg(t_philo *philo, int STATE);
t_result		safe_print_msg(t_philo *philo, int STATE);
void			cleanup(t_env *e);

double			ft_ceil(double x);
unsigned int	ft_max(unsigned int a, unsigned int b);

#endif
