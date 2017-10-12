#!/bin/bash

# A simple hack to get configure to pass the compiler check on Debian with 
# newlib missing most system calls

MACHINE="armv7e-m"
NEWLIB="/usr/lib/arm-none-eabi/newlib/"
CC=arm-none-eabi-gcc
AR=arm-none-eabi-ar

cat > /tmp/_exit.c << EOF
void _exit(int code) {};
EOF

$CC -c /tmp/_exit.c -mthumb -march=$MACHINE -o /tmp/_exit.o
$AR qs $NEWLIB/libc.a /tmp/_exit.o
rm /tmp/_exit.c /tmp/_exit.o
