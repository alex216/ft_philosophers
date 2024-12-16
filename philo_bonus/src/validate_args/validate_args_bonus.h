/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_args_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:04:52 by yliu              #+#    #+#             */
/*   Updated: 2024/12/06 17:26:01 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALIDATE_ARGS_BONUS_H
# define VALIDATE_ARGS_BONUS_H

# include "libftsubset_bonus.h"
# include "philo_bonus.h"
# include <errno.h>
# include <stddef.h>

t_result	validate_args(t_env *e, int argc, char **argv);

#endif
