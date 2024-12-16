/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 18:01:58 by yliu              #+#    #+#             */
/*   Updated: 2024/12/13 11:39:47 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftsubset_bonus.h"

static size_t	_ft_numlen(int n)
{
	size_t	str_len;

	str_len = 1 + (n < 0);
	while (n / 10)
	{
		n /= 10;
		str_len++;
	}
	return (str_len);
}

void	ft_itoa(int n, char *dest)
{
	size_t			len;
	unsigned int	un;

	len = _ft_numlen(n);
	dest[len] = '\0';
	if (n == 0)
		dest[0] = '0';
	if (n < 0)
	{
		dest[0] = '-';
		un = -n;
	}
	else
		un = n;
	while (un > 0)
	{
		dest[--len] = (un % 10) + '0';
		un = un / 10;
	}
}
