#ifndef PRINTER_H_
#define PRINTER_H_

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdint.h>

#include "cpu.h"

unsigned sleep(unsigned sec);

extern uint8_t cpu_num_g;
extern pthread_mutex_t mux_reader, mux_analyzer;
extern double percent[16];

void *print_status(void *cpu);
void *print_percent(void* p);

extern sem_t print, fin, prt_strt, fin_prt;

#endif