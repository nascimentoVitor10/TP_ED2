#ifndef QUEUE_H
#define QUEUE_H
#include "patient.h"
#include "exam.h"

typedef struct queue PatientQueue;
typedef struct queue_node QueueNode;

// Funções relacionadas a fila de pacientes
PatientQueue *q_create();

int q_size(PatientQueue *q);

int q_is_empty(PatientQueue *q);

void q_enqueue(PatientQueue *q, struct patient *data);

struct patient *patient_queue_dequeue(PatientQueue *q);

void q_free(PatientQueue *q);

#endif