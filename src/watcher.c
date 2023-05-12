/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 19:29:45 by gialexan          #+#    #+#             */
/*   Updated: 2023/05/11 22:17:15 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_bool  starving(t_context *ctx, t_philo *philo);
static void    throw_death(t_context *ctx, t_philo *philo);
static t_bool  all_stuffed(t_context *ctx, t_philo *philos);

void    *watcher_routine(void *arg)
{
    int         i;
    t_context   *ctx;
    t_philo     *philos;

    ctx = *get_ctx_ref();
    philos = (t_philo *)arg;
    while (all_stuffed(ctx, philos) != TRUE)
    {
        i = -1;
        while (++i < ctx->num_of_philo)
        {
            if (starving(ctx, &philos[i]))
            {
                throw_death(ctx, &philos[i]);
                return (NULL);
            }
        }
        usleep(1000);
    }
    return (NULL);
}

t_bool stop_dinner(t_context *ctx, t_philo *philo)
{
    t_bool stop_dinner;

    stop_dinner = FALSE;
    pthread_mutex_lock(&ctx->lock_eat);
    if (philo->meals == ctx->num_of_time_eat)
        stop_dinner = TRUE;
    pthread_mutex_unlock(&ctx->lock_eat);

    pthread_mutex_lock(&ctx->lock_death);
    if (ctx->philo_death == TRUE)
        stop_dinner = TRUE;
    pthread_mutex_unlock(&ctx->lock_death);
    return (stop_dinner);
}


static  t_bool all_stuffed(t_context *ctx, t_philo *philos)
{
    t_bool satisfied;

    satisfied = FALSE;
    pthread_mutex_lock(&ctx->lock_eat);
    if (philos[0].meals == ctx->num_of_time_eat)
        satisfied = TRUE;
    pthread_mutex_unlock(&ctx->lock_eat);
    return (satisfied);
}

static  void    throw_death(t_context *ctx, t_philo *philo)
{
    pthread_mutex_lock(&ctx->lock_death);
    ctx->philo_death = TRUE;
    pthread_mutex_unlock(&ctx->lock_death);
    state_log(ctx, philo, DEATH);
}

static  t_bool starving(t_context *ctx, t_philo *philo)
{
    int last_meal;

    pthread_mutex_lock(&ctx->lock_eat);
    last_meal = timestamp_in_ms() - philo->last_meal;
    pthread_mutex_unlock(&ctx->lock_eat);
    return (last_meal > ctx->time_to_die);
}
