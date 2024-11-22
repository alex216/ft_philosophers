/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:05:08 by yliu              #+#    #+#             */
/*   Updated: 2024/11/23 00:23:35 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "channel.h"
# include <pthread.h>
# include <stdbool.h>
# include <stddef.h>
# include <sys/time.h>

# define MAX_PHILO 200

typedef struct timeval			t_timeval;

typedef struct s_fork			t_fork;
typedef struct s_last_meal		t_last_meal;
typedef struct s_eat_count		t_eat_count;
typedef struct s_dead			t_dead;

typedef struct s_env			t_env;
typedef struct s_philosopher	t_philo;
typedef struct s_manager		t_manager;
typedef struct s_mutexes		t_mutexes;
typedef struct s_config			t_config;

typedef enum e_result
{
	SUCCESS = 0,
	FAILURE = 1
}								t_result;

typedef enum e_state
{
	HAS_FORK = 0,
	EATING = 1,
	SLEEPING = 2,
	THINKING = 3,
	DIED
}								t_state;

struct							s_fork
{
	pthread_mutex_t				lock;
};

struct							s_philosopher
{
	pthread_t					thread;
	size_t						id;
	t_timeval					start_at;

	t_env						*e;
};

struct							s_manager
{
	pthread_t					thread;

	t_env						*e;
};

struct							s_config
{
	const size_t				num_philo;
	const size_t				time_to_die;
	const size_t				time_to_eat;
	const size_t				time_to_sleep;
	const int					minimum_eat_count;
};

struct							s_mutexes
{
	t_fork						fork[MAX_PHILO];
	t_channel					*is_running;
	t_channel					*eat_count[MAX_PHILO];
	t_channel					*last_meal[MAX_PHILO];
};

struct							s_env
{
	t_philo						philo[MAX_PHILO];
	t_manager					manager;
	t_mutexes					mutexes;
	t_config					config;
};

#endif
