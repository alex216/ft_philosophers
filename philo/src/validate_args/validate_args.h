/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_args.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:04:52 by yliu              #+#    #+#             */
/*   Updated: 2024/11/13 11:51:48 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALIDATE_ARGS_H
# define VALIDATE_ARGS_H

# include <stddef.h>
# include <errno.h>

# include "philo.h"
# include "libftsubset.h"

t_result	validate_args(t_env *e, int argc, char **argv);

#endif
