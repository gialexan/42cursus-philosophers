/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 19:39:45 by gialexan          #+#    #+#             */
/*   Updated: 2023/05/11 19:42:44 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    dinner_action(t_context *ctx, t_philo *philo)
{
    pthread_mutex_lock(philo->fork_first);
    pthread_mutex_lock(philo->fork_second);
    if (stop_dinner(ctx, philo) == TRUE)
    {
        pthread_mutex_unlock(philo->fork_first);
        pthread_mutex_unlock(philo->fork_second);
        return ;
    }

    state_log(ctx, philo, TAKE_FORK);
    state_log(ctx, philo, EAT);

    pthread_mutex_lock(&ctx->lock_eat);
    philo->meals++;
    philo->last_meal = timestamp_in_ms();
    pthread_mutex_unlock(&ctx->lock_eat);

    mssleep(ctx->time_to_eat);
    pthread_mutex_unlock(philo->fork_first);
    pthread_mutex_unlock(philo->fork_second);
}

void    sleep_action(t_context *ctx, t_philo *philo)
{
    if (stop_dinner(ctx, philo) == TRUE)
        return ;
    state_log(ctx, philo, SLEEP);
    mssleep(ctx->time_to_sleep);
}

void    think_action(t_context *ctx, t_philo *philo)
{
    if (stop_dinner(ctx, philo) == TRUE)
        return ;
    state_log(ctx, philo, THINK);
}
