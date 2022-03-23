#include "../inc/analyzer.h"

void* cpu_calc(void *cpu)
{ 
    while (1)
    {   
        struct cpustatus prev;
        struct cpustatus *act = (struct cpustatus*)cpu;
        struct cpustatus *prev_ptr = &prev;


        sem_wait(&cpu_buffer.buffFull);
        sem_wait(&fin);
        pthread_mutex_lock(&mux_reader);
       // pthread_mutex_lock(&mux_analyzer);
        for(int i = 0 ;i<5;i++)
        {
            memcpy(prev_ptr,act,sizeof(struct cpustatus));
            act++;
            prev_ptr++;
        }
        prev_ptr = &prev;

        cb_pop_front(&cpu_buffer, act);
        
        if(prev_ptr->cpu_user != act->cpu_user)
        {
            for (size_t i = 0; i < cpu_num_g; i++)
            {
                percent[i] = calculate_load(prev_ptr, act);
               // printf("Percent %s, %lf\n",act->cpu_name, percent[i]);
                act++;
                prev_ptr++;
            }
        }
        counter--;
        pthread_mutex_unlock(&mux_reader);
       // pthread_mutex_unlock(&mux_analyzer);
        
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
    if(cpu_perc!=0)
        return cpu_perc;
    else
        return 0;
}