/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:29:12 by yliu              #+#    #+#             */
/*   Updated: 2024/12/18 18:01:38 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "channel_bonus.h"
#include <stdio.h>

// if program crashes or terminated by signal, semaphore stays in the system
// so I choose O_CREAT, instead of O_EXCL
static t_channel	*_set_channel_contents(const char *channel_name,
		size_t data_size, t_channel *channel)
{
	memset(channel->data, 0, data_size);
	channel->data_size = data_size;
	channel->lock = sem_open(channel_name, O_CREAT, 0600, 1);
	if (channel->lock == SEM_FAILED)
	{
		printf("sem open failed: %s\n", strerror(errno));
		free((char *)channel->name);
		return (NULL);
	}
	sem_unlink(channel_name);
	return (channel);
}

t_channel	*open_channel(const char *channel_name, size_t data_size)
{
	t_channel	*channel;

	channel = malloc(sizeof(t_channel));
	if (channel)
	{
		channel->data = malloc(data_size);
		if (channel->data)
		{
			channel->name = ft_strdup(channel_name);
			if (channel->name)
				return (_set_channel_contents(channel_name, data_size,
						channel));
			free(channel->data);
		}
		free(channel);
	}
	return (NULL);
}

void	close_channel(t_channel *channel)
{
	sem_close(channel->lock);
	free(channel->data);
	free((char *)channel->name);
	free(channel);
}

void	send_channel(t_channel *channel, void *data)
{
	sem_wait(channel->lock);
	__builtin_memcpy(channel->data, data, channel->data_size);
	sem_post(channel->lock);
}

void	receive_channel(t_channel *channel, void *data)
{
	sem_wait(channel->lock);
	__builtin_memcpy(data, channel->data, channel->data_size);
	sem_post(channel->lock);
}
