#include <stdio.h>
#include <pthread.h>
#include <stdint.h>
#include <string.h>
#include "cpu.h"
#include "printer.h"
#include "reader.h"

unsigned sleep(unsigned sec);

uint8_t get_num_of_cpu()
{
    uint8_t num =1 ;
    char cpu[6] = {"cpu"};
    char cpu_to[6] = {"cpu"}; 
    char c_num;
    FILE *fp= fopen("/proc/stat", "r");
    for (int i = 0; i < 6; i++)
    {

       /* c_num = itoa(i);
        strncat(cpu_to,c_num,3);

        fscanf(fp, "%s", cpu);
        if(strcmp(cpu,cpu_to)==1)
            num++;*/
    }
    
    return num;
}
int main()
{
    uint8_t num_of_cpu = get_num_of_cpu();

    struct cpustatus cpu;

    //Wstęp do wątku

    /*pthread_t reader, analyser;
    if(pthread_create(&reader,NULL,get_status(&cpu, "cpu0"),NULL)==-1)
        printf("Nie mozna utworzyc watku reader");
    //pthread_create(&analyser,NULL,get_status(&cpu, "cpu0"), NULL);*/
    while (1)
    {   
        get_status(&cpu, "cpu0");
        print_status(&cpu, "cpu0");
        sleep(1);
    }
    return 0; 
}
