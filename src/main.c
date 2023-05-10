/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:41:24 by gialexan          #+#    #+#             */
/*   Updated: 2023/05/10 17:41:48 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

int get_curr_time(void)
{
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	return ((tp.tv_sec * 1000) + (tp.tv_usec / 1000));
}

size_t get_ms_time(void)
{
    t_context   *ctx;
    size_t      curr_time;

    ctx = *get_ctx_ref();
    curr_time = get_curr_time();
    return (curr_time - ctx->start_time);
}


void    show_msg(t_context *ctx, t_philo *philo, char *status)
{
    pthread_mutex_lock(&ctx->lock_msg);
    printf("%.3ld Philosopher %s is %s\n", get_ms_time(), philo->name, status);
    pthread_mutex_unlock(&ctx->lock_msg);
}

void    save_ctx_ref(t_context *ctx)
{
    t_context   **save_ctx;
    
    save_ctx = get_ctx_ref();
    *save_ctx = ctx;
}

t_philo *create_philos(t_context *ctx, t_fork *forks)
{
    int         i;
    t_philo     *philos;
    const char  *names[] = {"Aristóteles", "Sócrates", "Platão", "Gialexan", "Shelson", "Marcelo", "Ygor"};

    i = -1;
    philos = malloc(ctx->num_of_philo * sizeof(t_philo));
    if (!philos)
        return (NULL);
    while(++i < ctx->num_of_philo)
    {
        philos[i].id = -1;
        philos[i].name = names[i];
        philos[i].last_meal = -1;
        philos[i].philo_action = -1;
        philos[i].fork_first = &forks[ft_min(i, (i + 1) % ctx->num_of_philo)];
        philos[i].fork_second = &forks[ft_max(i, (i + 1) % ctx->num_of_philo)];
    }
    return (philos);
}

t_context   init_context(char **argv)
{
    t_context   ctx;

    (void)argv;
    ctx.start_time = get_curr_time();
    ctx.num_of_philo = 2;
    ctx.time_to_die = 3;
    ctx.time_to_eat = 200;
    ctx.time_to_sleep = 100;
    ctx.num_of_time_eat = 3;
    pthread_mutex_init(&ctx.lock_msg, NULL);
    return (ctx);
}

t_fork  *create_forks(t_context *ctx)
{
    int     i;
    t_fork  *forks;

    i = -1;
    forks = malloc(ctx->num_of_philo * sizeof(t_fork));
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

    show_msg(ctx, philo, EAT);

    philo->last_meal = get_curr_time();

    usleep(200);

    pthread_mutex_unlock(philo->fork_first);
    pthread_mutex_unlock(philo->fork_second);
}

void    sleep_action(t_context *ctx, t_philo *philo)
{
    show_msg(ctx, philo, SLEEP);
    usleep(100);
}

void    think_action(t_context *ctx, t_philo *philo)
{
    show_msg(ctx, philo, THINK);
    usleep(100);
}

void    *philos_routine(void *philo)
{
    int         i;
    t_context   *ctx;

    i = -1;
    ctx = *get_ctx_ref();
    while (++i < ctx->num_of_time_eat)
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
    while (++i < ctx->num_of_philo)
        pthread_create(&philos[i].id, NULL, &philos_routine, &philos[i]);
}

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
        //printf("---> Current time: %d\n", get_current_time(ctx));

        //printf("---> Last dinner: %d\n", philos[i].last_dinner);

        //printf("----> test: %d\n", get_current_time(ctx) - philos[i].last_dinner);
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
    t_fork      *forks;
    t_philo     *philos;
    pthread_t   watcher;

    (void)argc;
    ctx = init_context(argv);
    forks = create_forks(&ctx);
    philos = create_philos(&ctx, forks);
    watcher = create_watcher(philos);
    begin_dinner(&ctx, philos);
    for (int i = 0; i < ctx.num_of_philo; i++)
        pthread_join(philos[i].id, NULL);
    pthread_join(watcher, NULL);
}

/* teste sobre qual garfo está disponível para cada philo.

     int i = -1;
    while (++i < ctx.num_of_philo)
        printf("id: %ld / fork_right: %p / fork_left: %p\n", philos[i].id, (void *)philos[i].fork_first, (void *)philos[i].fork_second);
*/
