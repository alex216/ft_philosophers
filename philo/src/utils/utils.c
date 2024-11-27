/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 19:20:46 by yliu              #+#    #+#             */
/*   Updated: 2024/11/27 20:47:39 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_result	print_msg(t_philo *philo, int STATE)
{
	t_timeval	now;
	int			diff_time;

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

t_result	sleep_with_check(t_philo *philo, size_t time_to_sleep)
{
	precise_msleep(time_to_sleep);
	if (!safe_is_game_running(philo->e))
		return (FAILURE);
	return (SUCCESS);
}
