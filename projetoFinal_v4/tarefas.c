/** \file tarefas.c
 * \brief   Fun��es para manipula��o das tarefas.
 *
 * \author  S�rgio Luiz Martins Jr.
 * \author  Marcos Vin�cius Leal da Silva
 * \date    20/07/16
 * \version 1.0
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include "tarefas.h"

struct tarefas{            /// Identificador da tarefa
    uint8_t id;            /// Quanto tempo a tarefa ser� totalmente executada - C
    uint64_t duracao;      /// Quanto tempo at� a tarefa ser executada novamente - T
    uint64_t periodo;      /// Em que tempo a variavel come�ou a ser executada
    uint32_t tempoInicio;  /// Quantos ciclos a tarefa executou
    uint32_t tempoExe;     /// Quantos "jobs" est�o na fila - Para quando os periodos T se acumulam
    uint32_t nmrExe;       /// Qual estado da tarefa
    ESTADO_TAREFA estado;
};

// Fun��o cria tarefa
tarefa_t* cria_tarefa(uint8_t id, uint64_t duracao, uint64_t periodo)
{
    tarefa_t* p_tarefa;

    p_tarefa = (tarefa_t*) malloc(sizeof(tarefa_t));
    if(p_tarefa == NULL){
        perror("Erro ao alocar tarefa:");
        exit(EXIT_FAILURE);
    }

    p_tarefa->id = id;
    p_tarefa->duracao = duracao;
    p_tarefa->periodo = periodo;
    p_tarefa->estado = PRONTA;
    p_tarefa->tempoExe = 0;
    p_tarefa->nmrExe = 0;

    return p_tarefa;
}

uint8_t tarefa_get_id(tarefa_t* tarefa)
{
    uint8_t id;

    // Verifica se o ponteiro de tarefa � v�lido
    if (tarefa == NULL) {
        fprintf(stderr, "tarefa_get_id: Ponteiro invalido\n");
        exit(EXIT_FAILURE);
    }

    id = tarefa->id;

    return id;
}

uint64_t tarefa_get_duracao(tarefa_t* tarefa)
{
    uint64_t duracao;

    // Verifica se o ponteiro de tarefa � v�lido
    if (tarefa == NULL) {
        fprintf(stderr, "tarefa_get_duracao: Ponteiro invalido\n");
        exit(EXIT_FAILURE);
    }

    duracao = tarefa->duracao;

    return duracao;
}

uint64_t tarefa_get_periodo(tarefa_t* tarefa)
{
    uint64_t periodo;

    if (tarefa == NULL) {
        fprintf(stderr, "tarefa_get_periodo: Ponteiro invalido\n");
        exit(EXIT_FAILURE);
    }

    periodo = tarefa->periodo;

    return periodo;
}

void tarefa_set_estado(tarefa_t* tarefa, ESTADO_TAREFA estado)
{
    // Verifica se o ponteiro de tarefa � v�lido
    if (tarefa == NULL) {
        fprintf(stderr, "tarefa_set_estado: Ponteiro invalido\n");
        exit(EXIT_FAILURE);
    }

    tarefa->estado = estado;
}

ESTADO_TAREFA tarefa_get_estado(tarefa_t* tarefa)
{
    ESTADO_TAREFA estado;

    if (tarefa == NULL) {
        fprintf(stderr, "tarefa_get_estado: Ponteiro invalido\n");
        exit(EXIT_FAILURE);
    }

    estado = tarefa->estado;

    return estado;
}

void ordena_tarefas(lista_enc_t* lista_tarefas)
{
    tarefa_t* p_tarefa;
    tarefa_t* p_tarefa_next;
    no_t* p_no;
    int tamanho, i;

    if (lista_tarefas == NULL) {
        fprintf(stderr, "ordena_tarefas: Ponteiro invalido\n");
        exit(EXIT_FAILURE);
    }

    for(tamanho = tamanho_lista(lista_tarefas); tamanho>1; tamanho--){
        p_no = obter_cabeca(lista_tarefas);
        for(i=0; i<(tamanho-1); i++){
            p_tarefa = (tarefa_t*) obter_dado(p_no);
            p_no = obtem_proximo(p_no);
            p_tarefa_next = (tarefa_t*) obter_dado(p_no);
            if(tarefa_get_periodo(p_tarefa) > tarefa_get_periodo(p_tarefa_next)){
                swap_nos(lista_tarefas, obtem_anterior(p_no));
            }
        }
    }
}

void imprime_tarefas(lista_enc_t* listaTarefas)
{
    no_t* p_no;
    tarefa_t* p_tarefa;
    char estados[4][20] = { {"Ociosa"},
                            {"Executando"},
                            {"Pronta"},
                            {"Parada"}
                          };
    int periodo;
    int duracao;

    // Verifica se o ponteiro de lista de tarefa � v�lido
    if (listaTarefas == NULL) {
        fprintf(stderr, "imprime_tarefas: Ponteiro invalido\n");
        exit(EXIT_FAILURE);
    }

    p_no = obter_cabeca(listaTarefas);

    while(p_no){
        p_tarefa = (tarefa_t*) obter_dado(p_no);

        printf("Tarefa %d - Estado %s \t", tarefa_get_id(p_tarefa), estados[(int)tarefa_get_estado(p_tarefa)]);
        periodo = tarefa_get_periodo(p_tarefa);
        duracao = tarefa_get_duracao(p_tarefa);
        printf("C: %d - T: %d\n", duracao, periodo);

        p_no = obtem_proximo(p_no);
    }
}

tarefa_t* retorna_tarefa_prio(lista_enc_t* listaTarefas)
{
    tarefa_t *p_tarefa;
    no_t *p_no;

    if (listaTarefas == NULL) {
        fprintf(stderr, "retorna_tarefa_prio: Ponteiro invalido\n");
        exit(EXIT_FAILURE);
    }

    p_no = obter_cabeca(listaTarefas);

    while(p_no){
        p_tarefa = (tarefa_t*) obter_dado(p_no);
        if(tarefa_get_estado(p_tarefa) != OCIOSA){
            return p_tarefa;
        }
        p_no = obtem_proximo(p_no);
    }

    return NULL;
}

void update_tarefas(lista_enc_t* listaTarefas, uint32_t tempo, FILE *fp)
{
    no_t* p_no;
    tarefa_t* p_tarefa;

    // Verifica se o ponteiro de tarefa � v�lido
    if (listaTarefas == NULL) {
        fprintf(stderr, "update_tarefas: Ponteiro invalido\n");
        exit(EXIT_FAILURE);
    }

    p_no = obter_cabeca(listaTarefas);

    while(p_no){
        p_tarefa = (tarefa_t*) obter_dado(p_no);

        if(!(tempo%p_tarefa->periodo)){
            p_tarefa->nmrExe++;
            // Desenha seta para cima
            gannt_seta_cima(fp,tarefa_get_id(p_tarefa),tempo);
            if(p_tarefa->estado == OCIOSA){
                p_tarefa->estado = PRONTA;
            }
        }
        p_no = obtem_proximo(p_no);
    }
}

void tarefa_set_inicio(tarefa_t* tarefa, uint32_t tempo)
{
    // Verifica se o ponteiro de tarefa � v�lido
    if (tarefa == NULL) {
        fprintf(stderr, "tarefa_set_inicio: Ponteiro invalido\n");
        exit(EXIT_FAILURE);
    }

    tarefa->tempoInicio = tempo;
    tarefa->estado = EXECUTANDO;
}

uint32_t tarefa_get_inicio(tarefa_t* tarefa)
{
    // Verifica se o ponteiro de tarefa � v�lido
    if (tarefa == NULL) {
        fprintf(stderr, "tarefa_get_inicio: Ponteiro invalido\n");
        exit(EXIT_FAILURE);
    }

    return tarefa->tempoInicio;
}

void tarefa_set_pausa(tarefa_t* tarefa, uint32_t tempo)
{
    // Verifica se o ponteiro de tarefa � v�lido
    if (tarefa == NULL) {
        fprintf(stderr, "tarefa_set_pausa: Ponteiro invalido\n");
        exit(EXIT_FAILURE);
    }

    tarefa->tempoExe = tarefa->tempoExe + (tempo - tarefa->tempoInicio);
    tarefa->estado = PARADA;
}

int tarefa_checa_termino(tarefa_t* tarefa, uint32_t tempo)
{
    // Verifica se o ponteiro de tarefa � v�lido
    if (tarefa == NULL) {
        fprintf(stderr, "tarefa_checa_termino: Ponteiro invalido\n");
        exit(EXIT_FAILURE);
    }

    // Necess�rio levar em considera��o a PAUSA
    if((tempo-tarefa->tempoInicio)+tarefa->tempoExe == tarefa->duracao){
        tarefa->nmrExe--;
        tarefa->tempoExe = 0;
        if(!tarefa->nmrExe){    // Se a tarefa n�o tiver mais execu��es na fila
            tarefa->estado = OCIOSA;
        }else tarefa->estado = PRONTA;
        return 1;
    }

    return 0;
}

uint64_t calcMDC(uint64_t x, uint64_t y)
{
    uint64_t res;

    do{
        res = x%y;

        x = y;
        y = res;
    }while(res);

    return x;
}

uint64_t calcMMC(uint64_t x, uint64_t y)
{
    return (x*y)/calcMDC(x,y);
}

uint64_t tarefas_calcMMC(lista_enc_t* listaTarefas)
{
    tarefa_t* p_tarefa;
    no_t* p_no;
    no_t* p_no_ant;
    uint64_t mmc;

    if (listaTarefas == NULL) {
        fprintf(stderr, "tarefas_calcMMC: Ponteiro invalido\n");
        exit(EXIT_FAILURE);
    }

    p_no_ant = obter_cabeca(listaTarefas);
    p_tarefa = (tarefa_t*) obter_dado(p_no_ant);
    mmc = p_tarefa->periodo;
    p_no = obtem_proximo(p_no_ant);
    while(p_no){
        p_tarefa = (tarefa_t*) obter_dado(p_no);
        mmc = calcMMC(mmc, p_tarefa->periodo);

        p_no_ant = p_no;
        p_no = obtem_proximo(p_no);
    }

    return mmc;
}

void gannt_cabecalho(FILE *fp, uint8_t numTarefas, uint32_t escalaTempo)
{
    if (fp == NULL) {
        fprintf(stderr, "gannt_cabecalho: Ponteiro invalido\n");
        exit(EXIT_FAILURE);
    }

    fprintf(fp, "\\documentclass[legalpaper,10pt]{article}\n");
    fprintf(fp, "\\usepackage[landscape]{geometry}\n");
    fprintf(fp, "\\usepackage[utf8]{inputenc}\n");
    fprintf(fp, "\\usepackage[brazil]{babel}\n\n");

    fprintf(fp, "\\usepackage{listings}\n");
    fprintf(fp, "\\usepackage{listingsutf8}\n\n");

    fprintf(fp, "\\usepackage{rtsched}\n\n");

    fprintf(fp, "\\begin{document}\n\n");

    fprintf(fp, "\\begin{figure}[h]\n");
    fprintf(fp, "\\centering\n\n");

    fprintf(fp, "\t%% Cria ambiente, %d tarefas, escala de tempo at� %d\n", numTarefas+1, escalaTempo);
    fprintf(fp, "\t\\begin{RTGrid}[nosymbols=1,width=25cm]{%d}{%d}\n\n", numTarefas+1, escalaTempo);
}

void gannt_finaliza_cabecalho(FILE *fp)
{
    if (fp == NULL) {
        fprintf(stderr, "gannt_finaliza_cabecalho: Ponteiro invalido\n");
        exit(EXIT_FAILURE);
    }

    fprintf(fp, "\n\t\\end{RTGrid}\n\n");

    fprintf(fp, "\\caption{Exemplo de escalonamento para tarefas.}\n");
    fprintf(fp, "\\label{fig:ex1}\n");
    fprintf(fp, "\\end{figure}\n");
    fprintf(fp, "\\end{document}");
}

void gannt_nomenclatura(FILE *fp, lista_enc_t* lista_tarefas)
{
    tarefa_t* p_tarefa;
    no_t* p_no;
    int tamanho, i;

    if (fp == NULL || lista_tarefas == NULL){
        fprintf(stderr, "gannt_nomenclatura: Ponteiro invalido\n");
        exit(EXIT_FAILURE);
    }

    fprintf(fp, "\t%% Nomenclatura das tarefas\n");

    tamanho = tamanho_lista(lista_tarefas);

    fprintf(fp, "\t\\RowLabel{%d}{CPU}\n", tamanho+1);

    p_no = obter_cabeca(lista_tarefas);

    for(i = 0; i < tamanho; i++){
        p_tarefa = (tarefa_t*) obter_dado(p_no);
        fprintf(fp, "\t\\RowLabel{%d}{$\\tau_%d$}\n", tarefa_get_id(p_tarefa), tarefa_get_id(p_tarefa));
        p_no = obtem_proximo(p_no);
    }

    fprintf(fp, "\n");
}

void gannt_seta_cima(FILE *fp, uint8_t id, uint32_t tempo)
{
    if (fp == NULL) {
        fprintf(stderr, "gannt_seta_cima: Ponteiro invalido\n");
        exit(EXIT_FAILURE);
    }

    fprintf(fp, "\t\\TaskArrival{%d}{%d}\n", id, tempo);
}

void gannt_seta_baixo(FILE *fp, uint8_t id, uint32_t tempo)
{
    if (fp == NULL) {
        fprintf(stderr, "gannt_seta_baixo: Ponteiro invalido\n");
        exit(EXIT_FAILURE);
    }

    fprintf(fp, "\t\\TaskDeadline{%d}{%d}\n", id, tempo);
}

void gannt_quadrado(FILE *fp, uint8_t id, uint32_t inicio, uint32_t fim)
{
    if (fp == NULL) {
        fprintf(stderr, "gannt_quadrado: Ponteiro invalido\n");
        exit(EXIT_FAILURE);
    }

    fprintf(fp, "\t\\TaskExecution{%d}{%d}{%d}\n", id, inicio, fim);
}

void desaloca_lista_tarefas(lista_enc_t* lista_tarefas)
{
    no_t* p_no;
    tarefa_t* p_tarefa;

    if(lista_tarefas == NULL){
        perror("Desaloca lista de tarefas, lista invalida:");
        exit(EXIT_FAILURE);
    }

    while(!lista_vazia(lista_tarefas)){
        p_no = remover_cabeca(lista_tarefas);
        p_tarefa = (tarefa_t*) obter_dado(p_no);
        free(p_tarefa);
        free(p_no);
    }

    free(lista_tarefas);
}
