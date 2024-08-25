#ifndef MEDICO_H
#define MEDICO_H
#include "patient.h"
#include "report.h"
#include "exam.h"

struct medico {
  int disponibilidade;   // 0 = disponível , 1 = indisponível
  int tempo_atendimento; // 30 unidades de tempo
  struct exam *paciente_atendido; // paciente que já recebeu diagnóstico
  struct exam *paciente_em_consulta; // paciente em consulta
};

struct pathology{
  char *nome;
  double probabilidade;
  int gravidade;
};

// Funções relacionadas ao médico
struct medico *create_medico(struct medico *medico);
  
double gerar_prob_aleatoria();

struct pathology *generate_condition(struct pathology *pathologys, int size_pat);

struct exam *pre_diagnosis(struct patient *patient, int rx_id, int exam_time, struct pathology pathologys[], int size_pat);

void generate_report_condition(struct report *report, struct pathology pathologys[], int size_pat);

#endif
