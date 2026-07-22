#include "hexdump.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void usage(const char *p) {
    fprintf(stderr, "Usage: %s [-aAcl:oh] [FILE...]\n", p);
}

int main(int argc, char **argv) {
    hexdump_opts_t opts;
    hexdump_defaults(&opts);
    int opt;
    while ((opt = getopt(argc, argv, "aAcCl:oh")) != -1) {
        switch (opt) {
            case 'A': opts.show_ascii = 0; break;
            case 'C': opts.colored = 0; break;
            case 'c': opts.colored = 1; break;
            case 'l': opts.bytes_per_line = atoi(optarg); break;
            case 'o': opts.start_offset = strtoull(optarg, NULL, 0); break;
            case 'h': usage(argv[0]); return 0;
            default:  usage(argv[0]); return 1;
        }
    }
    if (optind >= argc) return hexdump_stdin(&opts);
    int ret = 0;
    for (int i = optind; i < argc; i++)
        if (hexdump_file(argv[i], &opts) != 0) ret = 1;
    return ret;
}
