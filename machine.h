// Cabeçalhos das funções e estruturas desenvolvidas
#ifndef MACHINE_H
#define MACHINE_H
#include <time.h>
#include "patient.h"

// TAD da máquina
struct maquina 
{
    int rx_id;
    int estado; // 0: livre, 1: ocupada
    int tempo_restante;
    struct patient *paciente_anterior;
    struct patient *paciente_atendido;
    struct maquina *proxima;
};

// Funções relacionadas às máquinas
struct maquina * criar_maquinas(int num_maquinas);

struct maquina * encontrar_maquina_livre(struct maquina  *cabeca);

void atribuir_paciente(struct maquina *maquina, struct patient *patient);

int contar_maquinas_livres(struct maquina  *cabeca);

void atualizar_tempo(int x, struct maquina  *cabeca) ;

#endif