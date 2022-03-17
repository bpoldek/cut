#include "../inc/printer.h"

void *print_status(void *cpu)
{
    pthread_mutex_lock(&mux_reader);
    struct cpustatus *c = (struct cpustatus*) cpu;
    for(int i = 0; i <5 ; i++)
    {
        printf("%s %ld %ld %ld %ld %ld %ld %ld\n", c->cpu_name, c->cpu_user,(c->cpu_nice),c->cpu_system,c->cpu_idle,c->cpu_iowait,c->cpu_irq, c->cpu_softirq);
        c++;
    } 
    pthread_mutex_unlock(&mux_reader);
    return 0;
}
/*void *print_percent(void *cpu)
{
    PrevIdle = previdle + previowait
    Idle = idle + iowait

    PrevNonIdle = prevuser + prevnice + prevsystem + previrq + prevsoftirq + prevsteal
    NonIdle = user + nice + system + irq + softirq + steal

    PrevTotal = PrevIdle + PrevNonIdle
    Total = Idle + NonIdle

# differentiate: actual value minus the previous one
totald = Total - PrevTotal
idled = Idle - PrevIdle

CPU_Percentage = (totald - idled)/totald
    return 0;
}*/