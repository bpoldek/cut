#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>
#include <string.h>
#include "inc/cpu.h"
#include "inc/printer.h"
#include "inc/reader.h"
#include "inc/analyzer.h"

char raw_data[2048];

unsigned sleep(unsigned sec);

pthread_mutex_t mux_reader, mux_analyzer, mux_printer;

uint8_t get_num_cpu()
{
    FILE *fp= fopen("/proc/stat", "r");
    char line[80];
    uint8_t linesum=0;
    char *pline;
    while(fgets(line,sizeof(line),fp))
    {
            pline = line;
            if(*pline!='c')
                break;
            linesum++;           
    }
    fclose(fp);

    return linesum;
}
int main()
{   
    pthread_mutex_init(&mux_reader, NULL);;
    pthread_t reader, printer, analyzer;
    uint8_t cpu_num = get_num_cpu();
    struct cpustatus cpu[cpu_num];
    /*if(cpu_num!=0)
    {
        
    }
    else
    {
        printf("Bad number of CPU\n");
        exit(1);
    }*/
    system("clear");
    
    while (1)
    {   
        if(pthread_create(&reader,NULL,get_raw_data, raw_data)==-1)
            printf("Nie mozna utworzyc watku reader");
        if(pthread_create(&analyzer,NULL,cpu_calc,&cpu)==-1)
            printf("Nie mozna utworzyc watku printer");
        if(pthread_create(&printer,NULL,print_status,&cpu)==-1)
            printf("Nie mozna utworzyc watku printer");
       sleep(1);
       system("clear");

    }
    if(pthread_join(reader, NULL)==-1)
        printf("Blad zakonczenia watku");
    if(pthread_join(analyzer, NULL)==-1)
        printf("Blad zakonczenia watku");
    if(pthread_join(printer, NULL)==-1)
        printf("Blad zakonczenia watku");
    pthread_mutex_destroy(&mux_reader);
    //pthread_mutex_destroy(&mux_analyzer);
    //pthread_mutex_destroy(&mux_printer);
    return 0; 
}
