#ifndef HEXDUMP_H
#define HEXDUMP_H
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

typedef struct {
    int show_ascii;
    int colored;
    int bytes_per_line;
    uint64_t start_offset;
    uint64_t end_offset;
} hexdump_opts_t;

void hexdump_defaults(hexdump_opts_t *opts);
int hexdump_file(const char *filename, const hexdump_opts_t *opts);
int hexdump_buffer(const uint8_t *data, size_t len, const hexdump_opts_t *opts);
int hexdump_stdin(const hexdump_opts_t *opts);
#endif
