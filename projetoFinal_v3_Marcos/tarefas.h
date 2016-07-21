/** \file tarefas.h
 * \brief   Cabe�alho de Fun��es para manipula��o das tarefas.
 *
 * \author  S�rgio Luiz Martins Jr.
 * \author  Marcos Vin�cius Leal da Silva
 * \date    20/07/16
 * \version 1.0
 *
 */

#ifndef TAREFAS_H_INCLUDED
#define TAREFAS_H_INCLUDED

#include <inttypes.h>
#include "lista_enc.h"

/** \enum ESTADO_TAREFA
 * Indica qual � o estado da tarefa, sendo:
 */
typedef enum{
    OCIOSA,     ///< Nada a fazer
    EXECUTANDO, ///< Em execu��o
    PRONTA,     ///< Pronta para ser executada
    PARADA      ///< Tarefa parada por outra com maior prioridade
} ESTADO_TAREFA;

/** \struct tarefas tarefas.h "tarefas.h"
 *   \brief Estrutura das tarefas
 *
 * Todas as tarefas cont�m um identificador (id), dura��o (C), per�odo (T), tempo de in�cio, tempo executado,
 * numero de "jobs" que est�o na fila e estado. O tempo no decorrer do programa � medido em "ticks".
 * A dura��o (C) corresponde quanto tempo a tarefa precisa para ser executada por completo.
 * Quanto menor o per�odo (T) de uma tarefa, maior ser� sua prioridade na fila de tarefas, sendo que esse
 * n�mero significa de quanto em quanto tempo a tarefa ser� chamada.
 * O tempo de in�cio � o tempo no qual a tarefa come�ou a ser executada.
 * O tempo de execu��o representa quantos ciclos a tarefa executou.
 * O n�mero de execu��o representa quantos "jobs" est�o na fila.
 * E o estado indica qual o estado da tarefa.
 */
typedef struct tarefas tarefa_t;

/// \brief Cria��o de tarefas, indicando C e T
/**
 *  \param id: Identificador para a tarefa
 *  \param duracao: Tempo de dura��o da tarefa - C
 *  \param periodo: Tempo para chamada da tarefa - T
 *  \return Um ponteiro alocado do tipo tarefa_t
 *  \sa tarefa_get_id(), tarefa_get_duracao(), tarefa_get_periodo(), tarefa_set_estado(), tarefa_get_estado()
 */
tarefa_t* cria_tarefa(uint8_t id, uint64_t duracao, uint64_t periodo);

/// \brief Adquire o id da tarefa
/**
 *  \param tarefa: um ponteiro que representa o endere�o da tarefa
 *  \return id: identificador da tarefa
 *  \sa cria_tarefa(), tarefa_get_duracao(), tarefa_get_periodo(), tarefa_set_estado(), tarefa_get_estado()
 */
uint8_t tarefa_get_id(tarefa_t* tarefa);

/// \brief Adquire a dura��o (C) da tarefa
/**
 *  \param tarefa: um ponteiro que representa o endere�o da tarefa
 *  \return Dura��o da tarefa
 *  \sa cria_tarefa(), tarefa_get_id(), tarefa_get_periodo(), tarefa_set_estado(), tarefa_get_estado()
 */
uint64_t tarefa_get_duracao(tarefa_t* tarefa);

/// \brief Adquire o per�odo (T) da tarefa
/**
 *  \param tarefa: um ponteiro que representa o endere�o da tarefa
 *  \return Per�odo da tarefa
 *  \sa cria_tarefa(), tarefa_get_id(), tarefa_get_duracao(), tarefa_set_estado(), tarefa_get_estado()
 */
uint64_t tarefa_get_periodo(tarefa_t* tarefa);

/// \brief Estabelece o estado da tarefa
/**
 *  \param tarefa: um ponteiro que representa o endere�o da tarefa
 *  \param estado: pondendo ser OCIOSO, EXECUTANDO, PRONTA ou PARADA
 *  \return vazio
 *  \sa cria_tarefa(), tarefa_get_id(), tarefa_get_duracao(), tarefa_get_periodo(), tarefa_get_estado()
 */
void tarefa_set_estado(tarefa_t* tarefa, ESTADO_TAREFA estado);

/// \brief Adquire o estado da tarefa
/**
 *  \param tarefa: um ponteiro que representa o endere�o da tarefa
 *  \return estado: pondendo ser OCIOSO, EXECUTANDO, PRONTA ou PARADA
 *  \sa cria_tarefa(), tarefa_get_id(), tarefa_get_duracao(), tarefa_get_periodo(), tarefa_set_estado()
 */
ESTADO_TAREFA tarefa_get_estado(tarefa_t* tarefa);

/// \brief Ordena as tarefas pelo per�odo (T), sendo do menor para o maior.
/**
 *  \param lista_tarefas: um ponteiro que representa o endere�o da lista de tarefas
 *  \return vazio
 *  \sa cria_tarefa(), tarefa_get_id(), tarefa_get_duracao(), tarefa_get_periodo(), tarefa_set_estado()
 */
void ordena_tarefas(lista_enc_t* lista_tarefas);

// Fun��o para testes:
/// \brief Fun��o para depura��o do c�digo, onde imprime todas as informa��es de todas tarefas da lista.
/**
 *  \param listaTarefas: um ponteiro que representa o endere�o da lista de tarefas
 *  \return vazio
 *  \sa cria_tarefa(), tarefa_get_id(), tarefa_get_duracao(), tarefa_get_periodo(), tarefa_set_estado()
 */
void imprime_tarefas(lista_enc_t* listaTarefas);

/// \brief Estabelece o tempo de in�cio da tarefa.
/**
 *  \param tarefa: um ponteiro que representa o endere�o da tarefa
 *  \param tempo: um ponteiro que representa o endere�o da tarefa
 *  \return vazio
 */
void tarefa_set_inicio(tarefa_t* tarefa, uint32_t tempo);

/// \brief Adquire o tempo de in�cio da tarefa.
/**
 *  \param tarefa: um ponteiro que representa o endere�o da tarefa
 *  \return Tempo de in�cio da tarefa
 *  \sa cria_tarefa(), tarefa_get_id(), tarefa_get_duracao(), tarefa_get_periodo(), tarefa_set_estado()
 */
uint32_t tarefa_get_inicio(tarefa_t* tarefa);

/// \brief Adquire a tarefa priorit�ria.
/**
 *  \param listaTarefas: um ponteiro que representa o endere�o da lista de tarefas
 *  \return Tarefa priorit�ria
 *  \sa cria_tarefa(), tarefa_get_id(), tarefa_get_duracao(), tarefa_get_periodo(), tarefa_set_estado()
 */
tarefa_t* retorna_tarefa_prio(lista_enc_t* listaTarefas);

/// \brief Verifica requisi��o de tarefa.
/**
 *  \param listaTarefas: um ponteiro que representa o endere�o da lista de tarefas
 *  \param tempo: tempo
 *  \param fp: um ponteiro que representa o endere�o da lista de tarefas
 *  \return Vazio
 *  \sa cria_tarefa(), tarefa_get_id(), tarefa_get_duracao(), tarefa_get_periodo(), tarefa_set_estado()
 */
void update_tarefas(lista_enc_t* listaTarefas, uint32_t tempo, FILE *fp);

/// \brief Estabelece o tempo de in�cio da tarefa.
/**
 *  \param tarefa: um ponteiro que representa o endere�o da tarefa
 *  \param tempo: tempo de in�cio que ser� estabelecido
 *  \return Vazio
 *  \sa cria_tarefa(), tarefa_get_id(), tarefa_get_duracao(), tarefa_get_periodo(), tarefa_set_estado()
 */
void tarefa_set_inicio(tarefa_t* tarefa, uint32_t tempo);

/// \brief Estabelece o tempo de pausa da tarefa.
/**
 *  \param tarefa: um ponteiro que representa o endere�o da tarefa
 *  \param tempo: tempo de pausa que ser� estabelecido
 *  \return Vazio
 *  \sa cria_tarefa(), tarefa_get_id(), tarefa_get_duracao(), tarefa_get_periodo(), tarefa_set_estado()
 */
void tarefa_set_pausa(tarefa_t* tarefa, uint32_t tempo);

/// \brief Verifica se a tarefa est� terminada.
/**
 *  \param tarefa: um ponteiro que representa o endere�o da tarefa
 *  \param tempo: tempo que ser� verificado.
 *  \return 0: tarefa n�o terminada; 1: tarefa terminada
 *  \sa cria_tarefa(), tarefa_get_id(), tarefa_get_duracao(), tarefa_get_periodo(), tarefa_set_estado()
 */
int tarefa_checa_termino(tarefa_t* tarefa, uint32_t tempo);

/// \brief Calcula o m�ximo divisor comum (MDC) entre dois n�meros.
/**
 *  \param x: n�mero inteiro n�o sinalizado
 *  \param y: n�mero inteiro n�o sinalizado
 *  \return m�ximo divisor comum
 *  \sa cria_tarefa(), tarefa_get_id(), tarefa_get_duracao(), tarefa_get_periodo(), tarefa_set_estado()
 */
uint64_t calcMDC(uint64_t x, uint64_t y);

/// \brief Calcula o m�nimo m�ltiplo comum (MMC) entre dois n�meros.
/**
 *  \param x: n�mero inteiro n�o sinalizado
 *  \param y: n�mero inteiro n�o sinalizado
 *  \return m�nimo m�ltiplo comum
 *  \sa cria_tarefa(), tarefa_get_id(), tarefa_get_duracao(), tarefa_get_periodo(), tarefa_set_estado()
 */
uint64_t calcMMC(uint64_t x, uint64_t y);

/// \brief Calcula o m�nimo m�ltiplo comum (MMC) do per�odo (T) de uma lista de tarefas.
/**
 *  \param listaTarefas: ponteiro que representa o endere�o de uma lista de tarefas
 *  \return m�nimo m�ltiplo comum dos per�odos (T) da lista de tarefas
 *  \sa cria_tarefa(), tarefa_get_id(), tarefa_get_duracao(), tarefa_get_periodo(), tarefa_set_estado()
 */
uint64_t tarefas_calcMMC(lista_enc_t* listaTarefas);

/// \brief Escreve em um arquivo de sa�da o cabe�alho do Diagrama de Gannt.
/**
 *  \param fp: ponteiro do arquivo de sa�da
 *  \param numTarefas: numero de tarefas do Diagrama de Gannt
 *  \param escalaTempo: escala de tempo do Diagrama de Gannt
 *  \return vazio
 *  \sa gannt_finaliza_cabecalho(), gannt_nomenclatura(), gannt_seta_cima(), gannt_seta_baixo(), gannt_quadrado()
 */
void gannt_cabecalho(FILE *fp, uint8_t numTarefas, uint32_t escalaTempo);

/// \brief Escreve em um arquivo de sa�da a finaliza��o do cabe�alho do Diagrama de Gannt.
/**
 *  \param fp: ponteiro do arquivo de sa�da
 *  \return vazio
 *  \sa gannt_cabecalho(), gannt_nomenclatura(), gannt_seta_cima(), gannt_seta_baixo(), gannt_quadrado()
 */
void gannt_finaliza_cabecalho(FILE *fp);

/// \brief Escreve em um arquivo de sa�da a legenda das tarefas no Diagrama de Gannt.
/**
 *  \param fp: ponteiro do arquivo de sa�da
 *  \param lista_tarefas: ponteiro que representa o endere�o de uma lista de tarefas
 *  \return vazio
 *  \sa gannt_cabecalho(), gannt_finaliza_cabecalho(), gannt_seta_cima(), gannt_seta_baixo(), gannt_quadrado()
 */
void gannt_nomenclatura(FILE *fp, lista_enc_t* lista_tarefas);

/// \brief Escreve em um arquivo de sa�da a chegada de uma tarefa no Diagrama de Gannt.
/**
 *  \param fp: ponteiro do arquivo de sa�da
 *  \param id: identificador da tarefa
 *  \param tempo: tempo de chegada da tarefa
 *  \return vazio
 *  \sa gannt_cabecalho(), gannt_finaliza_cabecalho(), gannt_nomenclatura(), gannt_seta_baixo(), gannt_quadrado()
 */
void gannt_seta_cima(FILE *fp, uint8_t id, uint32_t tempo);

/// \brief Escreve em um arquivo de sa�da o t�rmino de uma tarefa no Diagrama de Gannt.
/**
 *  \param fp: ponteiro do arquivo de sa�da
 *  \param id: identificador da tarefa
 *  \param tempo: tempo de t�rmino da tarefa
 *  \return vazio
 *  \sa gannt_cabecalho(), gannt_finaliza_cabecalho(), gannt_nomenclatura(), gannt_seta_cima(), gannt_quadrado()
 */
void gannt_seta_baixo(FILE *fp, uint8_t id, uint32_t tempo);

/// \brief Escreve em um arquivo de sa�da a execu��o de uma tarefa no Diagrama de Gannt.
/**
 *  \param fp: ponteiro do arquivo de sa�da
 *  \param id: identificador da tarefa
 *  \param inicio: tempo de in�cio da execu��o
 *  \param fim: tempo de fim da execu��o
 *  \return vazio
 *  \sa gannt_cabecalho(), gannt_finaliza_cabecalho(), gannt_nomenclatura(), gannt_seta_cima(), gannt_seta_baixo()
 */
void gannt_quadrado(FILE *fp, uint8_t id, uint32_t inicio, uint32_t fim);

/// \brief Desaloca o espa�o de mem�ria utilizado pela lista de tarefas.
/**
 *  \param lista_tarefas: ponteiro da lista de tarefas
 *  \return vazio
 *  \sa cria_no(), cria_lista_enc(), cria_tarefa()
 *
 * Fun��o recebe toda a lista e desaloca n�s, tarefas e a lista.
 */
void desaloca_lista_tarefas(lista_enc_t* lista_tarefas);

#endif // TAREFAS_H_INCLUDED

