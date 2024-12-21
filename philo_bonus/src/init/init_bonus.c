/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:46:55 by yliu              #+#    #+#             */
/*   Updated: 2024/12/21 21:25:57 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init_bonus.h"

// t_timeval can be shallow copied because it is a struct of two longs
static void	_init_philo(t_env *e)
{
	size_t	i;

	i = 0;
	while (i < e->config.num_philo)
	{
		e->philo[i].id = i + 1;
		e->philo[i].e = e;
		i++;
	}
}

static t_result	close_all_channels(t_env *e, size_t i)
{
	while (i > 0)
	{
		close_channel(e->semaphores.eat_count[--i]);
		close_channel(e->semaphores.last_meal[i]);
	}
	return (FAILURE);
}

static unsigned int	_calc_extra_sleep_time(t_env *env)
{
	const size_t	n = env->config.num_philo;
	const size_t	k = n / 2;
	const size_t	e = env->config.time_to_eat;
	const size_t	s = env->config.time_to_sleep;

	return (ft_max(e * n / k - (e + s), 0));
}

static t_result	init_semaphore_of_philo(t_env *e)
{
	size_t			i;
	size_t			eat_count;
	const size_t	num_of_philo = e->config.num_philo;
	char			*sem_name;
	char			philo_idx[20];

	eat_count = 0;
	i = 0;
	while (i < num_of_philo)
	{
		ft_itoa(i, philo_idx);
		sem_name = ft_strjoin("eat_count_", philo_idx);
		if (sem_name == NULL)
			return (close_all_channels(e, i));
		e->semaphores.eat_count[i] = open_channel(sem_name, sizeof(size_t));
		free(sem_name);
		if (e->semaphores.eat_count[i] == NULL)
			return (close_all_channels(e, i));
		send_channel(e->semaphores.eat_count[i], &eat_count);
		sem_name = ft_strjoin("last_meal_", philo_idx);
		if (sem_name == NULL)
		{
			close_channel(e->semaphores.eat_count[i]);
			return (close_all_channels(e, i));
		}
		e->semaphores.last_meal[i] = open_channel(sem_name, sizeof(t_timeval));
		free(sem_name);
		if (e->semaphores.last_meal[i] == NULL)
		{
			close_channel(e->semaphores.eat_count[i]);
			return (close_all_channels(e, i));
		}
		send_channel(e->semaphores.last_meal[i], &e->start_at);
		i++;
	}
	return (SUCCESS);
}

static t_result	_init_semaphore(t_env *e)
{
	// unhappy path not considered yet.
	e->semaphores.waiter = malloc(sizeof(sem_t));
	if (e->semaphores.waiter == NULL)
		return (FAILURE);
	e->semaphores.waiter = sem_open("waiter", O_CREAT, 0600, e->config.num_philo
			- 1);
	if (e->semaphores.waiter == SEM_FAILED)
	{
		printf("sem_open failed: %s\n", strerror(errno));
		return (FAILURE);
	}
	unlink("waiter");
	e->semaphores.is_running = malloc(sizeof(t_sembool));
	if (e->semaphores.is_running == NULL)
		return (FAILURE);
	e->semaphores.is_running = sem_open("is_running_flag", O_CREAT, 0600, 1);
	if (e->semaphores.is_running == SEM_FAILED)
	{
		printf("sem_open failed: %s\n", strerror(errno));
		return (FAILURE);
	}
	sem_unlink("is_running_flag");
	if (init_semaphore_of_philo(e) == FAILURE)
	{
		return (FAILURE);
	}
	return (SUCCESS);
}

t_result	init(t_env *e)
{
	t_timeval	start_at;
	const int	time_to_create_procs = 500 * e->config.num_philo;

	gettimeofday(&start_at, NULL);
	e->start_at = timeval_add_ms(start_at, time_to_create_procs);
	e->extra_sleep_time = _calc_extra_sleep_time(e);
	_init_philo(e);
	e->manager.e = e;
	return (_init_semaphore(e));
}
