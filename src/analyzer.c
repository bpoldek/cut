#include "../inc/analyzer.h"

void* cpu_calc(void *cpu)
{ 
    while (1)
    {   
        struct cpustatus prev;
        struct cpustatus *act = (struct cpustatus*)cpu;

        sem_wait(&cpu_buffer.buffFull);
        sem_wait(&fin);
        pthread_mutex_lock(&mux_analyzer); 
        pthread_mutex_lock(&mux_reader);
        
       // printf("act: %ld adress: %p\n",cpu_buffer.tail->cpu_user, cpu_buffer.tail);
        //cb_pop_front(&cpu_buffer, &prev);
        
        memcpy(&prev,act,sizeof(struct cpustatus));
        cb_pop_front(&cpu_buffer, act);
        //printf("prev: %ld adress: %p\n",cpu_buffer.tail->cpu_user, cpu_buffer.tail);
        //printf("In analyzer: %d ,act: %ld prev: %ld\n", counter, act->cpu_user, prev.cpu_user );
        percent[counter] = calculate_load(&prev, act);
        printf("Percent %d, %lf\n",counter, percent[counter]);
        counter--;
        //if(cpu_buffer.count==0)
        pthread_mutex_unlock(&mux_reader);
        pthread_mutex_unlock(&mux_analyzer);
        sem_post(&cpu_buffer.buffEmpty);
        sem_post(&print);
    }
    return 0;
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