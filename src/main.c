/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:41:24 by gialexan          #+#    #+#             */
/*   Updated: 2023/05/11 18:05:37 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t timestamp_in_ms(void);

t_bool stop_dinner(t_context *ctx, t_philo *philo);

int    mssleep(size_t ms)
{
    size_t    start;

    start = timestamp_in_ms();
    while (ms > timestamp_in_ms() - start)
        usleep(100);
    return (0);
}

int ft_min(int a, int b)
{
    if (a < b)
        return (a);
    return (b);
}

int ft_max(int a, int b)
{
    if (a > b)
        return (a);
    return (b);
}

t_context   **get_ctx_ref(void)
{
    static t_context *ctx;

    return (&ctx);
}

size_t timestamp_in_ms(void)
{
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	return ((tp.tv_sec * 1000) + (tp.tv_usec / 1000));
}

void    state_log(t_context *ctx, t_philo *philo, char *status)
{
    size_t  current;
    size_t  elapsed;

    pthread_mutex_lock(&ctx->lock_log);

    current = timestamp_in_ms();
    elapsed = current - ctx->start_time;
    printf("%5ld Philosopher %2d %s\n", elapsed, philo->name, status);

    pthread_mutex_unlock(&ctx->lock_log);
}

void    save_ctx_ref(t_context *ctx)
{
    t_context   **save_ctx;

    save_ctx = get_ctx_ref();
    *save_ctx = ctx;
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
        philos[i].name = i;
        philos[i].meals = 0;
        philos[i].last_meal = ctx->start_time;
        philos[i].fork_first = &forks[ft_min(i, (i + 1) % ctx->num_of_philo)];
        philos[i].fork_second = &forks[ft_max(i, (i + 1) % ctx->num_of_philo)];
    }
    return (philos);
}

t_context   init_context(char **argv)
{
    t_context   ctx;

    (void)argv;
    ctx.start_time = timestamp_in_ms();
    ctx.num_of_philo = 4;
    ctx.time_to_die = 310;
    ctx.time_to_eat = 200;
    ctx.time_to_sleep = 100;
    ctx.num_of_time_eat = -1;
    ctx.philo_death = FALSE;
    pthread_mutex_init(&ctx.lock_log, NULL);
    pthread_mutex_init(&ctx.lock_eat, NULL);
    pthread_mutex_init(&ctx.lock_death, NULL);
    return (ctx);
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

void    *philos_routine(void *philo)
{
    t_context   *ctx;

    ctx = *get_ctx_ref();
    while(stop_dinner(ctx, philo) != TRUE)
    {
        dinner_action(ctx, philo);
        sleep_action(ctx, philo);
        think_action(ctx, philo);
    }
    return (NULL);
}

void    begin_dinner(t_context *ctx, t_philo *philos)
{
    int i;

    i = -1;
    save_ctx_ref(ctx);
    while(++i < ctx->num_of_philo)
        pthread_create(&philos[i].id, NULL, &philos_routine, &philos[i]);
}

t_bool all_satisfied(t_context *ctx, t_philo *philos)
{
    t_bool satisfied;

    satisfied = FALSE;
    pthread_mutex_lock(&ctx->lock_eat);
    if (philos[0].meals == ctx->num_of_time_eat)
        satisfied = TRUE;
    pthread_mutex_unlock(&ctx->lock_eat);
    return (satisfied);
}

t_bool starved_death(t_context *ctx, t_philo *philo)
{
    size_t last_meal;

    pthread_mutex_lock(&ctx->lock_eat);
    last_meal = timestamp_in_ms() - philo->last_meal;
    pthread_mutex_unlock(&ctx->lock_eat);
    return (last_meal > ctx->time_to_die);
}

void    throw_death(t_context *ctx, t_philo *philo)
{
    pthread_mutex_lock(&ctx->lock_death);
    ctx->philo_death = TRUE;
    pthread_mutex_unlock(&ctx->lock_death);
    state_log(ctx, philo, DEATH);
}

t_bool  all_alive(t_context *ctx, t_philo *philos)
{
    int i;

    i = -1;
    while (++i < ctx->num_of_philo)
    {
        if (starved_death(ctx, &philos[i]))
            return (FALSE);
    }
    return (TRUE);
}

void    *watcher_routine(void *philos)
{
    t_context   *ctx;

    ctx = *get_ctx_ref();
    while (all_satisfied(ctx, philos) != TRUE)
    {
        if (all_alive(ctx, philos) != TRUE)
        {
            throw_death(ctx, philos);
            return (NULL);
        }
        usleep(1000);
    }
    return (NULL);
}

pthread_t    create_watcher(t_philo *philos)
{
    pthread_t   watcher;

    pthread_create(&watcher, NULL, &watcher_routine, philos);
    return (watcher);
}

int main(int argc, char **argv)
{
    t_context   ctx;
    t_mutex     *forks;
    t_philo     *philos;
    pthread_t   watcher;

    (void)argc;
    ctx = init_context(argv);
    forks = create_forks(&ctx);
    philos = create_philos(&ctx, forks);
    begin_dinner(&ctx, philos);
    watcher = create_watcher(philos);
    //colocar em loop while.
    for(int i = 0; i < ctx.num_of_philo; i++){
        pthread_join(philos[i].id, NULL);
    }
    pthread_join(watcher, NULL);
    free(philos);
    free(forks);
}
