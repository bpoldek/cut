#ifndef READER_H_
#define READER_H_

#include <stdio.h>
#include <pthread.h>
#include <stdint.h>
#include <string.h>
#include <semaphore.h>
#include "cpu.h"
#include "buffer.h"
extern pthread_mutex_t mux_reader, mux_analyzer;
extern struct circular_buffer cpu_buffer;
extern char raw_data[2048];
extern sem_t buffEmpty,buffFull,print;
extern int counter;
void *get_status(void *cpu);
void *get_raw_data(void *c);
void parse_stat(struct cpustatus *c);

#endif