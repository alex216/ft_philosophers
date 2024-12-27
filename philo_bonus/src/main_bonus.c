/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:05:00 by yliu              #+#    #+#             */
/*   Updated: 2024/12/27 21:16:31 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init_bonus.h"
#include "philo_bonus.h"
#include "simulation_bonus.h"
#include "validate_args_bonus.h"
#include <stdlib.h>

static void	_print_usage(void)
{
	printf("Usage: ./philo(_bonus) num_of_philo time_to_die ");
	printf("time_to_eat time_to_sleep [min_eat_count]\n");
}

// TODO: crash with many philos
// TODO: busy wait (polling)
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
	cleanup(&e);
	return (EXIT_SUCCESS);
}
