/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:26:22 by yliu              #+#    #+#             */
/*   Updated: 2024/12/21 19:47:12 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "semaphores_bonus.h"

void	destroy_semaphores(t_env *e)
{
	sem_close(e->semaphores.forks);
	sem_close(e->semaphores.is_running);
	sem_close(e->semaphores.waiter);
}
