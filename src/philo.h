/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:41:36 by gialexan          #+#    #+#             */
/*   Updated: 2023/05/10 21:08:29 by gialexan         ###   ########.fr       */
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

# define EAT "eating"
# define THINK "thinking"
# define SLEEP "sleeping"

typedef pthread_mutex_t t_mutex;

typedef enum s_status
{
    DEAD,
    EATING,
    THINKING,
    SLEEPING,
}   t_status;

typedef struct s_philo
{
    pthread_t   id;
    int         name;
    t_status    action;
    size_t      last_meal;
    t_mutex     *fork_first;
    t_mutex     *fork_second;
}   t_philo;

typedef struct s_context
{
    t_mutex  lock_log;
    size_t  start_time;
    int     num_of_philo;
    int     time_to_eat;
    int     time_to_die;
    int     time_to_sleep;
    int     num_of_time_eat;
}   t_context;


#endif