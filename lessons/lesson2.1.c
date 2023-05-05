/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lesson2.1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:59:06 by gialexan          #+#    #+#             */
/*   Updated: 2023/05/03 17:37:40 by gialexan         ###   ########.fr       */
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

int x = 5;

/* Threads

void    *routine(void *arg)
{
    x++;
    sleep(2);
    printf("Valor de x: %d\n", x);
}

void    *routine1(void *arg)
{
    sleep(2);
    printf("Valor de x: %d\n", x);
}

int main(void)
{
    // Struct pthreads
    pthread_t t1, t2;

    // Criar threads
    pthread_create(&t1, NULL, &routine, NULL);
    pthread_create(&t2, NULL, &routine1, NULL);

    // Aguardar as thread finalizarem
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    
    // Processo pai
    printf("Valor de x: %d\n", x);
    return (0);
}
*/

/* Processos

int main(void)
{
    int y;
    int pid;

    y = 5;
    // Criar processos filhos
    pid = fork();
    if (pid == -1)
        return (1);
    if (pid == 0)
        y++;
    // Exibi id dos processos criados
    printf("Valor de y: %d\n", y);
    if (pid != 0)
        wait(NULL);
    return (0);
}
*/
