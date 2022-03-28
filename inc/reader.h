#ifndef READER_H_
#define READER_H_

#include <stdio.h>
#include <pthread.h>
#include <stdint.h>
#include <string.h>
#include <semaphore.h>
#include <signal.h>

#include "cpu.h"
#include "buffer.h"

extern pthread_mutex_t mux_reader;

extern struct circular_buffer cpu_buffer;
extern char raw_data[2048];
extern sem_t print, fin, prt_strt, fin_prt;

void *get_status(void *cpu);
void *get_raw_data(void *c);
void get_lines(char *raw_data);
void parse_stat(struct cpustatus *c);

#endif