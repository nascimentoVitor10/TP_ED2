// Cabeçalhos das funções e estruturas desenvolvidas
#ifndef REPORT_H
#define REPORT_H
#include <time.h>

// Tipos de dados abstratos
struct report{
    int id;
    int exam_id;
    char *condition;
    int time_retorno_report;
};

// Funções relacionadas ao paciente
void destroy_report(struct report *report);

struct report *create_report(int id, int exam_id, char *condition, int time_retorno_report);

int get_report_id(struct report *report);

int get_report_exam_id(struct report *report);

char *get_report_condition(struct report *report);

void database_report(struct report *report);

#endif