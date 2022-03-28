#include "../inc/printer.h"


void *print_status(void *cpu)
{
    while(1)
    {
        pthread_mutex_lock(&mux_reader);
        struct cpustatus *c = (struct cpustatus*) cpu;
        printf("%-4s | %-7s | %-4s | %-5s | %-7s | %-7s | %-3s | %-7s |\n","core", "user","nice","system", "idle", "iowait", "irq", "softirq");
        for(int i = 0; i <5 ; i++)
        {
            printf("%-6s %-9ld %-6ld %-8ld %-9ld %-9ld %-5ld %ld \n", c->cpu_name, c->cpu_user,(c->cpu_nice),c->cpu_system,c->cpu_idle,c->cpu_iowait,c->cpu_irq, c->cpu_softirq);
            c++;
        }
        pthread_mutex_unlock(&mux_reader); 
        sleep(1);
        system("clear");
    }
    return 0;
}
void *print_percent(void* percent)
{   
    while(1)
    {
        double *per =  (double*) percent;
        sem_wait(&print);
        pthread_mutex_lock(&mux_reader);
        printf("| Core | Percent of consumption |\n");
        printf("---------------------------------\n"); 
        printf("| Main | %-22.2lf |\n", *per);
        per++;
        for(int i=0; i<cpu_num_g-1; i++)
        {
            printf("| %-4d | %-22.2lf |\n",i, *per);
            per++;
        }
        printf("---------------------------------\n"); 
        sem_post(&fin);
        sem_post(&fin_prt); 
        pthread_mutex_unlock(&mux_reader);
        sleep(1);

        system("clear");
    }
    return 0;
}
