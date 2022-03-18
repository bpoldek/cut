#include "../inc/analyzer.h"

void* cpu_calc(void *cpu)
{ 
    while (1)
    {
        pthread_mutex_lock(&mux_reader);
        pthread_mutex_lock(&mux_analyzer);
        //char * ptr = &raw_data[0]; 
        struct cpustatus *c = (struct cpustatus*)cpu;
        parse_stat(c);
        pthread_mutex_unlock(&mux_reader);
        pthread_mutex_lock(&mux_reader);
        parse_stat(c);
        pthread_mutex_unlock(&mux_reader);
        pthread_mutex_unlock(&mux_analyzer);   
    }
    

    return 0;
}

void parse_stat(struct cpustatus *c) 
{
    char * ptr = &raw_data[0];
    for(int i = 0; i<5; i++)
        {
            sscanf(ptr,"%s %ld %ld %ld %ld %ld %ld %ld",
            c->cpu_name,
            &(c->cpu_user),
            &(c->cpu_nice),
            &(c->cpu_system),
            &(c->cpu_idle),
            &(c->cpu_iowait),
            &(c->cpu_irq),
            &(c->cpu_softirq));
            c++;
            while (*ptr != '\n')
            {
                ptr++;
            }
            if(i<5)
                ptr++;
        }
}
