/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lesson1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 09:03:51 by gialexan          #+#    #+#             */
/*   Updated: 2023/05/02 15:55:44 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

/*
 * Criar e testar threads.
*/

void    *routine(void *arg)
{
    printf("Test from threads\n");
    sleep(3);
    printf("Ending thread\n");
}

int main(void)
{
    // Struct pthreads
    pthread_t t1, t2;
    
    // Criar threads 
    pthread_create(&t1, NULL, &routine, NULL);
    pthread_create(&t2, NULL, &routine, NULL);

    // Aguardar as threads finalizarem 
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return (0);
}
