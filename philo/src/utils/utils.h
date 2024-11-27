/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:03:46 by yliu              #+#    #+#             */
/*   Updated: 2024/11/27 20:33:25 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "mutexes.h"
# include "philo.h"
# include <stdio.h>

t_result	print_msg(t_philo *philo, int STATE);
t_result	sleep_with_check(t_philo *philo, size_t time_to_sleep);

#endif
