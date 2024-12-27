/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 19:20:46 by yliu              #+#    #+#             */
/*   Updated: 2024/12/27 21:17:22 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_bonus.h"

t_result	unsafe_print_msg(t_philo *philo, int STATE)
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

// if STATE is DIED, it will not release the is_running semaphore
t_result	safe_print_msg(t_philo *philo, int STATE)
{
	sem_wait(philo->e->semaphores.is_running);
	unsafe_print_msg(philo, STATE);
	if (STATE == DIED)
		return (FAILURE);
	sem_post(philo->e->semaphores.is_running);
	return (SUCCESS);
}

void	cleanup(t_env *e)
{
	size_t			i;
	const size_t	num_of_philo = e->config.num_philo;

	destroy_semaphores(e);
	i = 0;
	while (i < num_of_philo)
	{
		sem_close(e->philo[i].lock);
		i++;
	}
}
