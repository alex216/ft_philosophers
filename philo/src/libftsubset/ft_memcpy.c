/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 08:57:28 by yliu              #+#    #+#             */
/*   Updated: 2024/11/20 08:58:07 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftsubset.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	void	*tmp;

	if (dst == NULL || src == NULL)
		return (NULL);
	tmp = dst;
	while (n--)
		*(char *)tmp++ = *(char *)src++;
	return (dst);
}
