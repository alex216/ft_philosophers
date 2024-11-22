/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:29:12 by yliu              #+#    #+#             */
/*   Updated: 2024/11/20 21:37:59 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "channel.h"

t_channel	*construct_channel(size_t data_size)
{
	t_channel	*channel;

	channel = malloc(sizeof(t_channel));
	if (!channel)
		return (NULL);
	channel->data = malloc(data_size);
	if (!channel->data)
	{
		free(channel);
		return (NULL);
	}
	memset(channel->data, 0, data_size);
	channel->data_size = data_size;
	pthread_mutex_init(&channel->lock, NULL);
	return (channel);
}

void	destruct_channel(t_channel *channel)
{
	pthread_mutex_destroy(&channel->lock);
	free(channel->data);
	free(channel);
}

void	send_channel(t_channel *channel, void *data)
{
	pthread_mutex_lock(&channel->lock);
	ft_memcpy(channel->data, data, channel->data_size);
	pthread_mutex_unlock(&channel->lock);
}

void	receive_channel(t_channel *channel, void *data)
{
	pthread_mutex_lock(&channel->lock);
	ft_memcpy(data, channel->data, channel->data_size);
	pthread_mutex_unlock(&channel->lock);
}
