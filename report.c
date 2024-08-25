#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "report.h"

// função para destruir a estrutura alocada para o report
void destroy_report(struct report *report){  
  if (report != NULL){
    free(report->condition);
    free(report);
  }
}

// Função para criar os reports
struct report *create_report(int id, int exam_id, char *condition, int time_retorno_report){

  struct report *report = (struct report *) malloc(sizeof(struct report));
    if(report == NULL){
      printf("Erro ao alocar memória para o report");
      exit(1);
    }

    report->id = id;

    report->exam_id = exam_id;

    
    report->condition = (char *)malloc(sizeof(char) * strlen(condition) + 1);
    if (report->condition == NULL) {
      printf("Erro ao alocar memória\n");
      destroy_report(report);
      return NULL;
    }

    report->time_retorno_report = time_retorno_report;

    return report;
}

// função para retornar o id do report
int get_report_id(struct report *report){
  if (report == NULL){
    printf("Erro: o ponteiro é NULL\n");
  }
  return report->id;
}

// função para retornar o id do exame do report
int get_report_exam_id(struct report *report){
  if (report == NULL){
    printf("Erro: o ponteiro é NULL\n");
  }
  return report->exam_id;
}

// função para retornar a condição diagnosticada pelo médico
char *get_report_condition(struct report *report){
  if (report == NULL){
    printf("Erro: o ponteiro é NULL\n");
  }
  return report->condition;
}

// Função para criar e preencher os arquivos(report)
void database_report(struct report *report) {
    FILE *arquivo;

    // Abre o arquivo no modo de escrita, criando-o se não existir
    arquivo = fopen("db_report.txt", "a");

    // Verifica se o arquivo foi aberto com sucesso
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    // Escreve cada informação em uma linha
    fprintf(arquivo, "%d\n", report->id);
    fprintf(arquivo, "%d\n", report->exam_id);
    fprintf(arquivo, "%s\n", report->condition);
    fprintf(arquivo, "%d\n", report->time_retorno_report);
    fprintf(arquivo, "\n");
    fclose(arquivo);
}