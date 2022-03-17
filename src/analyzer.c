#include "../inc/analyzer.h"

void* cpu_calc(void *cpu)
{ 
    while (1)
    {
        pthread_mutex_lock(&mux_reader);
        pthread_mutex_lock(&mux_analyzer);
        char * ptr = &raw_data[0]; 
        struct cpustatus *c = (struct cpustatus*) cpu;
        c->cpu_nice_prev = c->cpu_nice;
        c->cpu_system_prev = c->cpu_system;
        c->cpu_idle_prev = c->cpu_idle;
        c->cpu_iowait_prev = c->cpu_iowait;
        c->cpu_irq_prev = c->cpu_irq;
        c->cpu_softirq_prev = c ->cpu_softirq_prev;
        for(int i = 0; i<5; i++)
        {
            sscanf(ptr,"%s %ld %ld %ld %ld %ld %ld %ld",c->cpu_name, &(c->cpu_user),&(c->cpu_nice),&(c->cpu_system),&(c->cpu_idle),&(c->cpu_iowait),&(c->cpu_irq), &(c->cpu_softirq));
            c++;
            while (*ptr != '\n')
            {
                ptr++;
            }
            if(i<5)
                ptr++;
        }
        c->cpu_idle_prev = c->cpu_idle_prev + c->cpu_iowait_prev;
        c->cpu_idle = c->cpu_idle + c->cpu_iowait;

        c->PrevNonIdle = c->cpu_user_prev + c->cpu_nice_prev + c->cpu_system_prev + c->cpu_softirq_prev;
        //PrevNonIdle = prevuser + prevnice + prevsystem + previrq + prevsoftirq + prevsteal
        c->NonIdle = c->cpu_user + c->cpu_nice + c->cpu_system + c->cpu_irq + c->cpu_softirq;
        //NonIdle = user + nice + system + irq + softirq + steal

        c->PrevTotal = c->PrevIdle + c->PrevNonIdle;
        c->Total = c->Idle + c->NonIdle;

        c->Total = c->Total - c->PrevTotal;
        c->Idle = c->Idle - c->PrevIdle;

        c->CPU_Percentage = (c->Total - c->Idle)/c->Total;
        pthread_mutex_unlock(&mux_reader);
        pthread_mutex_unlock(&mux_analyzer);   
    }
    

    return 0;
}

