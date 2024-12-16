/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+
+:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:05:08 by yliu              #+#    #+#             */
/*   Updated: 2024/12/06 15:29:32 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include "channel_bonus.h"
# include <pthread.h>
# include <semaphore.h>
# include <stdbool.h>
# include <stddef.h>
# include <sys/time.h>

# define MAX_PHILO 200

typedef struct timeval			t_timeval;

typedef struct s_last_meal		t_last_meal;
typedef struct s_eat_count		t_eat_count;
typedef struct s_dead			t_dead;

typedef struct s_env			t_env;
typedef struct s_philosopher	t_philo;
typedef struct s_manager		t_manager;
typedef struct s_semaphores		t_semaphores;
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

struct							s_philosopher
{
	pthread_t					thread;
	size_t						id;

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
	const size_t				min_eat_count;
};

struct							s_semaphores
{
	sem_t						*forks;
	t_channel					*is_running;
	t_channel					*eat_count[MAX_PHILO];
	t_channel					*last_meal[MAX_PHILO];
};

struct							s_env
{
	t_philo						philo[MAX_PHILO];
	t_semaphores				semaphores;
	t_manager					manager;
	t_config					config;
	t_timeval					start_at;
};

#endif
