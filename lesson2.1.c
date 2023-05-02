/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lesson2.1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:59:06 by gialexan          #+#    #+#             */
/*   Updated: 2023/05/02 15:31:18 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/wait.h>
#include <sys/types.h>

/*
 * Diferença entre threads e processos
 *
 * Diferente de um processo, as threads neste exemplo 
 * compartilham a mesma memória do processo pai. Desta
 * forma quando routine() incrementar x, mudara o estado da variável
 * e todos que acessarem a memória da variável terão o valor modificado de 5 para 6.
 * 
 * Diferente de threds, quando um novo processo é criado com fork()
 * ele possui uma memória independete do processo pai, sendo assim qualquer
 * alteração feita no processo filho não afetara o estado do processo pai.
 * OBS: Quando processo é criado usando fork(), o novo processo recebe uma cópia do processo pai.
 * 
*/

/* Thresds

// Variável global.
int x = 5;

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