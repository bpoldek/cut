#include "../inc/analyzer.h"

void* cpu_calc(void *cpu)
{ 
    while (1)
    {   
        struct cpustatus prev;
        struct cpustatus *act = (struct cpustatus*)cpu;
        pthread_mutex_lock(&mux_reader);
        sem_wait(&buffEmpty);
        parse_stat(act);
        cb_push_back(&cpu_buffer, act);
        sem_post(&buffFull);
        pthread_mutex_unlock(&mux_reader);
        sem_wait(&buffFull);
        pthread_mutex_lock(&mux_reader);
        cb_pop_front(&cpu_buffer, act);
        cb_pop_front(&cpu_buffer, &prev);
        percent = calculate_load(&prev, act);
        sem_post(&buffEmpty);
        pthread_mutex_unlock(&mux_reader);
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
double calculate_load(struct cpustatus *prev, struct cpustatus *cur) 
{
    int idle_prev = (prev->cpu_idle) + (prev->cpu_iowait);
    int idle_cur = (cur->cpu_idle) + (cur->cpu_iowait);

    int nidle_prev = (prev->cpu_user) + (prev->cpu_nice) + (prev->cpu_system) + (prev->cpu_irq) + (prev->cpu_softirq);
    int nidle_cur = (cur->cpu_user) + (cur->cpu_nice) + (cur->cpu_system) + (cur->cpu_irq) + (cur->cpu_softirq);

    int total_prev = idle_prev + nidle_prev;
    int total_cur = idle_cur + nidle_cur;

    double totald = (double) total_cur - (double) total_prev;
    double idled = (double) idle_cur - (double) idle_prev;

    double cpu_perc = (1000 * (totald - idled) / totald + 1) / 10;

    return cpu_perc;
}