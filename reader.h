#ifndef READER_H_
#define READER_H_

#include <stdio.h>
#include <pthread.h>
#include <stdint.h>
#include <string.h>
#include "cpu.h"
extern pthread_mutex_t mux_reader;
extern char raw_data[2048];
void *get_status(void *cpu);
void *get_raw_data(void *c);

#endif