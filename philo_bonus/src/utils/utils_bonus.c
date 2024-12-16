/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 19:20:46 by yliu              #+#    #+#             */
/*   Updated: 2024/12/13 22:10:30 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_bonus.h"

t_result	print_msg(t_philo *philo, int STATE)
{
	t_timeval	now;
	int			diff_time;

	gettimeofday(&now, NULL);
	diff_time = difftimeval_ms(philo->e->start_at, now);
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

t_result	safe_print_msg(t_channel *channel, t_philo *philo, int STATE)
{
	t_result	result;

	result = FAILURE;
	sem_wait(channel->lock);
	if (*(bool *)philo->e->semaphores.is_running->data)
	{
		result = print_msg(philo, STATE);
	}
	sem_post(channel->lock);
	return (result);
}
