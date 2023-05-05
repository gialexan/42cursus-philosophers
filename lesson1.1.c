/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lesson1.1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 22:05:57 by gialexan          #+#    #+#             */
/*   Updated: 2023/05/04 22:56:43 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

/*
 * Criar threads com laço de repetição
*/

int counter = 0;
// Struct mutex.
pthread_mutex_t mutex;

void    *routine(void *arg)
{
    // Condição de corrida
    for (int i = 0; i < 10000000; i++)
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
    pthread_t th[5];

    // Iniciar mutex
    pthread_mutex_init(&mutex, NULL);

    // Criar threads
    for (int i = 0; i < 5; i++)
    {
        pthread_create(&th[i], NULL, &routine, NULL);
        printf("Thread %d começou\n", i);
    }
    // Aguardar as thread finalizarem
    for (int i = 0; i < 5; i++)
    {
        pthread_join(th[i], NULL);
        printf("Thread %d encerrou execução\n", i);
    }
    // Destruir mutex
    pthread_mutex_destroy(&mutex);

    printf("Value of counter: %d\n", counter);
    return (0);
}
