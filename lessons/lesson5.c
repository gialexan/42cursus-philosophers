/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lesson5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 19:18:12 by gialexan          #+#    #+#             */
/*   Updated: 2023/05/05 10:33:24 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

/*
 * Obter valor de retorno de threads através da função pthread_join.
*/

void    *roll_dice(void *arg)
{
    int value;
    int *result;

    value = (rand() % 6) + 1;
    result = malloc(sizeof(int));
    
    // Salva valor da variável value no ponteiro.
    *result = value;
    printf("-> Valor pseudoaleatório: %d\n", value);
    printf("-> Valor colocado no ptr result: %d / localização memória do ptr: %p\n", *result, result);
    return ((void *)result);
}

int main(void)
{
    // Struct pthreads
    pthread_t t1;
    
    // Variável que vai armazenar resultado da thread.
    int *result;

    // srand() é usado para inicializar o gerador de números pseudoaleatórios
    // time() retorna a hora atual do sistema em segundos
    srand(time(NULL));

    // Criar threads
    pthread_create(&t1, NULL, &roll_dice, NULL);

    // Aguardar as thread finalizarem
    // Segundo parêmetro é variável que foi apontar para resultado da thread.
    pthread_join(t1, (void **)&result);

    printf("<- Valor colocado no ptr result: %d / localização memória do ptr %p\n", *result, result);
    free(result);
    return (0);
}
