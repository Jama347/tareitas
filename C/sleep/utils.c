#include "utils.h"
#include <time.h>
#include <stdio.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

void pausa_ms(int milisegundos) {
#ifdef _WIN32
    Sleep(milisegundos);
#else
    usleep(milisegundos * 1000);
#endif
}
