#include <stdio.h>
#include "temp_api.h"
#include <inttypes.h>

void print_stat(Stat_t stat, int month_num)
{
    if (stat.records_number > 0)
    {
        printf("%10d | %10lld | %10d | %10d | %10d | %10.2f ",
                month_num,
                stat.records_number,   
                stat.year,
                stat.t_min,
                stat.t_max,
                stat.t_sum/stat.records_number
                );
    }
    else
        printf("%10d | %10lld | %10s | %10s | %10s | %10s ",
                month_num,
                stat.records_number,   
                "-",
                "-",
                "-",
                "-"
                );
};

void stat_month(const RecordNode_t* head, int month)
{
    // Init array with months stats:
    Stat_t stats[12];
    for (int i = 0; i < 12; i++)
    {
        stats[i].records_number = 0;
        stats[i].year = 0;
        stats[i].t_min = 100;
        stats[i].t_max =  -100;
        stats[i].t_sum =  0.;
    }

    while (head) {
        stats[head->value.month - 1].records_number++;
        stats[head->value.month - 1].year = head->value.year;
        // Min T
        if (head->value.temperature < stats[head->value.month - 1].t_min) 
            stats[head->value.month - 1].t_min = head->value.temperature;
        // Max T
        if (head->value.temperature > stats[head->value.month - 1].t_max) 
            stats[head->value.month - 1].t_max = head->value.temperature;
        // T sum
        stats[head->value.month - 1].t_sum += head->value.temperature;
        head = head->next;
    }

    // Year stats:
    int64_t records_number_y = 0;
    int8_t t_min_y = 100;
    int8_t t_max_y = -100;
    double t_sum_y = 0.0;
    for (int i = 0; i < 12; i++)
    {
        records_number_y += stats[i].records_number;
        t_sum_y += stats[i].t_sum;
        t_min_y =  (t_min_y > stats[i].t_min) ? stats[i].t_min : t_min_y;
        t_max_y =  (t_max_y < stats[i].t_max) ? stats[i].t_max : t_max_y;
    } 
    
    printf("\n------------------------------------------------------------------------------------");
    printf("\n%10s | %10s | %10s | %10s | %10s | %10s ", "Month",  "N-Records", "Year", "T min", "T max", "T avg");
    printf("\n------------------------------------------------------------------------------------");
    if (!month)
        {
            for (int i = 0; i < 12; i++)
            {
                printf("\n");
                print_stat(stats[i], i + 1);
            }
            printf("\n------------------------------------------------------------------------------------");
            printf("\nYear Temperature Statistic:\tMin: %d\tMax: %d\tAvg: %.2f", t_min_y, t_max_y, t_sum_y/records_number_y);
            printf("\n------------------------------------------------------------------------------------");
        }
    else
        {
            printf("\n");
            print_stat(stats[month - 1], month);
            printf("\n------------------------------------------------------------------------------------");

        }
    printf("\n");
};

void help()
{
    printf("\nTemperature statistic application.\n");
    printf("\tUsage: report [-h | -m <month number>] -f <path>\n");
    printf("\t\t-h \t Show this help.\n");
    printf("\t\t-f \t Path to cvs file with ; separator. Show temperature statistics for year.\n");
    printf("\t\t   \t See -m option to get month statisics.\n");
    printf("\t\t-m \t <month number> integer number [1-12]. Show temperature statistics for month.\n");
    printf("\tExamples:\n");
    printf("\t\treport -m 2 -f data.csv\n");
    printf("\t\treport -f data.csv\n");
    printf("\t\treport -h\n");
};
