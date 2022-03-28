#include "../inc/reader.h"
unsigned sleep(unsigned sec);

void *get_raw_data(void *c)
{
    while(1)
    {   
        struct cpustatus *cpu = (struct cpustatus*)c;
        sem_wait(&cpu_buffer.buffEmpty);
        sem_wait(&fin_prt);
        pthread_mutex_lock(&mux_reader);

        char *ptr_raw_data = &raw_data[0];
        get_lines(ptr_raw_data);                //get lines from proc/stat
        sleep(1);                   
        parse_stat(cpu);                        //pase raw data to cpustatus struct
        cb_push_back(&cpu_buffer, cpu);         //push cpustatus to buffer
        
        pthread_mutex_unlock(&mux_reader);
        sem_post(&cpu_buffer.buffFull);  
        sem_post(&prt_strt);
       
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
void get_lines(char *raw_data)
{    
        char line[80];
        uint8_t linesum=0;
        char *pline;
        FILE *fp= fopen("/proc/stat", "r");
        while(fgets(line,sizeof(line),fp))
        {
                pline = line;
                if(*pline!='c')
                    break;
                strcpy(raw_data,line);
                raw_data = raw_data+ strlen(line);
                linesum++;           
        }
        fclose(fp); 
}