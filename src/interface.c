/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 19:59:26 by gialexan          #+#    #+#             */
/*   Updated: 2023/05/11 22:11:27 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_context   **get_ctx_ref(void)
{
    static t_context *ctx;

    return (&ctx);
}

void    save_ctx_ref(t_context *ctx)
{
    t_context   **save_ctx;

    save_ctx = get_ctx_ref();
    *save_ctx = ctx;
}
