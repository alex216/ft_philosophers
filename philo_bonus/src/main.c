/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:05:00 by yliu              #+#    #+#             */
/*   Updated: 2024/12/13 23:14:19 by yliu             ###   ########.fr       */
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
	close_channel(e->semaphores.is_running);
	i = 0;
	while (i < num_of_philo)
	{
		close_channel(e->semaphores.eat_count[i]);
		close_channel(e->semaphores.last_meal[i]);
		i++;
	}
}

static void	_print_usage(void)
{
	printf("Usage: ./philo(_bonus) num_of_philo time_to_die ");
	printf("time_to_eat time_to_sleep [min_eat_count]\n");
}

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
