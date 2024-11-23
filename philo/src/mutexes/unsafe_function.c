/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsafe_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 22:48:32 by yliu              #+#    #+#             */
/*   Updated: 2024/11/23 13:34:07 by yliu             ###   ########.fr       */
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

t_result	unsafe_eat(void *void_ptr)
{
	t_philo	*philo;
	size_t	eat_count;
	size_t	id;

	philo = (t_philo *)void_ptr;
	id = philo->id;
	if (unsafe_printf(philo, EATING) == FAILURE)
		return (FAILURE);
	precise_msleep(philo->e->config.time_to_eat);
	receive_channel(philo->e->mutexes.eat_count[id - 1], &eat_count);
	eat_count++;
	send_channel(philo->e->mutexes.eat_count[id - 1], &eat_count);
	return (SUCCESS);
}

t_result	unsafe_printf(t_philo *philo, int STATE)
{
	t_timeval	now;
	int			diff_time;

	if (!safe_is_game_running(philo->e))
		return (FAILURE);
	gettimeofday(&now, NULL);
	diff_time = difftimeval_ms(philo->start_at, now);
	if (STATE == HAS_FORK)
		printf("%d %zu has taken a fork\n", diff_time, philo->id);
	else if (STATE == EATING)
		printf("%d %zu is eating\n", diff_time, philo->id);
	else if (STATE == SLEEPING)
		printf("%d %zu is sleeping\n", diff_time, philo->id);
	else if (STATE == THINKING)
		printf("%d %zu is thinking\n", diff_time, philo->id);
	else if (STATE == DIED)
		printf("%d %zu died\n", diff_time, philo->id);
	else
		printf("unknown state\n");
	return (SUCCESS);
}
