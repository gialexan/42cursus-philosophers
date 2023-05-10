/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:41:24 by gialexan          #+#    #+#             */
/*   Updated: 2023/05/10 10:39:16 by gialexan         ###   ########.fr       */
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

int get_current_time(t_context *ctx)
{
    t_time      end_time;
    int         current_time;

    gettimeofday(&end_time, NULL);
    current_time = end_time.tv_sec - ctx->start_time.tv_sec;
    return (current_time);
}

void    show_info(t_context *ctx, t_philo *philos)
{
    pthread_mutex_lock(&ctx->lock_msg);
    printf("%d Philosopher %s is eating\n", get_current_time(ctx), philos->name);
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
    const char  *names[] = {"Sócrates", "Platão", "Aristóteles", "Gialexan", "Shelson", "Marcelo", "Ygor"};

    i = -1;
    philos = malloc(ctx->num_of_philo * sizeof(t_philo));
    if (!philos)
        return (NULL);
    while(++i < ctx->num_of_philo)
    {
        philos[i].id = -1;
        philos[i].name = names[i];
        philos[i].philo_action = -1;
        philos[i].last_dinner = -1;
        philos[i].fork_first = &forks[ft_min(i, (i + 1) % ctx->num_of_philo)];
        philos[i].fork_second = &forks[ft_max(i, (i + 1) % ctx->num_of_philo)];
    }
    return (philos);
}

t_context   init_context(char **argv)
{
    t_context   ctx;

    ctx.num_of_philo = 2;
    ctx.time_to_eat = 200;
    ctx.time_to_sleep = 100;
    ctx.num_of_time_eat = 3;
    pthread_mutex_init(&ctx.lock_msg, NULL);
    gettimeofday(&ctx.start_time, NULL);
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

void    dinner_action(t_context *ctx, t_philo *philos)
{
    pthread_mutex_lock(philos->fork_first);
    pthread_mutex_lock(philos->fork_second);

    show_info(ctx, philos);
    philos->last_dinner = get_current_time(ctx);
    philos->philo_action = EATING;
    sleep(2);

    pthread_mutex_unlock(philos->fork_first);
    pthread_mutex_unlock(philos->fork_second);
}

void    sleep_action(t_context *ctx, t_philo *philos)
{
    show_info(ctx, philos);
    philos->philo_action = SLEEPING;
    sleep(1);
}

void    think_action(t_context *ctx, t_philo *philos)
{
    show_info(ctx, philos);
    philos->philo_action = THINKING;
    sleep(1);
}

void    *philos_routine(void *args)
{
    int         i;
    t_context   *ctx;
    t_philo     *philos;
    
    i = -1;
    ctx = *get_ctx_ref();
    philos = (t_philo *)args;
    while (++i < ctx->num_of_time_eat)
    {
        dinner_action(ctx, philos);
        sleep_action(ctx, philos);
        think_action(ctx, philos);
    }
}

void    *manager_routine(void *args)
{
    
}

void    begin_dinner(t_context *ctx, t_philo *philos)
{
    int i;

    i = -1;
    save_ctx_ref(ctx);
    while (++i < ctx->num_of_philo)
        pthread_create(&philos[i].id, NULL, &philos_routine, &philos[i]);
}

pthread_t    begin_manager(t_philo *philos)
{
    pthread_t   manager;

    pthread_create(&manager, NULL, &manager_routine, &philos);
    return(manager);
}

int main(int argc, char **argv)
{
    t_context   ctx;
    t_fork      *forks;
    t_philo     *philos;
    pthread_t   manager;

    ctx = init_context(argv);
    forks = create_forks(&ctx);
    philos = create_philos(&ctx, forks);
    manager = begin_manager(philos);
    begin_dinner(&ctx, philos);
    pthread_join(manager, NULL);
    for (int i = 0; i < ctx.num_of_philo; i++)
        pthread_join(philos[i].id, NULL);
}

/* teste sobre qual garfo está disponível para cada philo.

     int i = -1;
    while (++i < ctx.num_of_philo)
        printf("id: %ld / fork_right: %p / fork_left: %p\n", philos[i].id, (void *)philos[i].fork_first, (void *)philos[i].fork_second);
*/