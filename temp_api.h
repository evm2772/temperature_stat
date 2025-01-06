#ifndef TEMP_API_H
#define TEMP_API_H

#include "sensor.h"

typedef struct Stat
{
    int64_t records_number;
    uint16_t year;
    int8_t t_min;
    int8_t t_max;
    double t_sum;
} Stat_t;

void print_stat(Stat_t stat, int month_num);
void stat_month(const RecordNode_t* head, int month);
void help();

#endif