#include "patient.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


struct patient *create_patient(int id, const char *name, struct tm *birthdate, int hora_chegada, int tempo_de_espera) {
  // Verifica se name e birthdate são nulos
  if (!name) {
    printf("Erro: o ponteiro name não aponta para nenhum endereço de memória corretamente\n");
    return NULL; // Retorna NULL caso o ponteiro name seja NULL
  } else if (birthdate == NULL) {
    printf("Erro: o ponteiro name não aponta para nenhum endereço de memória corretamente\n");
      return NULL; // Retorna NULL caso o ponteiro birthdate seja NULL
  }

// Alocar memória para a estrutura Patient e verifica se a memória foi alocada corretamente
  struct patient *patient = malloc(sizeof(struct patient));
  if (patient == NULL) {
    printf("Erro ao alocar memória\n");
    return NULL; // Retorna NULL caso a memória não seja alocada
  }
  
  // Atribui o ID do paciente
  patient->id = id;

  // Atribui 0 ao tempo de espera
  patient->tempo_de_espera = 0;

  // Aloca memória para o nome do paciente e verifica se a memória foi alocada corretamente
  patient->name = (char *)malloc(sizeof(char) * strlen(name) + 1);
  
  if (patient->name == NULL) {
    printf("Erro ao alocar memória\n");
    destroy_patient(patient); // Liberar a memória
    return NULL; // Retorna NULL caso a memória não foi alocada corretamente
  }

  // Copia o nome do paciente para a atribuição do nome do paciente
  strcpy(patient->name, name); 

  // Copia a estrutura tm para a atribuição da data de nascimento do paciente
  patient->birthdate = birthdate;
  
  // Atribui o timestamp do paciente
  patient->hora_chegada = hora_chegada; 
  return patient;
}

// função para destruir a estrutura alocada para o paciente
void destroy_patient(struct patient *patient) {
  if (patient != NULL) {
    free(patient); // Liberar memória alocada para estrutura Patient
    free(patient->name);
    free(patient->birthdate);
  }
}

// função para retornar ID do paciente
int get_patient_id(struct patient *patient) {
  // Verificar se o ponteiro patient é NULL
  if (patient == NULL) {
    printf("Erro: o ponteiro é NULL\n");
    return 0; // Retorna NULL caso o ponteiro não aponte para nenhum endereço de memória corretamente
  }
  
  return patient->id;
}

// função para retornar hora de chegada do paciente
int get_patient_hora_chegada(struct patient *patient) {
  // Verificar se o ponteiro patient é NULL
  if (patient == NULL) {
    printf("Erro: o ponteiro é NULL\n");
    return 0; // Retorna NULL caso o ponteiro não aponte para nenhum endereço de memória corretamente
  }
  return patient->hora_chegada;
}

// função para retornar hora de chegada do paciente
int get_patient_tempo_espera(struct patient *patient) {
  // Verificar se o ponteiro patient é NULL
  if (patient == NULL) {
    printf("Erro: o ponteiro é NULL\n");
    return 0; // Retorna NULL caso o ponteiro não aponte para nenhum endereço de memória corretamente
  }
  return patient->tempo_de_espera;
}

// função para retornar o nome do paciente
const char *get_patient_name(struct patient *patient) {
  // Verificar se o ponteiro patient é NULL
  if (patient == NULL) {
    printf("Erro: o ponteiro é NULL\n");
    return NULL; // Retorna NULL caso o ponteiro não aponte para nenhum endereço de memória corretamente
  }

  return patient->name; 
}

// estrutura para retornar data de nascimento
struct tm *get_patient_birthdate(struct patient *patient) { 
  // Verificar se o ponteiro patient é NULL
  if (patient == NULL) {
    printf("Erro: o ponteiro é NULL\n");
    return NULL; // Retorna NULL caso o ponteiro não aponte para nenhum endereço de memória corretamente
  }

  return patient->birthdate;
}

// Função para criar e preencher os arquivos(pacientes)
void database_patient(struct patient *patient) {
    FILE *arquivo;

    // Abre o arquivo no modo de escrita, criando-o se não existir
    arquivo = fopen("db_patient.txt", "a");

    // Verifica se o arquivo foi aberto com sucesso
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    // Escreve cada informação em uma linha
    fprintf(arquivo, "%d\n", patient->id);
    fprintf(arquivo, "%s\n", patient->name);
    fprintf(arquivo, "%d\n", patient->hora_chegada);
    fprintf(arquivo, "\n");
    fclose(arquivo);
}

// imprime as informações do paciente criado
void print_patient(struct patient *patient)
{
   printf("Paciente criado:\n");
   printf("ID: %d\n", get_patient_id(patient));
   printf("Nome: %s\n", get_patient_name(patient));
   printf("Data de Nascimento: %s\n", asctime(get_patient_birthdate(patient)));
}