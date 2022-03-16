#include "reader.h"
unsigned sleep(unsigned sec);
/*void *get_status(void *c)
{ 
        
        struct cpustatus *cpu = (struct cpustatus*) c;
        pthread_mutex_lock(&m);
        FILE *fp= fopen("/proc/stat", "r");
        if(fp!=NULL)
        {
            fscanf(fp,"%s %ld %ld %ld %ld %ld %ld %ld",cpu->cpu_name, &(cpu->cpu_user),&(cpu->cpu_nice),&(cpu->cpu_system),&(cpu->cpu_idle),&(cpu->cpu_iowait),&(cpu->cpu_irq), &(cpu->cpu_softirq));    
        }
        sleep(1);
        pthread_mutex_unlock(&sygnalizacja);
        fclose(fp); 

    return 0;
}*/
void *get_raw_data(void *c)
{
    printf("enter reader\n");
    char *byte = (char*)c;
    FILE *fp= fopen("/proc/stat", "r");
    char line[80];
    uint8_t linesum=0;
    char *pline;
    pthread_mutex_lock(&mux_reader);
    while(fgets(line,sizeof(line),fp))
    {
            pline = line;
            if(*pline!='c')
                break;
            strcpy(byte,line);
            byte = byte + strlen(line);
            linesum++;           
    }
    fclose(fp);
    pthread_mutex_unlock(&mux_reader);
    printf("redaer go sleep\n");
    printf("reader woke up\n");

    return 0;
}