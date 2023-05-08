/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:41:24 by gialexan          #+#    #+#             */
/*   Updated: 2023/05/08 19:47:29 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>


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

t_philo *create_philos(t_context *ctx, t_fork *forks)
{
    int     i;
    t_philo *philos;

    i = -1;
    philos = malloc(ctx->num_of_philo * sizeof(t_philo));
    if (!philos)
        return (NULL);
    while(++i < ctx->num_of_philo)
    {
        philos[i].id = i;
        philos[i].fork_first = &forks[ft_min(i, (i + 1) % ctx->num_of_philo)];
        philos[i].fork_second = &forks[ft_max(i, (i + 1) % ctx->num_of_philo)];
    }
    return (philos);
}

t_context   init_context(char **argv)
{
    t_context   ctx;

    ctx.num_of_philo = 3;
    ctx.time_to_eat = 2;
    ctx.time_to_sleep = 5;
    ctx.num_of_time_eat = 2;
    return (ctx);
}

t_fork  *init_forks(t_context *ctx)
{
    int     i;
    t_fork  *forks;

    i = -1;
    forks = malloc(ctx->num_of_philo * sizeof(t_fork));
    if (!forks)
        return (NULL);
    while(++i < ctx->num_of_philo)
        pthread_mutex_init(&forks[i], NULL);
}

// int main(int argc, char **argv)
// {
//     t_context   ctx;
//     t_philo     *philos;
//     t_fork      *forks;

//     ctx = init_context(argv);
//     forks = init_forks(&ctx);
//     philos = create_philos(&ctx, forks);

//     int i = -1;
//     while (++i < ctx.num_of_philo)
//         printf("id: %ld / fork_right: %p / fork_left: %p\n", philos[i].id, (void *)philos[i].fork_right, (void *)philos[i].fork_left);
// }

#include <sys/time.h>

int main()
{
    struct timeval start, end;
 
    gettimeofday(&start, NULL);
    gettimeofday(&end, NULL);
 
    long seconds = (end.tv_sec - start.tv_sec);
 
    printf("The elapsed time is %ld seconds\n", seconds);
    sleep(5);
    gettimeofday(&end, NULL);
    seconds = (end.tv_sec - start.tv_sec);
    printf("The elapsed time is %ld seconds\n", seconds);
    sleep(1);
    gettimeofday(&end, NULL);
    seconds = (end.tv_sec - start.tv_sec);
    printf("The elapsed time is %ld seconds\n", seconds);
 
    return 0;
}

