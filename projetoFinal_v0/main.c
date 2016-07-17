// Data: 16/07/2016
//
// Objetivo: Criar o TaD que ira ser utilizado para conter as informa��es das tarefas
//

#include <stdio.h>
#include <stdlib.h>

#include "tarefas.h"
#include "lista_enc.h"
#include "no.h"

#define NOME_ARQUIVO "escalonamento.txt"
#define NUM_TAREFAS

int main()
{
    tarefa_t* tarefaTeste;
    lista_enc_t* listaTarefas;
    no_t* no_aux;

    listaTarefas = cria_lista_enc();

    tarefaTeste = cria_tarefa(1, 2, 7);
    no_aux = cria_no((void*) tarefaTeste);
    add_cauda(listaTarefas, no_aux);

    tarefaTeste = cria_tarefa(2, 1, 10);
    no_aux = cria_no((void*) tarefaTeste);
    add_cauda(listaTarefas, no_aux);

    tarefaTeste = cria_tarefa(3, 6, 18);
    no_aux = cria_no((void*) tarefaTeste);
    add_cauda(listaTarefas, no_aux);

    tarefaTeste = cria_tarefa(4, 10, 30);
    no_aux = cria_no((void*) tarefaTeste);
    add_cauda(listaTarefas, no_aux);

    tarefaTeste = cria_tarefa(5, 4, 10);
    no_aux = cria_no((void*) tarefaTeste);
    add_cauda(listaTarefas, no_aux);

    tarefa_set_estado(tarefaTeste, OCIOSA);

    return 0;
}
