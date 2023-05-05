/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lesson2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 12:13:41 by gialexan          #+#    #+#             */
/*   Updated: 2023/05/03 17:37:34 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/wait.h>
#include <sys/types.h>

/*
 * Diferença entre threads e processos.
 *
 * Cada processo tem seu próprio espaço de endereçamento e identificador de processo, 
 * enquanto as threads compartilham o mesmo espaço de endereçamento do processo pai.
 * 
 * Processos são mais pesados e têm um consumo de recursos maior do que as threads.
 * 
 * Threads são mais eficientes em termos de uso de recursos e permitem maior paralelismo em um programa.
 * 
 * Threads podem compartilhar variáveis e recursos, mas devem ser cuidadosamente gerenciadas para evitar 
 * condições de corrida e outros problemas de concorrência.
*/

/* Threads

void    *routine(void *arg)
{
    printf("Id process %d\n", getpid());
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
    return (0);
}
*/

/* Processos

int main(void)
{
    int pid;
    
    // Criar processos filhos
    pid = fork();
    if (pid == -1)
        return (1);

    // Exibi id dos processos criados
    printf("Id process %d\n", getpid());
    if (pid != 0)
        wait(NULL);
    return (0);
}
*/
