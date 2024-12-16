/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftsubset_bonus.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:48:41 by yliu              #+#    #+#             */
/*   Updated: 2024/12/14 05:14:03 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTSUBSET_BONUS_H
# define LIBFTSUBSET_BONUS_H

# include <errno.h>
# include <limits.h>
# include <stddef.h>
# include <stdlib.h>

int		ft_atoi(const char *str);
void	ft_itoa(int n, char *dest);
int		ft_strcmp(const char *s1, const char *s2);
size_t	ft_strlen(const char *s);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*ft_strdup(const char *src);
char	*ft_strjoin(char const *s1, char const *s2);

#endif
