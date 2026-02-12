#ifndef TRANSPORT_H
#define TRANSPORT_H

#include <stddef.h>
#include <stdint.h>

typedef struct {
    int  (*read_byte)(uint8_t *byte);   // returns 1 if byte read, 0 if none
    void (*write_bytes)(const uint8_t *data, size_t len);
} transport_t;

#endif
