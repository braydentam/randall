# Randall

## Overview
Randall is a Random Byte Generator is a command-line interface (CLI) tool designed for generating random bytes. 

## Features
- **Seed Sources**: Choose from hardware, software, or file-based seed sources.
- **Hardware Capability Checks**: Uses CPUID and RDRAND instructions to verify and utilize hardware RNG capabilities.
- **Output Options**: Supports block-wise writing of generated random bytes.
- **Memory Management**: Leverages advanced C memory management techniques for optimal performance.
- **Testing**: Includes unit tests, Valgrind, and AddressSanitizer to ensure code robustness.

## Prerequisites

- **C Compiler**
- **Make**
- **Shell** - Bash or any POSIX-compliant shell.

## Installation
1. cd into randall:
   ```sh
   cd randall
   ```
2. build the program:
   ```sh
   make
   ```
   
## Options
    -i, --input [rdrand|lrand48_r|file <filename>]: Select the seed source.
      - `rdrand`: Use hardware-based random number generation.
      - `lrand48_r`: Use software-based random number generation.
      - `file <filename>`: Use a file as the seed source.
    
    -o, --output <stdio|N>: Specify the output method.
      - `stdio`: Write to standard output.
      - `N`: Write in blocks of N bytes.

### Examples

1. Generate 5 random bytes using hardware RNG (`rdrand`) and output to standard output:
   `sh
   ./randall -i rdrand -o stdio 5
   `

2. Generate 23 random bytes using software RNG (`lrand48_r`) and output to standard output:
   `sh
   ./randall -i lrand48_r -o stdio 23
   `

3. Generate 42 random bytes using a file (`/dev/random`) as the seed source and output in blocks of 10 bytes:
   `sh
   ./randall -i /dev/random -o 10 42
   `

my thought and development process are in notes.txt