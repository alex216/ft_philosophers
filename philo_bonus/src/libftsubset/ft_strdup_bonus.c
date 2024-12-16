/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 19:55:12 by yliu              #+#    #+#             */
/*   Updated: 2024/12/13 21:28:06 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftsubset_bonus.h"

char	*ft_strdup(const char *src)
{
	char	*dst;
	size_t	length;
	size_t	i;

	if (src == NULL)
		return (NULL);
	length = ft_strlen(src);
	dst = malloc(sizeof(char) * (length + 1));
	if (!dst)
		return (NULL);
	i = 0;
	while (i < length)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
