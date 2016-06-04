#include "../include/buffer.h"

static ring_buffer _rb;

int ring_buffer_init(rb_attr_t *attr)
{
    int err = -1; 
 
	if ((attr->buffer != 0) && (attr->s_elem > 0)) 
	{
		/* Check that the size of the ring buffer is a power of 2 */
		if (((attr->n_elem - 1) & attr->n_elem) == 0) 
		{
			/* Initialize the ring buffer internal variables */
			_rb.head = 0;
			_rb.tail = 0;
			_rb.buf = attr->buffer;
			_rb.s_elem = attr->s_elem;
			_rb.n_elem = attr->n_elem;

			err= 0;
		}
	}
 
    return err;
}

static int _ring_buffer_full(ring_buffer *rb)
{
    return ((rb->head - rb->tail) == rb->n_elem) ? 1 : 0;
}
 
static int _ring_buffer_empty(ring_buffer *rb)
{
    return ((rb->head - rb->tail) == 0U) ? 1 : 0;
}

int ring_buffer_put(const void *data)
{
    int err = 0;
 
    if (_ring_buffer_full(&_rb) == 0) 
    {
        const size_t offset = (_rb.head & (_rb.n_elem - 1)) * _rb.s_elem;
        memcpy(&(_rb.buf[offset]), data, _rb.s_elem);
        _rb.head++;
    } 
    else 
        err = -1;
 
    return err;
}

int ring_buffer_get(void *data)
{
    int err = 0;
 
    if (_ring_buffer_empty(&_rb) == 0) 
    {
        const size_t offset = (_rb.tail & (_rb.n_elem - 1)) * _rb.s_elem;
        memcpy(data, &(_rb.buf[offset]), _rb.s_elem);
        _rb.tail++;
    } 
    else 
        err = -1;
 
    return err;
}
