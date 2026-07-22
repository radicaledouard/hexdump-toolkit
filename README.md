# hexdump-toolkit

A hexdump analysis and binary inspection toolkit. Parse, filter, and visualize binary data.

## Features

- Multiple output formats (hex, binary, octal)
- Pattern search in binary data
- Diff mode for comparing hex dumps
- Filter by byte ranges
- Color-coded output

## Build

```bash
make
```

## Usage

```bash
./hexdump file.bin
./hexdump -l 8 file.bin
cat file | ./hexdump
```

## License

MIT
