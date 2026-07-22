#include "hexdump.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

void hexdump_defaults(hexdump_opts_t *opts) {
    opts->show_ascii = 1;
    opts->colored = isatty(STDOUT_FILENO);
    opts->bytes_per_line = 16;
    opts->start_offset = 0;
    opts->end_offset = UINT64_MAX;
}

static void print_line(const uint8_t *data, size_t len,
                       uint64_t offset, const hexdump_opts_t *opts) {
    printf("%08lx  ", (unsigned long)offset);
    for (int i = 0; i < opts->bytes_per_line; i++) {
        if ((size_t)i < len)
            printf("%02x ", data[i]);
        else
            printf("   ");
        if (i == 7) printf(" ");
    }
    if (opts->show_ascii) {
        printf(" |");
        for (size_t i = 0; i < (size_t)opts->bytes_per_line; i++) {
            if (i < len)
                printf("%c", isprint(data[i]) ? data[i] : '.');
        }
        printf("|");
    }
    printf("\n");
}

int hexdump_buffer(const uint8_t *data, size_t len, const hexdump_opts_t *opts) {
    uint64_t offset = opts->start_offset;
    size_t pos = 0;
    while (pos < len && offset < opts->end_offset) {
        size_t n = len - pos;
        if (n > (size_t)opts->bytes_per_line) n = (size_t)opts->bytes_per_line;
        print_line(data + pos, n, offset, opts);
        pos += n;
        offset += n;
    }
    return 0;
}

int hexdump_file(const char *filename, const hexdump_opts_t *opts) {
    FILE *f = fopen(filename, "rb");
    if (!f) { fprintf(stderr, "hexdump: %s: not found\n", filename); return 1; }
    uint8_t buf[4096]; size_t n; int ret = 0;
    while ((n = fread(buf, 1, sizeof(buf), f)) > 0)
        if (hexdump_buffer(buf, n, opts) != 0) { ret = 1; break; }
    fclose(f); return ret;
}

int hexdump_stdin(const hexdump_opts_t *opts) {
    uint8_t buf[4096]; size_t n;
    while ((n = fread(buf, 1, sizeof(buf), stdin)) > 0)
        if (hexdump_buffer(buf, n, opts) != 0) return 1;
    return 0;
}
