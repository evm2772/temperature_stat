#ifndef SENSOR_H
#define SENSOR_H
#include <inttypes.h>

typedef struct {
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hh;
    uint8_t mm;
    int8_t temperature;
} record_t;

//List stack
typedef struct RecordNode{
    record_t value;
    struct RecordNode *next;
} RecordNode_t;

void push(RecordNode_t **head, record_t value);

RecordNode_t* pop(RecordNode_t **head) ;

void print_list(const RecordNode_t* head, int nrecords);

size_t get_size(const RecordNode_t *head);

void add_record(RecordNode_t **head,
                uint16_t year,
                uint8_t month,
                uint8_t day,
                uint8_t hh,
                uint8_t mm,
                int8_t t);

void add_test_data(RecordNode_t **head);
void read_cvs(RecordNode_t **head, const char* path);

#endif
