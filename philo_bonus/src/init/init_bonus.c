/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:46:55 by yliu              #+#    #+#             */
/*   Updated: 2024/12/28 14:38:04 by yliu             ###   ########.fr       */
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
		e->philo[i].eat_count = 0;
		e->philo[i].last_meal = e->start_at;
		i++;
	}
}

static unsigned int	_calc_extra_sleep_time(t_env *env)
{
	const size_t	n = env->config.num_philo;
	const size_t	k = n / 2;
	const size_t	e = env->config.time_to_eat;
	const size_t	s = env->config.time_to_sleep;

	if (n == 1)
		return (0);
	return (ft_max(e * n / k - (e + s), 0));
}

static t_result	init_semaphore_of_philo(t_env *e)
{
	size_t			i;
	const size_t	num_of_philo = e->config.num_philo;
	char			*sem_name;
	char			philo_idx[20];

	i = 0;
	while (i < num_of_philo)
	{
		ft_itoa(i, philo_idx);
		sem_name = ft_strjoin("philo_lock_", philo_idx);
		if (sem_name == NULL)
			return (FAILURE);
		e->philo[i].lock = sem_open(sem_name, O_CREAT, 0600, 1);
		if (e->philo[i].lock == SEM_FAILED)
			return (FAILURE);
		sem_unlink(sem_name);
		free(sem_name);
		i++;
	}
	return (SUCCESS);
}

static t_result	_init_semaphores(t_env *e)
{
	e->semaphores.forks = sem_open("forks", O_CREAT, 0600, e->config.num_philo);
	if (e->semaphores.forks == SEM_FAILED)
	{
		printf("sem_open failed: %s\n", strerror(errno));
		return (FAILURE);
	}
	sem_unlink("forks");
	if (e->config.num_philo == 1)
		e->semaphores.waiter = sem_open("waiter", O_CREAT, 0600, 1);
	else
		e->semaphores.waiter = sem_open("waiter", O_CREAT, 0600,
				e->config.num_philo - 1);
	if (e->semaphores.waiter == SEM_FAILED)
		return (FAILURE);
	sem_unlink("waiter");
	e->semaphores.is_running = sem_open("is_running_flag", O_CREAT, 0600, 1);
	if (e->semaphores.is_running == SEM_FAILED)
		return (FAILURE);
	sem_unlink("is_running_flag");
	if (init_semaphore_of_philo(e) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

t_result	init(t_env *e)
{
	t_timeval	start_at;
	const int	time_to_create_procs = 2000;

	gettimeofday(&start_at, NULL);
	e->start_at = timeval_add_ms(start_at, time_to_create_procs);
	e->extra_sleep_time = _calc_extra_sleep_time(e);
	_init_philo(e);
	return (_init_semaphores(e));
}
