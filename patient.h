#ifndef PATIENT_H
#define PATIENT_H
#include <time.h>

// Função para criar um paciente
struct patient {
  int id;
  char *name;
  struct tm *birthdate;
  int hora_chegada;
  int tempo_de_espera;
};


struct patient *create_patient(int, const char *, struct tm *birthdate, int hora_chegada, int tempo_de_espera);

void destroy_patient(struct patient *patient);

int get_patient_id(struct patient *patient);

int get_patient_hora_chegada(struct patient *patient);

int get_patient_tempo_espera(struct patient *patient);

const char *get_patient_name(struct patient *patient);

struct tm *get_patient_birthdate(struct patient *patient);

void database_patient(struct patient *patient);

void print_patient(struct patient *patient);

#endif