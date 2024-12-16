/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:29:12 by yliu              #+#    #+#             */
/*   Updated: 2024/12/14 04:22:11 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "channel_bonus.h"
#include <stdio.h>

static t_channel	*_set_channel_contents(const char *channel_name,
		size_t data_size, t_channel *channel)
{
	memset(channel->data, 0, data_size);
	channel->data_size = data_size;
	channel->lock = sem_open(channel_name, O_CREAT | O_EXCL, 0600, 1);
	if (errno == 0)
	{
		sem_unlink(channel_name);
		return (channel);
	}
	printf("sem_open failed: %s\n", strerror(errno));
	free((char *)channel->name);
	return (NULL);
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
	ft_memcpy(channel->data, data, channel->data_size);
	sem_post(channel->lock);
}

void	receive_channel(t_channel *channel, void *data)
{
	sem_wait(channel->lock);
	ft_memcpy(data, channel->data, channel->data_size);
	sem_post(channel->lock);
}
