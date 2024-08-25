#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H
#include "patient.h"
#include "exam.h"
#include "medico.h"

typedef struct heap Heap;

// Funções relacionadas a fila de pioridade
void trocar(struct exam *a, struct exam *b);

void reorganiza_fila(struct exam *fila, int *n, int i);

void inserir_patient_priority(struct exam heap[], int *fila_size, struct exam *novo_exam);

struct exam extrair_maior_prioridade(struct exam fila[], int *fila_size);

int fila_prioridade_vazia(struct exam *heap);

void atualiza_tempo_fila(struct exam *heap, struct medico *medico);

#endif