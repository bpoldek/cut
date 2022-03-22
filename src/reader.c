#include "../inc/reader.h"
unsigned sleep(unsigned sec);

void *get_raw_data(void *c)
{
    while(1)
    {
        sem_wait(&cpu_buffer.buffEmpty);
        pthread_mutex_lock(&mux_reader);
        struct cpustatus *cpu = (struct cpustatus*)c;
        char *ptr = &raw_data[0];
        char line[80];
        uint8_t linesum=0;
        char *pline;
        FILE *fp= fopen("/proc/stat", "r");
        while(fgets(line,sizeof(line),fp))
        {
                pline = line;
                if(*pline!='c')
                    break;
                strcpy(ptr,line);
                ptr = ptr + strlen(line);
                linesum++;           
        }
        fclose(fp);
        
        parse_stat(cpu);
        sleep(1);
        printf("reader: %d %ld, %p\n", counter, cpu_buffer.head->cpu_user, cpu_buffer.head);
        cb_push_back(&cpu_buffer, cpu);
        counter++;
        pthread_mutex_unlock(&mux_reader);
        sem_post(&cpu_buffer.buffFull);
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