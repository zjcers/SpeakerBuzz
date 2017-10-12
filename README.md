# tiva-gcc-base
A base project for the TI Tiva EK-TM4C1294XL

Build dependencies (debian packages)
* arm-none-eabi-gcc
* autoconf
* automake
* libtool
Debug dependencies (debian packages)
* openocd
* netcat
* arm-none-eabi-gdb

Build instructions
1. ./autogen.sh
2. cd build/
3. ../configure --host=arm-none-eabi
4. make

Program instructions
1. Start openocd -f /usr/share/openocd/scripts/board/ek-tm4c1294xl.cfg in a terminal
2. arm-none-eabi-gdb project.bin
  1. target extended-remote :3333
  2. monitor reset halt
  3. load
  4. monitor reset init
  5. continue
