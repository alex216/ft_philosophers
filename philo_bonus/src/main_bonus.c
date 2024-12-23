/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:05:00 by yliu              #+#    #+#             */
/*   Updated: 2024/12/23 10:09:21 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init_bonus.h"
#include "philo_bonus.h"
#include "simulation_bonus.h"
#include "validate_args_bonus.h"
#include <stdlib.h>

static void	_cleanup(t_env *e)
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

static void	_print_usage(void)
{
	printf("Usage: ./philo(_bonus) num_of_philo time_to_die ");
	printf("time_to_eat time_to_sleep [min_eat_count]\n");
}

// TODO: extra sleep time (or use distrubuted algorithm)
// TODO: crash with many philos
// TODO: busy wait (polling)
// TODO: waiter
int	main(int argc, char **argv)
{
	t_env	e;

	if (validate_args(&e, argc, argv) == FAILURE)
	{
		_print_usage();
		return (EXIT_FAILURE);
	}
	if (init(&e) == FAILURE)
		return (EXIT_FAILURE);
	if (start_simulation(&e) == FAILURE)
		return (EXIT_FAILURE);
	if (wait_simulation_end(&e) == FAILURE)
		return (EXIT_FAILURE);
	_cleanup(&e);
	return (EXIT_SUCCESS);
}
