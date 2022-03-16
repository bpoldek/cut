#ifndef PRINTER_H_
#define PRINTER_H_

#include <stdio.h>
#include <pthread.h>
#include "cpu.h"

#include "cpu.h"
extern pthread_mutex_t mux_reader;
void *print_status(void *cpu);
void *print_percent(void *cpu);

#endif