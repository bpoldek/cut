#include "reader.h"

void get_status(struct cpustatus *cpu, char*name)
{ 
    FILE *fp= fopen("/proc/stat", "r");
    
    if(fp!=NULL)
    {
        fscanf(fp,"%s %ld %ld %ld %ld %ld %ld %ld",cpu->cpu_name, &(cpu->cpu_user),&(cpu->cpu_nice),&(cpu->cpu_system),&(cpu->cpu_idle),&(cpu->cpu_iowait),&(cpu->cpu_irq), &(cpu->cpu_softirq));
        fclose(fp); 
    }
}