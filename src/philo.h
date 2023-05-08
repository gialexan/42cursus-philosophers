/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:41:36 by gialexan          #+#    #+#             */
/*   Updated: 2023/05/08 15:20:16 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PHILO_H
# define PHILO_H

#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

typedef pthread_mutex_t t_fork;

typedef struct s_philo
{
    pthread_t       id;
    pthread_mutex_t *fork_left;
    pthread_mutex_t *fork_right;
}   t_philo;

typedef struct s_context
{
    int     num_of_philo;
    int     time_to_eat;
    int     time_to_sleep;
    int     num_of_time_eat;

}   t_context;


#endif