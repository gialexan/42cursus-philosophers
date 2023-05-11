/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:41:36 by gialexan          #+#    #+#             */
/*   Updated: 2023/05/11 18:01:31 by gialexan         ###   ########.fr       */
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

# define TAKE_FORK "has take a fork ⚡️"
# define EAT "is eating 🍕"
# define THINK "is thinking 🤔"
# define SLEEP "is sleeping 😴"
# define DEATH "is death 💀"

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


#endif