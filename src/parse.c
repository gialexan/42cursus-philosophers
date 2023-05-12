/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 07:55:57 by gialexan          #+#    #+#             */
/*   Updated: 2023/05/12 11:08:14 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool  check_args(int argc, char **argv)
{
    int i;

    i = 0;
    if (argc < 5 || argc > 6 || to_int(argv[1]) < 1)
    {
        printf("Invalid Argument!\n");
        return (FALSE);
    }
    while (++i < argc)
    {
        if (to_int(argv[i]) == INVALID_NUMBER)
        {
            printf("Invalid Argument!\n");
            return (FALSE);
        }
    }
    return (TRUE);
}

int	to_int(const char *nptr)
{
	int         i;
	long int    res;
	int         sign;

	i = 0;
	res = 0;
	sign = 1;
	while ((nptr[i] >= '\t' && nptr[i] <= '\r') || (nptr[i] == ' '))
		i++;
	if (nptr[i] == '-')
		sign = sign * -1;
	if (nptr[i] == '-' || nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = res * 10 + nptr[i] - '0';
        if (res > INT_MAX && sign == 1)
            return (-1);
        if (res > INT_MIN && sign == -1)
            return (-1);
		i++;
	}
	return ((int)res * sign);
}
