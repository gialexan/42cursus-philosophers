/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:41:36 by gialexan          #+#    #+#             */
/*   Updated: 2023/05/12 11:07:31 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PHILO_H
# define PHILO_H

# include <time.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

# define EAT "is eating 🍕"
# define DEATH "is death 💀"
# define THINK "is thinking 🤔"
# define SLEEP "is sleeping 😴"
# define TAKE_FORK "has take a fork ⚡️"

#define INT_MAX 2147483647
#define INT_MIN -2147483648
#define INVALID_NUMBER -1

typedef pthread_mutex_t t_mutex;

typedef enum e_bool
{
	FALSE,
	TRUE,
}	t_bool;

typedef struct s_philo
{
    pthread_t   id;
    int         name;
    int         meals;
    size_t      last_meal;
    t_mutex     *fork_first;
    t_mutex     *fork_second;
}   t_philo;

typedef struct s_context
{
    t_mutex lock_log;
    t_mutex lock_eat;
    t_mutex lock_death;
    size_t  start_time;
    t_bool  philo_death;
    int     num_of_philo;
    int     time_to_eat;
    int     time_to_die;
    int     time_to_sleep;
    int     num_of_time_eat;
}   t_context;

/***************************************************************************\
 * MAIN.C
\***************************************************************************/

void    *philos_routine(void *philo);

/***************************************************************************\
 * WATCHER.C
\***************************************************************************/

void    *watcher_routine(void *arg);
t_bool  stop_dinner(t_context *ctx, t_philo *philo);

/***************************************************************************\
 * UTILS.C
\***************************************************************************/

int     min(int a, int b);
int     max(int a, int b);
int     mssleep(size_t ms);
size_t  timestamp_in_ms(void);
void    state_log(t_context *ctx, t_philo *philo, char *status);

/***************************************************************************\
 * INTERFACE.C
\***************************************************************************/

t_context   **get_ctx_ref(void);
void    save_ctx_ref(t_context *ctx);

/***************************************************************************\
 * CONTROL.C
\***************************************************************************/

t_mutex *create_forks(t_context *ctx);
t_context   init_context(int argc, char **argv);
void    begin_dinner(t_context *ctx, t_philo *philos);
t_philo *create_philos(t_context *ctx, t_mutex *forks);
void    clear(t_context *ctx, t_mutex *forks, t_philo *philos);

/***************************************************************************\
 * ACTION.C
\***************************************************************************/

void    think_action(t_context *ctx, t_philo *philo);
void    sleep_action(t_context *ctx, t_philo *philo);
void    dinner_action(t_context *ctx, t_philo *philo);

/***************************************************************************\
 * PARSE.C
\***************************************************************************/

int     to_int(const char *nptr);
t_bool  check_args(int argc, char **argv);

#endif