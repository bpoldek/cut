#ifndef CPU_H_
#define CPU_H_
struct cpustatus{
    char cpu_name[6];
    unsigned long cpu_user;
    unsigned long cpu_nice;
    unsigned long cpu_system;
    unsigned long cpu_idle;
    unsigned long cpu_iowait;
    unsigned long cpu_irq;
    unsigned long cpu_softirq;
    unsigned long cpu_user_prev;
    unsigned long cpu_nice_prev;
    unsigned long cpu_system_prev;
    unsigned long cpu_idle_prev;
    unsigned long cpu_iowait_prev;
    unsigned long cpu_irq_prev;
    unsigned long cpu_softirq_prev;

    unsigned long PrevNonIdle;
    unsigned long NonIdle;
    unsigned long Idle;
    unsigned long PrevIdle;
    unsigned long PrevTotal;
    unsigned long Total;
    double CPU_Percentage;
};
#endif