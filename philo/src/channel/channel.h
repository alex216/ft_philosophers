/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:33:55 by yliu              #+#    #+#             */
/*   Updated: 2024/12/01 11:43:17 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_H
# define CHANNEL_H

# include "libftsubset.h"
# include <pthread.h>
# include <stdlib.h>
# include <string.h>

typedef struct s_channel	t_channel;
typedef pthread_mutex_t		t_mutex;

struct						s_channel
{
	void					*data;
	size_t					data_size;
	t_mutex					lock;
};

t_channel					*construct_channel(size_t data_size);
void						destruct_channel(t_channel *channel);
void						send_channel(t_channel *channel, void *data);
void						receive_channel(t_channel *channel, void *data);

#endif
