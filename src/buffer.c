#include "../inc/buffer.h"



void cb_init(circular_buffer *cb, size_t capacity, size_t sz)
{
    cb->buffer = malloc(capacity * sz);
    if(cb->buffer == NULL)
    {

    }
        // handle error
    cb->buffer_end =(cpustatus *)cb->buffer + capacity * sz;
    cb->capacity = capacity;
    cb->count = 0;
    cb->sz = sz;
    cb->head = cb->buffer;
    cb->tail = cb->buffer;
}

void cb_free(circular_buffer *cb)
{
    free(cb->buffer);
    // clear out other fields too, just to be safe
}

void cb_push_back(circular_buffer *cb, const cpustatus *item)
{
    if(cb->count == cb->capacity){
        return 0;
        // handle error
    }
   // assert(cb->head);
    memcpy(cb->head, item, cb->sz);
    cb->head = (cpustatus *)cb->buffer + cb->sz;
    if(cb->head == cb->buffer_end)
        cb->head = cb->buffer;
    cb->count++;
}

void cb_pop_front(circular_buffer *cb, cpustatus *item)
{
    if(cb->count == 0){
        // handle error
        return 0;
    }
    memcpy(item, cb->tail, cb->sz);
    cb->tail =(cpustatus *)cb->buffer + cb->sz;
    if(cb->tail == cb->buffer_end)
        cb->tail = cb->buffer;
    cb->count--;
}