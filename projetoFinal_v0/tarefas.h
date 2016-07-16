/** \file tarefas.h
 * \brief   Cabeçalho de Funções para manipulação das tarefas.
 *
 * \author  Sérgio Luiz Martins Jr.
 * \author  Marcos Vinícius Leal da Silva
 * \date    16/07/16
 * \version 1.0
 *
 * A more elaborated file description.
 */

#ifndef TAREFAS_H_INCLUDED
#define TAREFAS_H_INCLUDED

#include <inttypes.h>

/** \enum ESTADO_TAREFA
 * Indica qual é o estado da tarefa, sendo:
 */


typedef enum{
    OCIOSA,     /// < Nada a fazer >
    EXECUTANDO, /// < Em execução >
    PRONTA,     /// < Pronta para ser executada >
    PARADA      /// < Tarefa parada por outra com maior prioridade >
} ESTADO_TAREFA;

typedef struct tarefas tarefa_t;

tarefa_t* cria_tarefa();

uint8_t tarefa_get_id(tarefa_t* tarefa);
uint64_t tarefa_get_duracao(tarefa_t* tarefa);
uint64_t tarefa_get_periodo(tarefa_t* tarefa);

void tarefa_set_estado(tarefa_t* tarefa, ESTADO_TAREFA estado);
ESTADO_TAREFA tarefa_get_estado(tarefa_t* tarefa);

#endif // TAREFAS_H_INCLUDED
