// Cabeçalhos das funções e estruturas desenvolvidas
#ifndef EXAM_H
#define EXAM_H
#include <time.h>

// TAD Exam
struct exam{
  int id;  
  int rx_id;
  int patient_id;
  char *condition_ia;
  int priority;
  struct exam *next;
  int tempo_fila_prioridade;
};


// Funções relacionadas ao paciente
struct exam* create_exam(int id, int patient_id, int rx_id, char *condition_ia, int priority, int tempo_fila_prioridade);

void destroy_exam(struct exam *exam);

int get_exam_id(struct exam *exam);

int get_exam_patient_id(struct exam *exam);

int get_exam_rx_id(struct exam *exam);

int get_exam_priority(struct exam *exam);

char *get_exam_condition_ia(struct exam *exam);

int get_exam_time(struct exam *exam);

void database_exam(struct exam *exam);

void print_exam(struct exam *exam);

#endif
