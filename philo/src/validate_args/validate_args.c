/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:04:56 by yliu              #+#    #+#             */
/*   Updated: 2024/11/28 11:19:53 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validate_args.h"

static size_t	str_to_sizet(char *string)
{
	int		answer;
	int		r;
	char	str[20];

	answer = ft_atoi(string);
	if (errno != 0 || answer < 0)
		return (errno = ERANGE, 0);
	ft_itoa(answer, str);
	r = ft_strcmp(str, string);
	if (r != 0)
		return (errno = ERANGE, 0);
	return (errno = 0, (size_t)answer);
}

t_result	validate_args(t_env *e, int argc, char **argv)
{
	t_config	*config;

	if (argc != 5 && argc != 6)
		return (FAILURE);
	memset(e, 0, sizeof(t_env));
	config = &e->config;
	*(size_t *)&config->num_philo = str_to_sizet(argv[1]);
	if (errno != 0 || config->num_philo > MAX_PHILO || config->num_philo < 2)
		return (FAILURE);
	*(size_t *)&e->config.time_to_die = str_to_sizet(argv[2]);
	if (errno != 0)
		return (FAILURE);
	*(size_t *)&e->config.time_to_eat = str_to_sizet(argv[3]);
	if (errno != 0)
		return (FAILURE);
	*(size_t *)&e->config.time_to_sleep = str_to_sizet(argv[4]);
	if (errno != 0)
		return (FAILURE);
	if (argc == 6)
	{
		*(size_t *)&e->config.min_eat_count = str_to_sizet(argv[5]);
		if (errno != 0)
			return (FAILURE);
	}
	else
		*(size_t *)&e->config.min_eat_count = 0;
	return (SUCCESS);
}
