/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsafe_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 22:48:32 by yliu              #+#    #+#             */
/*   Updated: 2024/11/21 20:44:26 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mutexes.h"

void	*unsafe_set_time(void *param)
{
	t_timeval	*last_meal_timestamp;

	last_meal_timestamp = param;
	gettimeofday(last_meal_timestamp, NULL);
	return (NULL);
}

void	*unsafe_increment(void *void_ptr)
{
	size_t	*count;

	count = (size_t *)void_ptr;
	(*count)++;
	return (NULL);
}

void	*unsafe_eat(void *void_ptr)
{
	t_philo	*philo;
	size_t	eat_count;
	size_t	id;

	philo = (t_philo *)void_ptr;
	id = philo->id;
	unsafe_printf(philo, EATING, 0);
	precise_msleep(philo->e->config.time_to_eat);
	receive_channel(philo->e->mutexes.eat_count[id - 1], &eat_count);
	eat_count++;
	send_channel(philo->e->mutexes.eat_count[id - 1], &eat_count);
	return (NULL);
}

void	*unsafe_printf(t_philo *philo, int STATE, size_t idx)
{
	if (STATE == HAS_FORK)
		printf("philo %zu has taken a fork %zu\n", philo->id, idx);
	else if (STATE == EATING)
		printf("philo %zu is eating\n", philo->id);
	else if (STATE == SLEEPING)
		printf("philo %zu is sleeping\n", philo->id);
	else if (STATE == THINKING)
		printf("philo %zu is thinking\n", philo->id);
	else if (STATE == DIED)
		printf("philo %zu died\n", philo->id);
	else
		printf("unknown state\n");
	return (NULL);
}
