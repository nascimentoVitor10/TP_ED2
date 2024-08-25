// importação de bibliotecas utilzadas

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include "aux.h"
#include "exam.h"
#include "report.h"
#include "machine.h"
#include "medico.h"
#include "patient.h"
#include "patient_queue.h"
#include "priority_queue.h"

#define MAX_SIZE 100

int main()
{
    struct pathology pathologys[] = {
        {"Normal", 0.3, 1},
        {"Bronquite", 0.2, 2},
        {"Pneumonia", 0.1, 3},
        {"Covid", 0.1, 4},
        {"Embolia pulmonar", 0.05, 4},
        {"Derrame pleural", 0.05, 4},
        {"Fibrose pulmonar", 0.05, 5},
        {"Tuberculose", 0.05, 5},
        {"Câncer de pulmão", 0.1, 6}
     };

    int num_pathologys = sizeof(pathologys)/sizeof(pathologys[0]);
    int prob_chegada[] = {1,1};
    int cont_id_pacient = 0;          // Contador de pacientes
    int cont_pacient_exame = 0;       // Contador de pacientes que fizeram exame

    srand(time(NULL));
                                      // Ponteiro para o início da lista de máquinas
    struct maquina  *cabeca_lista_maquinas = criar_maquinas(5);       // Crias as máquinas

    struct exam *cabeca_espera = NULL;      // Inicializa a fila de espera como vazia
    PatientQueue *q =  q_create() ;  // Cria a fila de espera

    struct exam fila[MAX_SIZE];             // Cria a fila de prioridade de exames
    int fila_size = 0;               // Contador de exames na fila de prioridade

    struct medico *medico = NULL;
    medico = create_medico(medico); 

    struct patient *patient = NULL;

    // contador de tempo para cada condição
    int cont_tempo_normal = 0;
    int cont_tempo_bronquite = 0;
    int cont_tempo_pneumonia = 0;
    int cont_tempo_covid = 0;
    int cont_tempo_emboliaP = 0;
    int cont_tempo_derrameP = 0;
    int cont_tempo_fibroseP = 0;
    int cont_tempo_tuberculose = 0;
    int cont_tempo_cancerP = 0;


    // contador de pacientes de cada condição
    int quant_pacient_normal = 0;
    int quant_pacient_bronquite = 0;
    int quant_pacient_pneumonia = 0;
    int quant_pacient_covid = 0;
    int quant_pacient_emboliaP = 0;
    int quant_pacient_derrameP = 0;
    int quant_pacient_fibroseP = 0;
    int quant_pacient_tuberculose = 0;
    int quant_pacient_cancerP = 0;

    // contadores gerais
    int qtd_laudo = 0;
    int tempo_exames_geral = 0;
    int qtd_exames_feitos = 0;

    // INÍCIO DA SIMULAÇÃO - HOSPITAL
    for (int i = 0; i < 43200; i++){
       int random_number = rand() % sizeof(prob_chegada) / sizeof(prob_chegada[0]);
       if (prob_chegada[random_number] == 1){
           // Hora de chegada do paciente
           int hour_chegada = i;

           // Definindo uma data de nascimento fictícia para o paciente
           struct tm birthdate = {0};
           birthdate.tm_year = 90;
           birthdate.tm_mon = 5;
           birthdate.tm_mday = 15;

           // Criando um paciente
           int tempo_de_espera = 0;
           struct patient *patient = create_patient(cont_id_pacient, "João Silva", &birthdate, hour_chegada, tempo_de_espera);
           database_patient(patient); //salva paciente no db_patient.txt
           cont_id_pacient++;
           printf("%d",cont_id_pacient);
           // Insere paciente na fila de espera
           q_enqueue(q, patient);


           // Atualiza o tempo das máquinas para já liberar para a contagem a seguir
           atualizar_tempo(i, cabeca_lista_maquinas);


           // Verificar quantas máquinas estão livres (num_maquinas_free)
           int maquinas_livres = contar_maquinas_livres(cabeca_lista_maquinas);

           // Verificar quantas pacientes estão na fila de espera
           int num_pacientes_fila = q_size(q);
           printf("%d",num_pacientes_fila);

           // Loop para atribuir pacientes às máquinas livres
           if ((maquinas_livres > num_pacientes_fila) || (maquinas_livres == num_pacientes_fila)) {
             for (int j = 0; j < num_pacientes_fila; j++){

                 patient = patient_queue_dequeue(q);                               // remove paciente da fila
                 struct maquina *maquina_free = encontrar_maquina_livre(cabeca_lista_maquinas);   // encontra uma máquina livre
                 atribuir_paciente(maquina_free, patient);                         // atribui o paciente à máquina livre
             }

            }else{
             for (int j = 0; j < maquinas_livres; j++){
                 patient = patient_queue_dequeue(q);
                 struct maquina *maquina_free = encontrar_maquina_livre(cabeca_lista_maquinas);
                 atribuir_paciente(maquina_free, patient);
             }
         }


         // verificar quais pacientes já saíram da máquina
         if (cabeca_lista_maquinas != NULL){
             struct maquina *maquina_atual = cabeca_lista_maquinas;
             while (maquina_atual != NULL){
                 if (maquina_atual->paciente_atendido != NULL){

                     // passar pela IA
                     struct exam *ia_exam = pre_diagnosis(maquina_atual->paciente_atendido, maquina_atual->rx_id, i, pathologys, fila_size);
                     database_exam(ia_exam);

                     qtd_exames_feitos++;

                     // inserir na fila de prioridade
                     inserir_patient_priority(fila, &fila_size, ia_exam); 
                 }
                 maquina_atual = maquina_atual->proxima;
             }
         }

         // antes verifica se a fila está vazia
         if (fila_prioridade_vazia(fila) == 1){

             // verificar se o médico está disponível
             if (medico->disponibilidade == 0 && medico->paciente_em_consulta != NULL){

                 medico->paciente_atendido = medico->paciente_em_consulta;
                 struct exam exam_para_consulta = extrair_maior_prioridade(fila, &fila_size);
                 medico->paciente_em_consulta = &exam_para_consulta;
                 medico->disponibilidade = 1;
                 medico->tempo_atendimento = 30; 

                 // etapa quando o paciente sai da consulta com o médico
                 // são guardadas em variáveis cada info do exame para poder liberar a struct exam
                 int id_paciente = medico->paciente_atendido->patient_id;
                 int exam_id = medico->paciente_atendido->id;
                 char *condition_ia = medico->paciente_atendido->condition_ia;
                 int prioridade = medico->paciente_atendido->priority;
                 int tempo_na_fila = medico->paciente_atendido->tempo_fila_prioridade;

                 // cria-se o report do exame
                 struct report *report_paciente = create_report(id_paciente, exam_id, condition_ia, tempo_na_fila);

                 // gera a condição dada pelo médico
                 generate_report_condition(report_paciente, pathologys, num_pathologys);
                 qtd_laudo ++;


                 // atualiza o tempo de espera total para cada condição
                 char *condicao = report_paciente->condition;
                 int tempo = report_paciente->time_retorno_report;

                 if (strcmp(condicao, "Normal") == 0) {
                     cont_tempo_normal += tempo;
                     quant_pacient_normal++;
                 }

                 else if (strcmp(condicao, "Bronquite") == 0) { 
                     cont_tempo_bronquite += tempo;
                     quant_pacient_bronquite++;
                 } 

                 else if (strcmp(condicao, "Pneumonia") == 0) {
                     cont_tempo_pneumonia += tempo;
                     quant_pacient_pneumonia++;
                 } 

                 else if (strcmp(condicao, "COVID") == 0) {
                     cont_tempo_covid += tempo;
                     quant_pacient_covid++;
                 } 

                 else if (strcmp(condicao, "Embolia pulmonar") == 0) { 
                     cont_tempo_emboliaP += tempo;
                     quant_pacient_emboliaP++;
                 }

                 else if (strcmp(condicao, "Derrame pleural") == 0) { 
                     cont_tempo_derrameP += tempo;
                     quant_pacient_derrameP++;
                 }

                 else if (strcmp(condicao, "Fibrose pulmonar") == 0) {
                     cont_tempo_fibroseP += tempo;
                     quant_pacient_fibroseP++;
                 }

                 else if (strcmp(condicao, "Tuberculose") == 0) {
                     cont_tempo_tuberculose += tempo;
                     quant_pacient_tuberculose++;
                 }

                 else if (strcmp(condicao, "Câncer de pulmão") == 0) {
                     cont_tempo_cancerP += tempo;
                     quant_pacient_cancerP++;
                 }

                 // após o diagnóstico, salva no database db_report.txt
                 database_report(report_paciente);

                 // destrói-se a struct exame e report do paciente finalmente diagnosticado
                 destroy_exam(medico->paciente_atendido);
                 destroy_report(report_paciente);

             }
            else if(medico->disponibilidade == 0 && medico->paciente_em_consulta == NULL){

                struct exam novo_exam = extrair_maior_prioridade(fila, &fila_size);
                 medico->paciente_em_consulta = &novo_exam;
                 medico->disponibilidade = 1;
                 medico->tempo_atendimento = 30;
             }
             else if (medico->disponibilidade == 0 && medico->paciente_em_consulta == NULL && medico->paciente_atendido == NULL)
             {
                 struct patient *novo = malloc(sizeof(struct patient));
                 struct exam novo_exam = extrair_maior_prioridade(fila, &fila_size);
                 medico->paciente_em_consulta = &novo_exam;
                 medico->disponibilidade = 1;
                 medico->tempo_atendimento = 30;
             }
             atualiza_tempo_fila(fila, medico);
         }

         // liberar a memória alocada para paciente
         destroy_patient(patient);    
       }

       if (i % 7200 == 0){

            // PRINTAR AS INFORMAÇÕES ABAIXO
            printf("→ RELATÓRIO ATUALIZADO - SIMULAÇÃO HOSPITALAR ←");
            printf("\n");

            printf("\nNúmero de pacientes cadastrados: %d", cont_id_pacient);
            printf("\nNúmero de pacientes que fizeram exame: %d", qtd_exames_feitos);
            printf("\nTempo médio para recebimento de laudo: %d",tempo_exames_geral/qtd_laudo);

            printf("\nTempo médio de laudo por condição:\n");
            printf("\n");
            printf("Tempo médio para recebimento de laudo (Normal): %d unidades", cont_tempo_normal/quant_pacient_normal);
            printf("Tempo médio para recebimento de laudo (Bronquite): %d unidades", cont_tempo_bronquite/quant_pacient_normal);
            printf("Tempo médio para recebimento de laudo (Pneumonia): %d unidades", cont_tempo_pneumonia/quant_pacient_normal);
            printf("Tempo médio para recebimento de laudo (COVID): %d", cont_tempo_covid/quant_pacient_normal);
            printf("Tempo médio para recebimento de laudo (Embolia pulmonar): %d unidades",cont_tempo_emboliaP/quant_pacient_normal);
            printf("Tempo médio para recebimento de laudo (Derrame pleural): %d unidades",cont_tempo_derrameP/quant_pacient_normal);
            printf("Tempo médio para recebimento de laudo (Fibrose pulmonar): %d unidades",cont_tempo_fibroseP/quant_pacient_normal);
            printf("Tempo médio para recebimento de laudo (Tuberculose): %d unidades",cont_tempo_tuberculose/quant_pacient_normal);
            printf("Tempo médio para recebimento de laudo (Câncer de pulmão): %d unidades",cont_tempo_cancerP/quant_pacient_normal);
            printf("\n");

            printf("Porcentagem de laudos feitos com base no número de exames realizados: %d",(qtd_laudo/qtd_exames_feitos)*100);

            // trava loop e retorna à simulação
            #ifdef _WIN32
                system("pause");
            #else
                sleep(1);
            #endif
            limparTela();
        }
    }
    printf("acabou");
    return 0;
}