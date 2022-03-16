#include "analyzer.h"

void* cpu_calc(void *cpu)
{
    
    //char line[100];
    char * ptr = &raw_data[0]; 
    struct cpustatus *c = (struct cpustatus*) cpu;
    pthread_mutex_lock(&mux_reader);
    for(int i = 0; i<5; i++)
    {
        sscanf(ptr,"%s %ld %ld %ld %ld %ld %ld %ld",c->cpu_name, &(c->cpu_user),&(c->cpu_nice),&(c->cpu_system),&(c->cpu_idle),&(c->cpu_iowait),&(c->cpu_irq), &(c->cpu_softirq));
        c++;
        while (*ptr != '\n')
        {
            ptr++;
        }
        ptr++;
    }
    pthread_mutex_unlock(&mux_reader);   
    return 0;
}

