/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:41:24 by gialexan          #+#    #+#             */
/*   Updated: 2023/05/10 23:10:49 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t timestamp_in_ms(void);

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
    printf("%ld Philosopher %d is %s\n", elapsed, philo->name, status);

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
        philos[i].action = -1;
        philos[i].meals = -1;
        philos[i].last_meal = -1;
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
    ctx.num_of_philo = 2;
    ctx.time_to_die = 400;
    ctx.time_to_eat = 200;
    ctx.time_to_sleep = 100;
    ctx.num_of_time_eat = 3;
    pthread_mutex_init(&ctx.lock_log, NULL);
    pthread_mutex_init(&ctx.lock_eat, NULL);
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
    while(++i < ctx->num_of_philo)
        pthread_mutex_init(&forks[i], NULL);
    return (forks);
}

void    dinner_action(t_context *ctx, t_philo *philo)
{
    pthread_mutex_lock(philo->fork_first);
    pthread_mutex_lock(philo->fork_second);
    philo->meals++;  
    
    pthread_mutex_lock(&ctx->lock_eat);
    philo->last_meal = timestamp_in_ms();
    pthread_mutex_unlock(&ctx->lock_eat);

    mssleep(ctx->time_to_eat);

    pthread_mutex_unlock(philo->fork_first);
    pthread_mutex_unlock(philo->fork_second);
}

void    sleep_action(t_context *ctx, t_philo *philo)
{
    state_log(ctx, philo, SLEEP);
    philo->action = SLEEPING;
    mssleep(ctx->time_to_sleep);
}

void    think_action(t_context *ctx, t_philo *philo)
{
    state_log(ctx, philo, THINK);
    philo->action = THINKING;
}

void    *philos_routine(void *philo)
{
    int         i;
    t_context   *ctx;

    i = -1;
    ctx = *get_ctx_ref();
    while(++i < ctx->num_of_time_eat)
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
    //watcher = create_watcher(philos);
    begin_dinner(&ctx, philos);
    for(int i = 0; i < ctx.num_of_philo; i++)
        pthread_join(philos[i].id, NULL);
    //pthread_join(watcher, NULL);
}

/*
void    *watcher_routine(void *args)
{
    int         i;
    t_context   *ctx;
    t_philo     *philos;
    
    i = -1;
    philos = args;
    ctx = *get_ctx_ref();
    (void)philos;
    while (++i < ctx->num_of_philo)
    {
        
    }
    return (NULL);
}

pthread_t    create_watcher(t_philo *philos)
{
    pthread_t   watcher;

    pthread_create(&watcher, NULL, &watcher_routine, philos);
    return (watcher);
}
*/