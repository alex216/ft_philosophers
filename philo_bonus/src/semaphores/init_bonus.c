/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:28:35 by yliu              #+#    #+#             */
/*   Updated: 2024/12/18 17:57:17 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "semaphores_bonus.h"

t_result	init_semaphores(t_env *e)
{
	e->semaphores.forks = sem_open("forks", O_CREAT, 0600, e->config.num_philo);
	if (e->semaphores.forks == SEM_FAILED)
	{
		printf("sem_open failed: %s\n", strerror(errno));
		return (FAILURE);
	}
	sem_unlink("forks");
	return (SUCCESS);
}
