/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:28:35 by yliu              #+#    #+#             */
/*   Updated: 2024/12/13 22:33:37 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "semaphores_bonus.h"

t_result	init_semaphores(t_env *e)
{
	// i dont know if its /forks or not yet
	e->semaphores.forks = sem_open("forks", O_CREAT | O_EXCL, 0600,
			e->config.num_philo);
	sem_unlink("forks");
	if (errno != 0)
		return (FAILURE);
	return (SUCCESS);
}
