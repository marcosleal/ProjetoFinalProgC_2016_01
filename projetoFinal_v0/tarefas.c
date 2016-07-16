// Changelog
//
//  16/07/2016 - Cria��o do dado
//

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include "tarefas.h"

struct tarefas{
    uint8_t id;            // Identificador da tarefa
    uint64_t duracao;      // Quanto tempo a tarefa ser� totalmente executada - C
    uint64_t periodo;      // Quanto tempo at� a tarefa ser executada novamente - T
    ESTADO_TAREFA estado;  // Qual estado da tarefa
};

// Fun��o cria tarefa - Precisamos decidir se ela j� vai ser criada e definida ou vamos ter fun��es de setar
tarefa_t* cria_tarefa()
{
    tarefa_t* p_tarefa;

    p_tarefa = (tarefa_t*) malloc(sizeof(tarefa_t));
    if(p_tarefa == NULL){
        perror("Erro ao alocar tarefa:");
        exit(EXIT_FAILURE);
    }

    return p_tarefa;
}

uint8_t tarefa_get_id(tarefa_t* tarefa)
{
    uint8_t id;

    // Verifica se o ponteiro de tarefa � v�lido



    id = tarefa->id;

    return id;
}

uint64_t tarefa_get_duracao(tarefa_t* tarefa)
{
    uint64_t duracao;

    // Verifica se o ponteiro de tarefa � v�lido


    duracao = tarefa->duracao;

    return duracao;
}

uint64_t tarefa_get_periodo(tarefa_t* tarefa)
{
    uint64_t periodo;

    periodo = tarefa->periodo;

    return periodo;
}

void tarefa_set_estado(tarefa_t* tarefa, ESTADO_TAREFA estado)
{
    // Verifica se o ponteiro de tarefa � v�lido

    tarefa->estado = estado;
}

ESTADO_TAREFA tarefa_get_estado(tarefa_t* tarefa)
{
    ESTADO_TAREFA estado;

    estado = tarefa->estado;

    return estado;
}
