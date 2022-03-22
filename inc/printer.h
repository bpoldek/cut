#ifndef PRINTER_H_
#define PRINTER_H_

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include "cpu.h"
unsigned sleep(unsigned sec);
extern pthread_mutex_t mux_reader, mux_analyzer;
extern double percent[20];
void *print_status(void *cpu);
void *print_percent(void* p);
extern sem_t buffEmpty,buffFull,print,fin;
#endif