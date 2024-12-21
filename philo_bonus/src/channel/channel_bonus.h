/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:33:55 by yliu              #+#    #+#             */
/*   Updated: 2024/12/19 20:39:50 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_BONUS_H
# define CHANNEL_BONUS_H

# include "libftsubset_bonus.h"
# include <pthread.h>
# include <semaphore.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>

typedef struct s_channel	t_channel;

struct						s_channel
{
	void					*data;
	const char				*name;
	size_t					data_size;
	sem_t					*lock;
};

t_channel					*open_channel(const char *channel_name,
								size_t data_size);
void						close_channel(t_channel *channel);
void						send_channel(t_channel *channel, void *data);
void						receive_channel(t_channel *channel, void *data);

#endif
