/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 19:53:26 by gialexan          #+#    #+#             */
/*   Updated: 2023/05/11 21:32:53 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int min(int a, int b)
{
    if (a < b)
        return (a);
    return (b);
}

int max(int a, int b)
{
    if (a > b)
        return (a);
    return (b);
}

int    mssleep(size_t ms)
{
    size_t    start;

    start = timestamp_in_ms();
    while (ms > timestamp_in_ms() - start)
        usleep(100);
    return (0);
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
