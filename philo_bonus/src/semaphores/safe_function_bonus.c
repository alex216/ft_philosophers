/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_function_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 01:17:16 by yliu              #+#    #+#             */
/*   Updated: 2024/12/23 20:54:31 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "semaphores_bonus.h"

bool	safe_is_philo_satisfied(t_philo *philo)
{
	size_t			eat_count;
	const size_t	min_eat_count = philo->e->config.min_eat_count;

	sem_wait(philo->lock);
	eat_count = philo->eat_count;
	sem_post(philo->lock);
	if (min_eat_count == 0)
		return (false);
	else
		return (eat_count >= min_eat_count);
}
