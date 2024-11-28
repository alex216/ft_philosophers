/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftsubset.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:48:41 by yliu              #+#    #+#             */
/*   Updated: 2024/11/28 10:59:12 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTSUBSET_H
# define LIBFTSUBSET_H

# include <errno.h>
# include <limits.h>
# include <stddef.h>

int		ft_atoi(const char *str);
void	ft_itoa(int n, char *dest);
int		ft_strcmp(const char *s1, const char *s2);
size_t	ft_strlen(const char *s);
void	*ft_memcpy(void *dst, const void *src, size_t n);

#endif
