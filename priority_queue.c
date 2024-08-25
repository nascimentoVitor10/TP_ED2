#include <stdio.h>
#include <stdlib.h>
#include <limits.h> 
#include "priority_queue.h"
#include "exam.h"


// Função para trocar dois elementos na fila
void trocar(struct exam *a, struct exam *b) {
    struct exam temp = *a;
    *a = *b;
    *b = temp;
}


// Função para heapify (mantém a propriedade do heap)
void reorganiza_fila(struct exam *fila, int *n, int i) {
    int maior = i;
    int esquerda = 2*i + 1;
    int direita = 2*i + 2;

    // Encontra o maior entre o nó atual e seus filhos
    if (esquerda < *n && fila[esquerda].priority > fila[maior].priority)
        maior = esquerda;
    if (direita < *n && fila[direita].priority > fila[maior].priority)
        maior = direita;

    // Se o maior não for o nó atual, troca e chama heapify recursivamente
    if (maior != i) {
        trocar(&fila[i], &fila[maior]);
        reorganiza_fila(fila, n, maior);
    }
}


// função para inserir um novo elemento na fila de prioridade
void inserir_patient_priority(struct exam heap[], int *fila_size, struct exam *novo_exam) {

    #define MAX_SIZE 100
  
    // Verifica se a fila está cheia
    if (*fila_size == MAX_SIZE) {
        printf("Fila cheia!\n");
        return;
    }
    // Encontra a posição correta para inserir o novo elemento
    int i = *fila_size - 1;
    while (i >= 0 && heap[i].priority < novo_exam->priority) {
      
        heap[i + 1] = heap[i];
        i--;
    }
    // Insere o novo elemento na posição correta
    heap[i + 1].id = novo_exam->id; 
    heap[i + 1].patient_id = novo_exam->patient_id;
    heap[i + 1].rx_id = novo_exam->rx_id;
    heap[i + 1].condition_ia = novo_exam->condition_ia;
    heap[i + 1].priority = novo_exam->priority;
    heap[i + 1].next = novo_exam->next;
    heap[i + 1].tempo_fila_prioridade = novo_exam->tempo_fila_prioridade;

     
    // Atualiza o tamanho da fila
    fila_size++;
}

// função para remover o elemento de maior prioridade da fila de prioridade
struct exam extrair_maior_prioridade(struct exam fila[], int *fila_size) {
    // Verifica se a fila está vazia
    if (*fila_size == 0) {
        printf("A fila está vazia.\n");
        // Retorna um elemento nulo ou um valor padrão para indicar erro
        struct exam elemento_nulo;
        return elemento_nulo;
    }

    // Substitui a raiz (maior elemento) pelo último elemento
    struct exam elemento_removido = fila[0];
    fila[0] = fila[*fila_size - 1];
    (*fila_size)--;

    // Restaura a propriedade do heap
    reorganiza_fila(fila, fila_size, 0);

    return elemento_removido;
}



// função para contar o número de pessas na fila de prioridade
int fila_prioridade_vazia(struct exam *heap) 
{ 
  if (&heap[0] == NULL){
      return 0;
  }
  return 1; 
}
    


// função para atualizar tempo de espera de pacientes na fila
void atualiza_tempo_fila(struct exam *heap, struct medico *medico) {

  struct medico *profissional = medico;
  if (profissional != NULL) {
    profissional->tempo_atendimento--;
    if (profissional->tempo_atendimento == 0){
      profissional->paciente_atendido = profissional->paciente_em_consulta;
      profissional->paciente_em_consulta = NULL;
      profissional->disponibilidade = 0;
    }
  }
  
  int i = 0;
  struct exam *atual = &heap[0]; 
  while (atual != NULL) {
    atual->tempo_fila_prioridade++;
    atual = atual->next;
  }
}