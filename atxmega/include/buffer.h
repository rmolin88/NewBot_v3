#ifndef BUFFER_H_
#define BUFFER_H_

#include "atxmega.h"
#include <string.h>

#define RING_BUFFER_MAX 1

typedef struct _ring_buffer
{
	uint8_t s_elem;
	uint8_t n_elem;
    uint8_t *buf;
    volatile uint8_t head;
    volatile uint8_t tail;
}ring_buffer;

typedef struct _rb_attr_t
{
	uint8_t s_elem;
    uint8_t n_elem;
    void *buffer;
}rb_attr_t;

int ring_buffer_init(rb_attr_t *attr);
// static int _ring_buffer_full(ring_buffer *rb);
// static int _ring_buffer_empty(ring_buffer *rb);
int ring_buffer_put(const void *data);
int ring_buffer_get(void *data);

#endif	// End of BUFFER_H_
