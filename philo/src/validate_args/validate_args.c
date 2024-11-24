/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:04:56 by yliu              #+#    #+#             */
/*   Updated: 2024/11/23 16:41:57 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validate_args.h"

t_result	validate_args(t_env *e, int argc, char **argv)
{
	t_config	*config;

	if (argc != 5 && argc != 6)
		return (FAILURE);
	memset(e, 0, sizeof(t_env));
	config = &e->config;
	*(size_t *)&config->num_philo = ft_atoi(argv[1]);
	if (errno != 0 || config->num_philo > MAX_PHILO || config->num_philo < 2)
		return (FAILURE);
	*(size_t *)&e->config.time_to_die = ft_atoi(argv[2]);
	if (errno != 0)
		return (FAILURE);
	*(size_t *)&e->config.time_to_eat = ft_atoi(argv[3]);
	if (errno != 0)
		return (FAILURE);
	*(size_t *)&e->config.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		*(int *)&e->config.min_eat_count = ft_atoi(argv[5]);
		if (errno != 0)
			return (FAILURE);
	}
	else
		*(int *)&e->config.min_eat_count = -1;
	return (SUCCESS);
}
