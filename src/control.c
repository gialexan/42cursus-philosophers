/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 19:56:54 by gialexan          #+#    #+#             */
/*   Updated: 2023/05/12 11:07:21 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_context   init_context(int argc, char **argv)
{
    t_context   ctx;

    ctx.start_time = timestamp_in_ms();
    ctx.num_of_philo = to_int(argv[1]);
    ctx.time_to_die = to_int(argv[2]);
    ctx.time_to_eat = to_int(argv[3]);
    ctx.time_to_sleep = to_int(argv[4]);
    ctx.num_of_time_eat = -1;
    if (argc == 6)
        ctx.num_of_time_eat = to_int(argv[5]);
    ctx.philo_death = FALSE;
    pthread_mutex_init(&ctx.lock_log, NULL);
    pthread_mutex_init(&ctx.lock_eat, NULL);
    pthread_mutex_init(&ctx.lock_death, NULL);
    return (ctx);
}

t_philo *create_philos(t_context *ctx, t_mutex *forks)
{
    int         i;
    t_philo     *philos;

    i = -1;
    philos = malloc(ctx->num_of_philo * sizeof(t_philo));
    if (!philos)
        return (NULL);
    while(++i < ctx->num_of_philo)
    {
        philos[i].id = -1;
        philos[i].name = i + 1;
        philos[i].meals = 0;
        philos[i].last_meal = ctx->start_time;
        philos[i].fork_first = &forks[min(i, (i + 1) % ctx->num_of_philo)];
        philos[i].fork_second = &forks[max(i, (i + 1) % ctx->num_of_philo)];
    }
    return (philos);
}

t_mutex  *create_forks(t_context *ctx)
{
    int     i;
    t_mutex  *forks;

    i = -1;
    forks = malloc(ctx->num_of_philo * sizeof(t_mutex));
    if (!forks)
        return (NULL);
    while (++i < ctx->num_of_philo)
        pthread_mutex_init(&forks[i], NULL);
    return (forks);
}

void    begin_dinner(t_context *ctx, t_philo *philos)
{
    int         i;
    pthread_t   watcher;

    i = -1;
    save_ctx_ref(ctx);
    while (++i < ctx->num_of_philo)
        pthread_create(&philos[i].id, NULL, &philos_routine, &philos[i]);
    pthread_create(&watcher, NULL, &watcher_routine, philos);
    while (i--)
        pthread_join(philos[i].id, NULL);
    pthread_join(watcher, NULL);
}

void    clear(t_context *ctx, t_mutex *forks, t_philo *philos)
{
    int i;

    i = -1;
    while (++i < ctx->num_of_philo)
        pthread_mutex_destroy(&forks[i]);
    pthread_mutex_destroy(&ctx->lock_log);
    pthread_mutex_destroy(&ctx->lock_eat);
    pthread_mutex_destroy(&ctx->lock_death);
    free(forks);
    free(philos);
}
