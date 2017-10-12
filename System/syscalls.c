#include <reent.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include "driverlib/inc/hw_memmap.h"
#include "System/chip.h"
#include "driverlib/uart.h"
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"

void _exit(int code)
{
    while(1) {};
}

_ssize_t _write(int fd, const void* buffer, size_t count)
{
    taskENTER_CRITICAL();
    for(int i=0; i<count; i++) {
        UARTCharPut(UART0_BASE, ((char*)buffer)[i]);
    }
    taskEXIT_CRITICAL();
    return 0;
}

char* heap_cur = 0;
caddr_t _sbrk(intptr_t incr)
{
    extern uint8_t __heap_start__;
    extern uint8_t __stack;
    taskENTER_CRITICAL();
    //If heap_cur is 0, it hasn't been initialized yet
    if (heap_cur == 0)
        heap_cur = (char*)&__heap_start__;
    //If incr is zero, this is just a request for the current break
    if (incr == 0)
        return heap_cur;
    //Calculate where the new break will be and check for passing the end of memory
    caddr_t heap_next = heap_cur + incr;
    if (heap_next > (caddr_t)&__stack) {
        errno = ENOMEM;
        return (caddr_t)-1;
    }
    //Save the old break to return and switch to the new break
    caddr_t heap_prev = heap_cur;
    heap_cur = heap_next;
    taskEXIT_CRITICAL();
    return (caddr_t)heap_prev;
}
int _close(int fd)
{
    errno = EIO;
    return -1;
}
off_t _lseek(int fd, off_t offset, int whence)
{
    errno = ESPIPE;
    return (off_t)-1;
}
ssize_t _read(int fd, void* buf, size_t count)
{
    errno = EIO;
    return -1;
}
int _fstat(int fd, struct stat* statbuf)
{
    errno = EACCES;
    return -1;
}
int _isatty(int fd)
{
    return 1;
}