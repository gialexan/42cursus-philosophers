/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:41:24 by gialexan          #+#    #+#             */
/*   Updated: 2023/05/05 19:14:31 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo *create_philoshopers(t_context *ctx)
{
    int     i;
    t_philo *philos;

    i = -1;
    philos = malloc(ctx->num_of_philo * sizeof(t_philo));
    while (++i <= ctx->num_of_philo)
    {
        philos[i].test = i + 1;
        philos[i].fork_right;
        printf("coloquei %d\n", i + 1);
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

int main(int argc, char **argv)
{
    t_context   ctx;
    t_philo     *philos;

    ctx = init_context(argv);
    philos = create_philoshopers(&ctx);


    int i = 0;
    while (i <= ctx.num_of_philo)
    {
        printf("test: %d\n", philos[i].test);
        i++;
    }

}