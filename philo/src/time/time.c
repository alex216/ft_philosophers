/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 12:55:32 by yliu              #+#    #+#             */
/*   Updated: 2024/11/23 00:36:29 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "time.h"

#define MSEC_IN_SEC 1000
#define USEC_IN_MSEC 1000
#define USEC_IN_SEC 1000000

long	difftimeval_ms(struct timeval t1, struct timeval t2)
{
	long	diff;

	diff = (t2.tv_sec - t1.tv_sec) * MSEC_IN_SEC;
	diff += (t2.tv_usec - t1.tv_usec) / USEC_IN_MSEC;
	return (diff);
}

suseconds_t	difftimeval_us(struct timeval t1, struct timeval t2)
{
	suseconds_t	diff;

	diff = (suseconds_t)(t2.tv_sec - t1.tv_sec) * USEC_IN_SEC;
	diff += t2.tv_usec - t1.tv_usec;
	return (diff);
}

struct timeval	timeval_add_ms(struct timeval t, int msec)
{
	t.tv_usec += (msec % MSEC_IN_SEC) * USEC_IN_MSEC;
	t.tv_sec += msec / MSEC_IN_SEC + t.tv_usec / USEC_IN_SEC;
	t.tv_usec %= USEC_IN_SEC;
	return (t);
}

static void	precise_msleep_until(struct timeval end)
{
	struct timeval	now;
	suseconds_t		diff;

	while (true)
	{
		gettimeofday(&now, NULL);
		diff = difftimeval_us(now, end);
		if (diff <= 0)
			break ;
		usleep(diff / 2);
	}
}

void	precise_msleep(size_t msec)
{
	struct timeval	start;
	struct timeval	end;

	gettimeofday(&start, NULL);
	end = timeval_add_ms(start, (int)msec);
	precise_msleep_until(end);
}
