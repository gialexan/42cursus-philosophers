/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lesson3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:39:32 by gialexan          #+#    #+#             */
/*   Updated: 2023/05/04 22:58:40 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

/*
 * Condição de corrida (Race Condition) entre threads.
 * 
 * Condição de corrida (Race Condition) é um problema que ocorre quando duas ou mais threads
 * acessam simultaneamente o mesmo espaço de memória compartilhado, podendo levar a resultados 
 * inesperados ou até mesmo corromper os dados. Isso acontece quando a sincronização das threads 
 * não é tratada adequadamente e cada thread executa de forma independente, sem levar em consideração 
 * a execução de outras threads no mesmo espaço de memória.
*/

int counter = 0;

void    *routine(void *arg)
{
    // Condição de corrida
    for (int i = 0; i < 1000000; i++)
        counter++;
}

int main(void)
{
    // Struct pthreads
    pthread_t t1, t2;
    
    // Criar threads
    pthread_create(&t1, NULL, &routine, NULL);
    pthread_create(&t2, NULL, &routine, NULL);

    // Aguardar as thread finalizarem
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Value of counter: %d\n", counter);
    return (0);
}
