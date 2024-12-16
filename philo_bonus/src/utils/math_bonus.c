/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:14:48 by yliu              #+#    #+#             */
/*   Updated: 2024/12/13 21:31:13 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_bonus.h"

double	ft_ceil(double x)
{
	double	truncated;

	truncated = (double)(long)x;
	if (x > truncated)
		return (truncated + 1.0);
	return (truncated);
}

unsigned int	ft_max(unsigned int a, unsigned int b)
{
	if (a < b)
		return (b);
	return (a);
}
