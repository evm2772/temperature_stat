#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sensor.h"

#define STACK_OVERFLOW  -100
#define STACK_UNDERFLOW -101
#define ERROR_READ_FILE -103
 

void push(RecordNode_t **head, record_t value) 
{
    RecordNode_t *tmp = malloc(sizeof(RecordNode_t));
    if (tmp == NULL) 
    {
        exit(STACK_OVERFLOW);
    }
    tmp->next = *head;
    tmp->value = value;
    *head = tmp;
}


RecordNode_t* pop(RecordNode_t **head) {
    RecordNode_t *out;
    if ((*head) == NULL) {
        exit(STACK_UNDERFLOW);
    }
    out = *head;
    *head = (*head)->next;
    return out;
}


size_t get_size(const RecordNode_t *head) 
{
    size_t size = 0;
    while (head) {
        size++;
        head = head->next;
    }
    return size;
}


void print_list(const RecordNode_t* head, int nrecords) 
{
    printf("\nRecords:\n");
    size_t counter = 1;
    while (head) 
    {
        if ((counter > nrecords) && (nrecords != 0)) 
            break;
        printf("#%6zu | %04d-%02d-%02d | %02d:%02d | t = %3d\n",
            counter,    
            head->value.year,
            head->value.month,
            head->value.day,
            head->value.hh,
            head->value.mm,
            head->value.temperature);
        head = head->next;
        counter++;
        
    }
}

void add_record(RecordNode_t **head,
                uint16_t year,
                uint8_t month,
                uint8_t day,
                uint8_t hh,
                uint8_t mm,
                int8_t t)
{   

    record_t record;
    record.year = year;
    record.month = month;
    record.day = day;
    record.hh = hh;
    record.mm = mm;
    record.temperature = t;
    push(head, record);
}


void add_test_data(RecordNode_t **head)
{
    add_record(head, 2021, 9, 16, 23, 56, -12);
    add_record(head, 2021, 9, 17, 23, 56, -10);
    add_record(head, 2021, 5, 23, 23, 56, -4);
    add_record(head, 2021, 9, 31, 23, 34, -1);
    add_record(head, 2021, 11, 16, 23, 56, -10);
    add_record(head, 2021, 2, 16, 23, 56, -12);
    add_record(head, 2021, 3, 17, 23, 56, -10);
    add_record(head, 2021, 4, 23, 23, 56, -4);
    add_record(head, 2021, 7, 31, 23, 34, -1);
    add_record(head, 2021, 11, 16, 23, 56, -10);
}


void read_cvs(RecordNode_t **head, const char* path)
{
    FILE* f = fopen(path, "r");
    if (f == NULL)
    {
        printf("Cannot read file %s", path);
        exit(ERROR_READ_FILE);
    }

    int x, y, m, d, hh, mm, t, line = 0;
    char err_str[256];
    printf("\n------------------------------------------------------------------------------------\n");
    while((x = fscanf(f, "%4d;%d;%d;%d;%d;%d\n", &y, &m, &d, &hh, &mm, &t)) != EOF)
    {
        line++;
        if (x < 6) 
        {
            fscanf(f, "%s[^\n]", err_str);
            printf("Data Syntax Error: Ln %d: %s\n", line , err_str);
            continue;
        }
        if ((m > 12) || (m < 1))
        {
            printf("Data Error (month = %d): Ln %d\n", m, line);
            continue;
        }
        if ((d > 31) || (d < 1))
        {
            printf("Data Error (day = %d): Ln %d\n", d, line);
            continue;
        }
        if ((hh > 23) || (hh < 0))
        {
            printf("Data Error (hours = %d): Ln %d\n", hh, line);
            continue;
        }
        if ((mm > 59) || (mm < 0))
        {
            printf("Data Error (minutes = %d): Ln %d\n", mm, line);
            continue;
        }

        if ((t > 99) || (t < -99))
        {
            printf("Data Error (temperature = %d): Ln %d\n", t, line);
            continue;
        }

        add_record(head,    (uint16_t)y, 
                            (uint8_t)m, 
                            (uint8_t)d, 
                            (uint8_t)hh, 
                            (uint8_t)mm, 
                            (int8_t)t);
       
    }
    fclose(f);
    printf("\nTotal valid records in file: %zu", get_size((*head)));
}
