#include "printer.h"

void print_status(struct cpustatus *cpu, char*name)
{
    printf("%s %ld %ld %ld %ld %ld %ld %ld\n",cpu->cpu_name, cpu->cpu_user,cpu->cpu_nice,cpu->cpu_system,cpu->cpu_idle,cpu->cpu_iowait,cpu->cpu_irq, cpu->cpu_softirq);
}