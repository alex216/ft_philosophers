/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:05:00 by yliu              #+#    #+#             */
/*   Updated: 2024/12/05 17:42:54 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "channel.h"
#include "init.h"
#include "philo.h"
#include "simulation.h"
#include "validate_args.h"
#include <stdlib.h>

static void	_cleanup(t_env *e)
{
	size_t			i;
	const size_t	num_of_philo = e->config.num_philo;

	destroy_mutexes(e);
	destruct_channel(e->mutexes.is_running);
	i = 0;
	while (i < num_of_philo)
	{
		destruct_channel(e->mutexes.eat_count[i]);
		destruct_channel(e->mutexes.last_meal[i]);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_env	e;

	if (validate_args(&e, argc, argv) == FAILURE)
		return (EXIT_FAILURE);
	if (init(&e) == FAILURE)
		return (EXIT_FAILURE);
	if (start_simulation(&e) == FAILURE)
		return (EXIT_FAILURE);
	if (wait_simulation_end(&e) == FAILURE)
		return (EXIT_FAILURE);
	_cleanup(&e);
	return (EXIT_SUCCESS);
}
