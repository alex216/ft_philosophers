/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:33:55 by yliu              #+#    #+#             */
/*   Updated: 2024/11/20 10:12:00 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_H
# define CHANNEL_H

# include "libftsubset.h"
# include <pthread.h>
# include <stdlib.h>
# include <string.h>

typedef struct s_channel	t_channel;

struct						s_channel
{
	void					*data;
	size_t					data_size;
	pthread_mutex_t			lock;
};

static t_channel			*construct_channel(size_t data_size);
void						destruct_channel(t_channel *channel);
void						send_channel(t_channel *channel, void *data);
void						receive_channel(t_channel *channel, void *data);

#endif
