/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:50:36 by yliu              #+#    #+#             */
/*   Updated: 2024/11/30 16:57:58 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIME_H
# define TIME_H

# include <stdbool.h>
# include <stddef.h>
# include <sys/time.h>
# include <unistd.h>

long			difftimeval_ms(struct timeval t1, struct timeval t2);
suseconds_t		difftimeval_us(struct timeval t1, struct timeval t2);
struct timeval	timeval_add_ms(struct timeval t, int msec);
void			precise_msleep_until(struct timeval end);
void			precise_msleep(size_t msec);

#endif
