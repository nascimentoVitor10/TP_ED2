#include "patient_queue.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "patient.h"
#include "exam.h"

// TADs Fila de Pacientes
struct queue
{
   QueueNode *front; 
   QueueNode *rear;  
};

struct queue_node
{
   struct patient *data;    
   QueueNode *next;
};

// Cria uma fila de pacientes
PatientQueue *q_create()
{  
   PatientQueue *q = (PatientQueue *)malloc(sizeof(PatientQueue)); 
   q->front = q->rear = NULL;            
   return q;
}

// Verifica o tamanho da fila
int q_size(PatientQueue *q)
{
   QueueNode *atual = q->front;
   int size = 0;

   while(atual != NULL){
      size++;
      atual = atual->next;
   } 
   return size;
}

// Verifica se a fila de pacientes está vazia
int q_is_empty(PatientQueue *q)
{  
   return q->front == NULL;
}

// Adiciona um paciente à fila de pacientes
void q_enqueue(PatientQueue *q, struct patient *patient)
{   
   QueueNode *node = (QueueNode *)malloc(sizeof(QueueNode)); 
   node->data = patient;
   node->next = NULL;

   if (q_is_empty(q))
   {
      q->front = node;
   } 
   else
   {
      q->rear->next = node;

   }
   q->rear = node;
}

// Remove um paciente da fila de pacientes
struct patient *patient_queue_dequeue(PatientQueue *q) 
{
  
   // Garante que a fila não esteja vazia
   assert(!q_is_empty(q));
   
   QueueNode *p = q->front;
   struct patient *data = p->data;

   if (q->front != q->rear) 
   {
      q->front = q->front->next;
   } else
   {
      q->front = q->rear = NULL;
   }

   // Liberar memória do paciente
   destroy_patient(data);
   free(data);

   free(p);
   return data; // Retornar uma cópia dos dados paciente
}

// Libera a memória alocada para a fila de pacientes
void q_free(PatientQueue *q)
{   
   QueueNode *p = q->front;
   while (p != NULL)
   {
      QueueNode *t = p->next; 
      free(p);                
      p = t;               
   }
   free(q);
}