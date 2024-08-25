#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "machine.h"
#include "patient.h"

// Função para criar as maquinas
struct maquina * criar_maquinas(int num_maquinas)
{

    struct maquina  *cabeca = NULL; // Inicializa a cabeça da lista como NULL

    struct maquina  *nova, *atual = NULL;
    for (int i = 0; i < num_maquinas; i++) {
        nova = (struct maquina  *)malloc(sizeof(struct maquina));
        nova->rx_id = i;
        nova->estado = 0; // Inicialmente livre
        nova->tempo_restante = 0;
        nova->paciente_anterior = NULL;
        nova->paciente_atendido = NULL;
        nova->proxima = NULL;

        if (cabeca == NULL) {
            cabeca = nova; // A primeira máquina se torna a cabeça da lista
        } else {
            atual->proxima = nova; // As máquinas subsequentes são adicionadas ao final da lista
        }
        atual = nova; // Atualizamos o ponteiro 'atual' para apontar para a nova máquina
    }
    return cabeca;
}


// Função para encontrar uma máquina livre
struct maquina * encontrar_maquina_livre(struct maquina  *cabeca) {
    struct maquina  *atual = cabeca;
    while (atual != NULL) {
        if (atual->estado == 0) {
            return atual;
        }
        atual = atual->proxima;
    }
    return NULL; // Todas as máquinas estão ocupadas
}


// Função para atribuir um paciente a uma máquina
void atribuir_paciente(struct maquina *maquina, struct patient *patient) {
    maquina->estado = 1;
    maquina->tempo_restante = 10;
    maquina->paciente_anterior = maquina->paciente_atendido;
    maquina->paciente_atendido = patient;
}

// função para contar máquinas livres
int contar_maquinas_livres(struct maquina  *cabeca){
    
    int num_maquinas_free = 0;
    struct maquina  *atual = cabeca;

    while (atual != NULL) {
        if (atual->estado == 0) {
            num_maquinas_free++;
        }
        atual = atual->proxima;
     }
    return num_maquinas_free;
}

// Função para atualizar o tempo
void atualizar_tempo(int x, struct maquina  *cabeca) {

    struct maquina  *atual = cabeca;
    while (atual != NULL) {
        if (atual->estado == 1) {
            atual->tempo_restante--;
            if (atual->tempo_restante == 0) {
                // Liberar a máquina e fazer algo com o paciente
                printf("Paciente %d atendido.\n", atual->paciente_atendido->id);
                atual->estado = 0;
                atual->paciente_anterior = atual->paciente_atendido;
                atual->paciente_atendido = NULL;   
            }
        }
    }   atual = atual->proxima;
}