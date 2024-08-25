#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "exam.h"

/*FUNÇÕES RELACIONADAS AO EXAME*/
// cria o exame
struct exam* create_exam(int id, int patient_id, int rx_id, char *condition_ia, int priority, int tempo_fila_prioridade){


  // aloca memória para a estrutura Exam
  struct exam* exam = malloc(sizeof(struct exam)); 
  // Verifica se a memória foi alocada corretamente
  if (exam == NULL){
    printf("Erro ao alocar memória!\n");
    exit(1); // Abortar programa caso a memória não foi alocada corretamente
  }
  
  exam->next = (struct exam*)malloc(sizeof(struct exam));
  exam->id = id;
  exam->patient_id = patient_id;
  exam->rx_id = rx_id;
  
  exam->condition_ia = (char *)malloc(sizeof(char) * strlen(condition_ia) + 1);
  if (exam->condition_ia == NULL) {
    printf("Erro ao alocar memória\n");
    destroy_exam(exam);
    return NULL;
  }

  strcpy(exam->condition_ia, condition_ia);
  exam->priority = priority;
  exam->tempo_fila_prioridade = tempo_fila_prioridade;
  return exam;
}



// função para destruir a estrutura alocada para o exame
void destroy_exam(struct exam *exam){
  if (exam != NULL){
    free(exam); // Liberar mémoria alocada para estrutura exam
  }
}

// função para retornar ID do exame
int get_exam_id(struct exam *exam){
  // Verificar se o ponteiro exam é NULL
  if (exam == NULL) {
    printf("Erro: o ponteiro é NULL\n");
    return -1;
  }
  return exam->id;
}

// função para retornar ID do paciente do exame
int get_exam_patient_id(struct exam *exam){
  // Verificar se o ponteiro exam é NULL
  if (exam == NULL) {
    printf("Erro: o ponteiro é NULL\n");
    return -1; 
  }
  return exam->patient_id;
}

// função para retornar ID do aparelho do exame
int get_exam_rx_id(struct exam *exam){
  // Verificar se o ponteiro exam é NULL
  if (exam == NULL) {
    printf("Erro: o ponteiro é NULL\n");
    return -1; 
  }
  return (*exam).rx_id; 
}

// função para retornar a condição diagnosticada pela IA
char *get_exam_condition_ia(struct exam *exam){
  // Verificar se o ponteiro exam é NULL
  if (exam == NULL){
    printf("Erro: o ponteiro é NULL\n");
    return NULL;
  }
  return exam->condition_ia;
}

// função para retornar o nível de prioridade do exame
int get_exam_priority(struct exam *exam){
  // Verificar se o ponteiro exam é NULL
  if (exam == NULL){
    printf("Erro: o ponteiro é NULL\n");
  }
  return exam->priority;
}

// estrutura para retornar data e hora do exame
int get_exam_time(struct exam *exam){
  // Verificar se o ponteiro exam é NULL
  if (exam == NULL) {
    printf("Erro: o ponteiro é NULL\n");
    return 0; // Retorna NULL caso o ponteiro não aponte para nenhum endereço de memória corretamente
  }
  return exam->tempo_fila_prioridade; 
}

// Função para criar e preencher os arquivos(exames))
void database_exam(struct exam *exam) {
    FILE *arquivo;

    // Abre o arquivo no modo de escrita, criando-o se não existir
    arquivo = fopen("db_exam.txt", "a");

    // Verifica se o arquivo foi aberto com sucesso
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    // Escreve cada informação em uma linha
    fprintf(arquivo, "%d\n", exam->id);
    fprintf(arquivo, "%d\n", exam->rx_id);
    fprintf(arquivo, "%d\n", exam->patient_id);
    fprintf(arquivo, "%s\n", exam->condition_ia);
    fprintf(arquivo, "%d\n", exam->tempo_fila_prioridade);
    fprintf(arquivo, "\n");
    fclose(arquivo);
}