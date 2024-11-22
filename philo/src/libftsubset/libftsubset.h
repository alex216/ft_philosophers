/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftsubset.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:48:41 by yliu              #+#    #+#             */
/*   Updated: 2024/11/20 08:57:49 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTSUBSET_H
# define LIBFTSUBSET_H

# include <errno.h>
# include <limits.h>
# include <stddef.h>

int		ft_atoi(const char *str);
size_t	ft_strlen(const char *s);
void	*ft_memcpy(void *dst, const void *src, size_t n);

#endif
