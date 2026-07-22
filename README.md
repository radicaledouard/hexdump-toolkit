# hexdump-toolkit

> A hexdump analysis toolkit in C

## Overview

A fast, minimal hexdump tool for binary analysis. Supports custom formatters, diffing, and pattern search.

## Features

- Multiple output formats (hex, binary, octal)
- Pattern search in binary data
- Diff mode for comparing hex dumps
- Filter by byte ranges
- Color-coded output

## Build

```bash
gcc -O2 -o hexdump hexdump.c
```

## Usage

```bash
./hexdump file.bin
./hexdump -f binary file.bin
./hexdump --diff file1.bin file2.bin
```

## License

MIT

## Co-authored with [@SamyAlderson](https://github.com/SamyAlderson)
