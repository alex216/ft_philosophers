/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 08:57:28 by yliu              #+#    #+#             */
/*   Updated: 2024/12/13 11:39:50 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftsubset_bonus.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	if (dst == NULL || src == NULL)
		return (NULL);
	s = src;
	d = dst;
	while (n)
	{
		*d++ = *s++;
		n--;
	}
	return (dst);
}
