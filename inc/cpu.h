#ifndef CPU_H_
#define CPU_H_
typedef struct cpustatus{
    char cpu_name[6];
    unsigned long cpu_user;
    unsigned long cpu_nice;
    unsigned long cpu_system;
    unsigned long cpu_idle;
    unsigned long cpu_iowait;
    unsigned long cpu_irq;
    unsigned long cpu_softirq;
}cpustatus;
#endif