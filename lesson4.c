/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lesson4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:17:12 by gialexan          #+#    #+#             */
/*   Updated: 2023/05/03 17:48:42 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

/*
 * Introdução a mutex
 *
 * Mutex (ou "mutual exclusion") é uma técnica utilizada em programação concorrente 
 * para garantir a exclusividade de acesso a um recurso compartilhado entre threads. 
 * É uma forma de prevenir condições de corrida (race conditions) que podem ocorrer quando 
 * duas ou mais threads tentam acessar o mesmo recurso simultaneamente, podendo levar a resultados 
 * inesperados ou erros no programa.
*/

int counter = 0;
// Struct mutex.
pthread_mutex_t mutex;

void    *routine(void *arg)
{
    // Condição de corrida
    for (int i = 0; i < 1000000; i++)
    {
        // Bloquear o acesso a variável
        pthread_mutex_lock(&mutex);
        counter++;
        // Desbloquear o acesso a variável
        pthread_mutex_unlock(&mutex);
    }
}

int main(void)
{
    // Struct pthreads
    pthread_t t1, t2;
    // Init mutex
    pthread_mutex_init(&mutex, NULL);

    // Criar threads
    pthread_create(&t1, NULL, &routine, NULL);
    pthread_create(&t2, NULL, &routine, NULL);

    // Aguardar as thread finalizarem
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    printf("Value of counter: %d\n", counter);
    return (0);
}