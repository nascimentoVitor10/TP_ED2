#include "medico.h"
#include "exam.h"
#include "patient.h"
#include "report.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// função para criar o médico que atuará
struct medico *create_medico(struct medico *medico) {
  medico = malloc(sizeof(struct medico));
  if (medico == NULL) {
    exit(1);
  }
  medico->tempo_atendimento = 0;
  medico->disponibilidade = 0;
  medico->paciente_atendido = NULL;
  medico->paciente_em_consulta = NULL;

  return medico;
}

// Função para gerar probabilidade para o médico
double gerar_prob_aleatoria() {
  srand(time(NULL));
  return (double)rand() / RAND_MAX;
}

struct pathology *generate_condition(struct pathology *pathologys, int size_pat) {

  double random_value = (double)rand() / RAND_MAX;
  double cumulative_probability = 0.0;

  for (int i = 0; i < size_pat; i++) {
    cumulative_probability += pathologys[i].probabilidade;
    if (random_value <= cumulative_probability) {
      return &pathologys[i];
    }
  }
  return NULL;
}

// Função para gerar o diagnóstico pelo médico
void generate_report_condition(struct report *report, struct pathology *pathologys,int size_pat) {

  double p = gerar_prob_aleatoria();
  if (p >= 0.8) {
    char *disease_medico_t = report->condition;
    while (disease_medico_t == report->condition) {
      struct pathology *disease_medico = generate_condition(pathologys, size_pat);
      disease_medico_t = disease_medico->nome;
    }
    report->condition = disease_medico_t;
  }
}

// função pré-diagnóstico da IA
struct exam *pre_diagnosis(struct patient *patient, int rx_id, int exam_time, struct pathology *pathologys, int size_pat) {
  struct pathology *disease = generate_condition(pathologys, size_pat);
  printf("Diagnóstico da IA: o paciente %s tem %s.\n", patient->name,disease->nome);

  // gerar exame com pré-diagnóstico
  int id_exam = patient->id;

  struct exam *exam = create_exam(id_exam, patient->id, rx_id, disease->nome, disease->gravidade, exam_time);

  database_exam(exam);

  return exam;
}
