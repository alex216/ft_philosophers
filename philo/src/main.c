/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:05:00 by yliu              #+#    #+#             */
/*   Updated: 2024/11/15 20:22:43 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "philo.h"
#include "init.h"
#include "simulation.h"
#include "validate_args.h"

int	main(int argc, char **argv)
{
	t_env			e;

	if (validate_args(&e, argc, argv) == FAILURE)
		return (EXIT_FAILURE);
	if (init(&e) == FAILURE)
		return (EXIT_FAILURE);
	if (start_simulation(&e) == FAILURE)
		return (EXIT_FAILURE);
	if (wait_simulation_end(&e) == FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
