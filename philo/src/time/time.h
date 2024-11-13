/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:50:36 by yliu              #+#    #+#             */
/*   Updated: 2024/11/15 21:44:34 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIME_H
# define TIME_H

# include <sys/time.h>
# include <stddef.h>
# include <stdbool.h>
# include <unistd.h>

int				difftimeval_ms(struct timeval t1, struct timeval t2);
suseconds_t		difftimeval_us(struct timeval t1, struct timeval t2);
struct timeval	timeval_add_ms(struct timeval t, int msec);
static void		precise_msleep_until(struct timeval end);
void			precise_msleep(size_t msec);

#endif
