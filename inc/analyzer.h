#ifndef ANALYZER_H_
#define ANALYZER_H_

#include <stdio.h>
#include <pthread.h>
#include "cpu.h"

extern pthread_mutex_t mux_reader, mux_analyzer;
extern char raw_data[2048];

void* cpu_calc(void *cpu);
void parse_stat(struct cpustatus *c); 

#endif