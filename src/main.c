/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:41:24 by gialexan          #+#    #+#             */
/*   Updated: 2023/05/09 15:35:18 by gialexan         ###   ########.fr       */
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

t_context   **get_ctx(void)
{
    static t_context *ctx;

    return (&ctx);
}

void    save_ctx_ref(t_context *ctx)
{
    t_context   **save_ctx;
    
    save_ctx = get_ctx();
    *save_ctx = ctx;
}

t_philo *create_philos(t_context *ctx, t_fork *forks)
{
    int         i;
    t_philo     *philos;
    const char  *names[] = {"Sócrates", "Platão", "Aristóteles"};

    i = -1;
    philos = malloc(ctx->num_of_philo * sizeof(t_philo));
    if (!philos)
        return (NULL);
    while(++i < ctx->num_of_philo)
    {
        philos[i].id = -1;
        philos[i].name = names[i];
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

int get_time(t_context *ctx)
{
    t_time      end_time;
    int         current_time;

    gettimeofday(&end_time, NULL);
    current_time = end_time.tv_sec - ctx->start_time.tv_sec;
    return (current_time);
}

void    *routine(void *arg)
{
    int         i;
    t_context   *ctx;
    t_philo     *philo;
    
    i = -1;
    ctx = *get_ctx();
    philo = (t_philo *)arg;
    while (++i < ctx->num_of_time_eat)
    {
        pthread_mutex_lock(philo->fork_first);
        pthread_mutex_lock(philo->fork_second);

        printf("%d Philosopher %s is eating\n", get_time(ctx), philo->name);
        sleep(2);

        pthread_mutex_unlock(philo->fork_first);
        pthread_mutex_unlock(philo->fork_second);

        printf("%d Philosopher %s is sleeping\n", get_time(ctx), philo->name);
        sleep(1);

        printf("%d Philosopher %s is thinking\n", get_time(ctx), philo->name);
    }
}

void    begin_dinner(t_context *ctx, t_philo *philos)
{
    int i;

    i = -1;
    save_ctx_ref(ctx);
    while (++i < ctx->num_of_philo)
        pthread_create(&philos[i].id, NULL, &routine, &philos[i]);
}

int main(int argc, char **argv)
{
    t_context   ctx;
    t_philo     *philos;
    t_fork      *forks;

    ctx = init_context(argv);
    forks = create_forks(&ctx);
    philos = create_philos(&ctx, forks);
    begin_dinner(&ctx, philos);

    for (int i = 0; i < ctx.num_of_philo; i++)
        pthread_join(philos[i].id, NULL);
}





// int main()
// {
//     t_time start, end;

//     gettimeofday(&start, NULL);

//     while (1)
//     {
//         sleep(3);
//         gettimeofday(&end, NULL);
//         printf("The elapsed time is %ld seconds\n", end.tv_sec - start.tv_sec);
//     }
//     return (0);
// }


/* teste sobre qual garfo está disponível para cada philo.

     int i = -1;
    while (++i < ctx.num_of_philo)
        printf("id: %ld / fork_right: %p / fork_left: %p\n", philos[i].id, (void *)philos[i].fork_first, (void *)philos[i].fork_second);
*/