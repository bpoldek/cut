#ifndef ANALYZER_H_
#define ANALYZER_H_

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include "cpu.h"
#include "buffer.h"

extern pthread_mutex_t mux_reader, mux_analyzer;
extern char raw_data[2048];
extern uint8_t cpu_num_g;
extern double percent[16];
extern struct circular_buffer cpu_buffer;
extern sem_t buffEmpty,buffFull,print,fin;
extern int counter;
void* cpu_calc(void *cpu);



double calculate_load(struct cpustatus *prev, struct cpustatus *cur); 

#endif