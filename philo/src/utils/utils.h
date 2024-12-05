/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:03:46 by yliu              #+#    #+#             */
/*   Updated: 2024/12/05 17:15:15 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "mutexes.h"
# include "philo.h"
# include <stdio.h>

t_result		print_msg(t_philo *philo, int STATE);
t_result		safe_print_msg(t_mutex *m, t_philo *philo, int STATE);
double			ft_ceil(double x);
unsigned int	ft_max(unsigned int a, unsigned int b);

#endif
