#include "../inc/buffer.h"



void cb_init(circular_buffer *cb, size_t capacity, size_t sz)
{
    cb->buffer = malloc(capacity * sz);
    if(cb->buffer == NULL)
    {
    }
    cb->buffer_end =(char *)cb->buffer + capacity * sz;
    cb->capacity = capacity;
    cb->count = 0;
    cb->sz = sz;
    cb->head = cb->buffer;
    cb->tail = cb->buffer;
    sem_init(&cb->buffEmpty,0,cb->capacity);
    sem_init(&cb->buffFull,0,0);
}

void cb_free(circular_buffer *cb)
{
    free(cb->buffer);
    sem_destroy(&cb->buffEmpty);
    sem_destroy(&cb->buffFull);
    // clear out other fields too, just to be safe
}

void cb_push_back(circular_buffer *cb, const cpustatus *item)
{
    if(cb->count == cb->capacity){
    }
    cb->head = (cpustatus *)cb->buffer + (cb->sz * cb->count);
    memcpy(cb->head, item, cb->sz);
    if(cb->head == cb->buffer_end)
        cb->head = cb->buffer;
    cb->count++;
}

void cb_pop_front(circular_buffer *cb, cpustatus *item)
{
    if(cb->count == 0){
        printf("pop_front count==size\n");
    }
    memcpy(item, cb->tail, cb->sz); 
    cb->tail =(cpustatus*)cb->buffer + (cb->sz * cb->count) ;
    if(cb->tail == cb->buffer_end)
        cb->tail = cb->buffer;
    cb->count--;
    
}