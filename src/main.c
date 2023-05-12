/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:41:24 by gialexan          #+#    #+#             */
/*   Updated: 2023/05/12 10:07:06 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
    t_context   ctx;
    t_mutex     *forks;
    t_philo     *philos;
    t_bool      valid;

    valid = check_args(argc, argv);
    if (!valid)
        return (1);
    ctx = init_context(argc, argv);
    forks = create_forks(&ctx);
    philos = create_philos(&ctx, forks);
    begin_dinner(&ctx, philos);
    clear(&ctx, forks, philos);
    return (0);
}

void    *philos_routine(void *philo)
{
    t_context   *ctx;

    ctx = *get_ctx_ref();
    if (ctx->num_of_philo == 1)
    {
        state_log(ctx, philo, TAKE_FORK);
        mssleep(ctx->time_to_die);
        return (NULL);
    }
    while(stop_dinner(ctx, philo) != TRUE)
    {
        dinner_action(ctx, philo);
        sleep_action(ctx, philo);
        think_action(ctx, philo);
    }
    return (NULL);
}
