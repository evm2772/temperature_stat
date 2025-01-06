#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "sensor.h"
#include "temp_api.h"
#define ERROR_MONTH_NUM -104

int main(int argc, char *argv[])
{
    if (argc == 1) 
    {
        help();
        return 0;
    }
    int opt = 0;
    char cvs_path[256];
    uint8_t m = 0;
    int h = 0;
    // Parse options
    while ((opt = getopt(argc, argv,"hf:m:")) != -1)
    {   
        switch (opt)
        {
            case 'h': 
                h = 1;
                break;
            case 'f': 
                strcpy(cvs_path, optarg);
                break;
            case 'm': 
                m = atoi(optarg);
                if ((m > 12) || (m < 1))
                {
                    printf("Error: month must be integer number from 1 to 12");
                    exit(ERROR_MONTH_NUM);
                }
                break;
            case '?': 
                printf("Unknown option. Type 'report -h' for help..\n");
                return 1;
        }
    }

    if (h)
    {
        help();
        return 0;
    }
    
    RecordNode_t *head = NULL;
    read_cvs(&head, cvs_path);
    stat_month(head, m);

    //Clear memory;
    RecordNode_t *tmp;
    while (head) 
    {
        tmp = pop(&head);
        free(tmp);
    }

}
