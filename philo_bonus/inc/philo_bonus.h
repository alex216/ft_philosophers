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

# include <pthread.h>
# include <semaphore.h>
# include <stdbool.h>
# include <stddef.h>
# include <string.h>
# include <sys/time.h>

# define MAX_PHILO 200

typedef struct timeval			t_timeval;
typedef sem_t					t_sembool;

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
	pid_t						pid;
	pthread_t					philo_tid;
	pthread_t					manager_tid;

	size_t						id;

	size_t						eat_count;
	t_timeval					last_meal;
	sem_t						*lock;

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
	sem_t						*waiter;
	t_sembool					*is_running;
};

struct							s_env
{
	t_philo						philo[MAX_PHILO];
	t_semaphores				semaphores;
	t_config					config;
	t_timeval					start_at;
	unsigned int				extra_sleep_time;
};

#endif
