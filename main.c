#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <semaphore.h>
#include "inc/buffer.h"
#include "inc/cpu.h"
#include "inc/printer.h"
#include "inc/reader.h"
#include "inc/analyzer.h"

#define BUFF_SIZE 10

char raw_data[2048];

double percent[20];
int counter=0;
sem_t print, fin;

unsigned sleep(unsigned sec);

pthread_mutex_t mux_reader, mux_analyzer, mux_printer;

circular_buffer cpu_buffer;

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
    pthread_t reader, printer, analyzer;
    uint8_t cpu_num = get_num_cpu();
    struct cpustatus cpu[cpu_num];
    pthread_mutex_init(&mux_reader, NULL);
    pthread_mutex_init(&mux_analyzer, NULL);;
    cb_init(&cpu_buffer, 2,sizeof(cpustatus));


    sem_init(&print,0,0);
    sem_init(&fin,1,20);
    //system("clear");
    
    if(pthread_create(&reader,NULL,get_raw_data, &cpu)==-1)
        printf("Nie mozna utworzyc watku reader");
    if(pthread_create(&analyzer,NULL,cpu_calc,&cpu)==-1)
        printf("Nie mozna utworzyc watku printer");
    /*if(pthread_create(&printer,NULL,print_percent,&percent)==-1)
        printf("Nie mozna utworzyc watku printer");*/
       
    //system("clear");

    if(pthread_join(reader, NULL)==-1)
        printf("Blad zakonczenia watku");
    if(pthread_join(analyzer, NULL)==-1)
        printf("Blad zakonczenia watku");
    if(pthread_join(printer, NULL)==-1)
        printf("Blad zakonczenia watku");
    pthread_mutex_destroy(&mux_reader);
    pthread_mutex_destroy(&mux_analyzer);
    cb_free(&cpu_buffer);
    //pthread_mutex_destroy(&mux_printer);
    return 0; 
}
